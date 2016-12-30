//
// Created by prolog on 09.12.16.
//

#ifndef GARBAGECOLLECTOR_HEAP_H
#define GARBAGECOLLECTOR_HEAP_H

#include "descriptors/typeDescriptor.h"
#include "block.h"

#include <stdlib.h>
#include <string>
#include <map>


using namespace std;
using Tag = TypeDescriptor *;

class Heap {
    using TypeDescriptorMap = map<string, TypeDescriptor *>;
public:
    static void gc(Pointer pointers[]) {
        for (int index = 0; pointers[index] != NULL; index++) {
            mark(pointers[index]);
        }
    }

    static Pointer alloc(string name) {
        TypeDescriptor *typeDescriptor = descriptors[name];
        Block *allocBlock = alloc(typeDescriptor);
        printf("Alloc:\n");
        printf("Block: %p \n", allocBlock);
        return determinePointer(allocBlock);
    }

    static void registered(string name, TypeDescriptor *typeDescriptor) {
        descriptors[name] = typeDescriptor;
        printf("descriptor: %p \n", typeDescriptor);
    }

private:
    static TypeDescriptorMap descriptors;
    static Block *free;

    static Block *createBlock(byte *data, int len) {
        initData(data, len);
        Block *block = (Block *) data;
        block->len = len;
        block->next = block;
        block->tag = 0;
        block->setFree(true);
        return block;
    }

    static void initData(byte *data, int length) {
        for (int i = 0; i < length; i++) {
            *(data + i) = 0;
        }
    }

    static Block *alloc(TypeDescriptor *typeDescriptor) {
        int size = typeDescriptor->objSize + OFFSET_DATA;
        Block *start = free;
        Block *prev = free;
        free = free->next;
        while (free->len < size && free != start) {
            prev = free;
            free = free->next;
        }
        if (free->len < size) {
            throw new bad_alloc;
        } else {
            Block *p = free;
            int newLen = p->len - size;
            if (newLen >= 8) { // split block
                p = (Block *) ((uintptr_t) p + p->len - size); // add new block with pointer arithmetic
                p->len = size;
                free->len = newLen;
            } else if (free == prev) { // last free block
                free = NULL;
            } else { // remove block from list
                prev->next = free->next;
                free = prev;
            }
            //Set all data bytes in block p to
            initData(determinePointer(p), size - OFFSET_DATA);
            p->tag = typeDescriptor;
            p->setFree(false);
            return p;
        }
    }

    static void mark(Pointer current) {
        determineBlock(current)->setMarked(true);
        Pointer prev = NULL;

        printf("Mark Block: %p \n", determineBlock(current));
        printf("Mark Tag: %p \n", determineBlock(current)->tag);

        for (;;) {
            determineBlock(current)->tag = (Tag) ((uintptr_t) determineBlock(current)->tag + 4);
            int off = *reinterpret_cast<int *>((uintptr_t) determineBlock(current)->tag - 1);
            printf("Offset: %d \n", off);
            if (off >= 0) { // advance
                uintptr_t parentAddress = (uintptr_t) current + off;
                Pointer p = (Pointer) *reinterpret_cast<Pointer *>(parentAddress);
                if (p != NULL && !determineBlock(p)->isMarked()) {
                    Pointer parent = (Pointer) parentAddress;
                    printf("Parent: %p\n", parent);
                    parent = (Pointer) ((uintptr_t) prev);      //Not working
                    prev = (Pointer) ((uintptr_t) current);
                    current = (Pointer) ((uintptr_t) p);
                    determineBlock(current)->setMarked(true);

                    printf("Mark Block: %p \n", determineBlock(current));
                    printf("Mark Tag: %p \n", determineBlock(current)->tag);
                }
            } else { // off < 0: retreat
                //printf("Tag: %p\n", determineBlock(current)->tag);
                determineBlock(current)->tag = (Tag) ((uintptr_t) determineBlock(current)->tag + off); // restore tag
                printf("Restored Tag: %p\n", determineBlock(current)->tag);
                if (prev == NULL) {
                    return;
                }
                Pointer p = (Pointer) ((uintptr_t) current);
                current = (Pointer) ((uintptr_t) prev);
                off = *reinterpret_cast<int *>((uintptr_t) determineBlock(current)->tag - 1);
                printf("Offset: %d \n", off);
                uintptr_t parentAddress = (uintptr_t) current + off;
                Pointer prev = (Pointer) parentAddress;                 // Now working
                Pointer parent = (Pointer) parentAddress;
                printf("Parent: %p\n", parent);
                parent = (Pointer) ((uintptr_t) p);
            }
        }
    }

    static Pointer determinePointer(Block *block) {
        return (Pointer) block + OFFSET_DATA;
    }

    static Block *determineBlock(Pointer pointer) {
        return (Block *) ((uintptr_t) pointer - OFFSET_DATA);
    }
};

Heap::TypeDescriptorMap Heap::descriptors = [] {
    TypeDescriptorMap ret;
    return ret;
}();

Block *Heap::free = Heap::createBlock((byte *) malloc(32 * 1024 * sizeof(byte)), 32 * 1024);

#endif //GARBAGECOLLECTOR_HEAP_H
