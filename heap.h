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
