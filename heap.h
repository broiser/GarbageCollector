//
// Created by prolog on 09.12.16.
//

#ifndef GARBAGECOLLECTOR_HEAP_H
#define GARBAGECOLLECTOR_HEAP_H

#include "descriptors/typeDescriptor.h"
#include "descriptors/dummyDescriptor.h"
#include "block.h"

#include <stdlib.h>
#include <string>
#include <map>


using namespace std;

class Heap {
    using TypeDescriptorMap = map<string, TypeDescriptor *>;
public:
    static void gc(Pointer pointers[]) {
        for (int index = 0; pointers[index] != NULL; index++) {
            Pointer pointer = pointers[index];
            mark((Block *) ((uintptr_t) pointer - OFFSET_DATA));
        }
    }

    static Pointer alloc(string name) {
        TypeDescriptor *typeDescriptor = descriptors[name];
        Block *allocBlock = alloc(typeDescriptor);
        printf("Alloc: %p \n", allocBlock);
        return (Pointer) ((uintptr_t) allocBlock + OFFSET_DATA);
    }

    static void registered(string name, TypeDescriptor *typeDescriptor) {
        descriptors[name] = typeDescriptor;
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
            initData((byte *) &p->data, size - OFFSET_DATA);
            p->tag = typeDescriptor;
            p->setFree(false);
            return p;
        }
    }

    // TODO
    static void mark(Block *current) {
        printf("Mark: %p \n", current);
        Block *prev = NULL;
        current->setMarked(true);
        for (;;) {
            current->tag = current->getTypeDescriptor();
            current->tag = current->tag + 4;
            uintptr_t currentAddress = (uintptr_t) current->tag;
            int off = *reinterpret_cast<int *>(currentAddress);
            printf("Offset: %d \n", off);
            if (off >= 0) { // advance
                uintptr_t parentAddress = ((uintptr_t) current) + off;
                Block *p = (Block *) parentAddress;
                if (p != NULL && !p->isMarked()) {
                    p = prev;
                    prev = current;
                    current = p;
                    current->setMarked(true);
                }
            } else { // off < 0: retreat
                current->tag = current->tag + off; // restore tag
                if (prev == NULL) {
                    return;
                }
                Block *p = current;
                current = prev;
                uintptr_t currentAddress = (uintptr_t) current->tag;
                off = *reinterpret_cast<int *>(currentAddress);
                uintptr_t parentAddress = ((uintptr_t) current) + off;
                prev = (Block *) parentAddress;
            }
        }
    }
};

Heap::TypeDescriptorMap Heap::descriptors = [] {
    TypeDescriptorMap ret;
    return ret;
}();

Block *Heap::free = Heap::createBlock((byte *) calloc(32 * 1024, sizeof(byte)), 32 * 1024);

#endif //GARBAGECOLLECTOR_HEAP_H
