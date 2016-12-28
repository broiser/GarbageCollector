//
// Created by prolog on 09.12.16.
//

#ifndef GARBAGECOLLECTOR_HEAP_H
#define GARBAGECOLLECTOR_HEAP_H

#include "descriptors/typeDescriptor.h"
#include "descriptors/dummyDescriptor.h"
#include "block.h"
#include <string>
#include <map>
#include <malloc.h>

using namespace std;

class Heap {
    using TypeDescriptorMap = map<string, TypeDescriptor *>;
public:
    static void gc(Pointer *pointers) {
        for (int index = 0; pointers[index] != NULL; index++) {
            mark(pointers[index]);
        }
    }

    static Pointer alloc(string name) {
        TypeDescriptor *typeDescriptor = descriptors[name];
        Block *allocBlock = alloc(typeDescriptor);
        return allocBlock->data;
    }

    static void registered(string name, TypeDescriptor *typeDescriptor) {
        descriptors[name] = typeDescriptor;
    }

private:
    static TypeDescriptorMap descriptors;
    static Block *free;

    static Block *createBlock(byte *data, int len) {
        Block *block = (Block *) data;
        block->len = len;
        block->next = block;
        block->initData();
        block->tag = new DummyDescriptor();
        block->setFree(true);
        return block;
    }

    static Block *alloc(TypeDescriptor *typeDescriptor) {
        int size = typeDescriptor->objSize;
        Block *start = free;
        Block *prev = free;
        free = free->next;
        while (free->len < size + 4 && free != start) {
            prev = free;
            free = free->next;
        }
        if (free->len < size + 4) {
            throw new bad_alloc;
        } else {
            Block *p = free;
            int newLen = p->len - (size + 4);
            if (newLen >= 8) { // split block
                p = (Block *) ((uintptr_t) p - 4 + p->len - size); // add new block with pointer arithmetic
                p->len = size + 4;
                free->len = newLen;
            } else if (free == prev) { // last free block
                free = NULL;
            } else { // remove block from list
                prev->next = free->next;
                free = prev;
            }
            //Set all data bytes in block p to 0
            p->initData();
            p->tag = typeDescriptor;
            p->setFree(false);
            return p;
        }
    }

    static void mark(Pointer pointer) {
        printf("%p \n", pointer);
    }
};

Heap::TypeDescriptorMap Heap::descriptors = [] {
    TypeDescriptorMap ret;
    return ret;
}();

Block *Heap::free = Heap::createBlock((byte *) calloc(32 * 1024, sizeof(byte)), 32 * 1024);

#endif //GARBAGECOLLECTOR_HEAP_H
