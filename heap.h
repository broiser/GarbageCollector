//
// Created by prolog on 09.12.16.
//

#ifndef GARBAGECOLLECTOR_HEAP_H
#define GARBAGECOLLECTOR_HEAP_H

#include "descriptors/typeDescriptor.h"
#include "block.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <map>

using namespace std;
using Tag = TypeDescriptor *;

class Heap {
    using TypeDescriptorMap = map<char *, TypeDescriptor *>;
public:
    static void gc(Pointer pointers[]) {
        for (int index = 0; pointers[index] != NULL; index++) {
            mark(pointers[index]);
        }
        sweep();
    }

    static Pointer alloc(char *name) {
        TypeDescriptor *typeDescriptor = descriptors[name];
        Block *allocBlock = alloc(typeDescriptor);
        allocBlock->type = name;
        return determinePointer(allocBlock);
    }

    static void registered(char *name, TypeDescriptor *typeDescriptor) {
//        typeDescriptor->typeName = name;
        descriptors[name] = typeDescriptor;
    }

    static void dump() {
        dumpLiveObjects();
        dumpFreeList();
    }

private:
    static uintptr_t heapStart, heapEnd;
    static TypeDescriptorMap descriptors;
    static Block *free;

    static Block *createBlock(int size) {
        byte *data = (byte *) calloc(size, sizeof(byte));
        initData(data, size);
        Block *block = (Block *) data;
        block->len = size;
        block->next = block;
        block->tag = 0;
        block->setFree(true);
        return block;
    }

    static void initData(byte *data, int length) {
        memset(data, 0, length);
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
            //Set all data bytes in block p to 0
            initData(determinePointer(p), size - OFFSET_DATA);
            p->tag = typeDescriptor;
            p->setFree(false);
            return p;
        }
    }

    static void mark(Pointer current) {
        determineBlock(current)->setMarked(true);
        Pointer prev = NULL;

        for (;;) {
            determineBlock(current)->tag = (Tag) ((uintptr_t) determineBlock(current)->tag + 4);
            Block *block = determineBlock(current);
            int off = *reinterpret_cast<int *>((uintptr_t) determineBlock(current)->tag - 1);
            if (off >= 0) { // advance
                uintptr_t parentAddress = (uintptr_t) current + off;
                Pointer p = (Pointer) *reinterpret_cast<Pointer *>(parentAddress);
                if (p != NULL && !determineBlock(p)->isMarked()) {
                    Pointer *parent = (Pointer *) parentAddress;
                    *parent = prev;
                    //memset(parent, *prev, 8);
                    prev = current;
                    current = p;
                    determineBlock(current)->setMarked(true);
                }
            } else { // off < 0: retreat
                determineBlock(current)->tag = (Tag) ((uintptr_t) determineBlock(current)->tag + off); // restore tag
                if (prev == NULL) {
                    return;
                }
                Pointer p = current;
                current = prev;
                off = *reinterpret_cast<int *>((uintptr_t) determineBlock(current)->tag - 1);
                uintptr_t parentAddress = (uintptr_t) current + off;
                prev = *((Pointer *) parentAddress);          // Now working
                Pointer *parent = (Pointer *) parentAddress;
                *parent = p;
            }
        }
    }

    static void sweep() {
        Pointer p = determinePointer((Block *) heapStart);
        free = NULL;
        while ((uintptr_t) p < heapEnd) {
            if (determineBlock(p)->isMarked()) {
                determineBlock(p)->setMarked(false);
            } else { // free: collect p
                int size = determineBlock(p)->len;
                Pointer q = (Pointer) (uintptr_t) p + size;
                while ((uintptr_t) q < heapEnd && !determineBlock(q)->isMarked()) {
                    size += determineBlock(q)->len; // merge
                    q = (Pointer) (uintptr_t) q + determineBlock(q)->len;
                }
                determineBlock(p)->tag = (Tag) p;
                determineBlock(p)->len = size;
                determineBlock(p)->next = free;
                determineBlock(p)->setFree(true);
                free = (Block *) (uintptr_t) p;
            }
            p += (uintptr_t) determineBlock(p)->len;
        }
    }

    static Pointer determinePointer(Block *block) {
        return (Pointer) block + OFFSET_DATA;
    }

    static Block *determineBlock(Pointer pointer) {
        return (Block *) ((uintptr_t) pointer - OFFSET_DATA);
    }

    static void dumpLiveObjects() {
        printf("List of all live objects\n");
        printf("------------------------\n");
        Pointer p = determinePointer((Block *) heapStart);
        int totalMemory = 0;
        for (int i = 1; (uintptr_t) p < heapEnd;) {
            Block *currentBlock = (Block *) determineBlock(p);
            if (!currentBlock->isFree()) {
                totalMemory += currentBlock->len;
                printf("Object %d\n-----------\n", i);
                printf("Type name: %s \n", currentBlock->type);
                printf("Block address: %p \n", currentBlock);
                printf("Data address: %p \n", p);
                printf("Data (first 4 bytes): ");
                for (int i = 0; i < 4; i++) {
                    printf("%b", *(p + i));
                }
                printf("\nPointers: ");
                int *pointers = ((int *) ((uintptr_t) currentBlock->getTypeDescriptor() + 4));
                int off = *reinterpret_cast<int *>((uintptr_t) pointers);
                for (int index = 0; *(pointers + index) >= 0; index++) {
                    printf("%d ", *(pointers + index));
                }
                i++;
                printf("\n");
            }
            p += (uintptr_t) currentBlock->len;
        }
        printf("----------------\nTotal amount of used memory: %d bytes \n\n", totalMemory);
    }

    static void dumpFreeList() {
        printf("Freelist\n");
        printf("------------------------\n");
        Pointer p = determinePointer((Block *) heapStart);
        int totalFreeMemory = 0;
        for (int i = 1; (uintptr_t) p < heapEnd;) {
            Block *currentBlock = (Block *) determineBlock(p);
            if (currentBlock->isFree()) {
                totalFreeMemory += currentBlock->len;
                printf("Block %d\n-----------\n", i);
                printf("Block address: %p \n", currentBlock);
                printf("Length of block: %d bytes \n", currentBlock->len);
                i++;
            }
            p += (uintptr_t) currentBlock->len;
        }
        printf("----------------\nTotal amount of free memory: %d bytes \n\n", totalFreeMemory);
    }

};

Heap::TypeDescriptorMap Heap::descriptors = [] {
    TypeDescriptorMap ret;
    return ret;
}();

Block *Heap::free = Heap::createBlock(32 * 1024);
uintptr_t Heap::heapEnd = (uintptr_t) Heap::free + (32 * 1024);
uintptr_t Heap::heapStart = (uintptr_t) Heap::free;

#endif //GARBAGECOLLECTOR_HEAP_H
