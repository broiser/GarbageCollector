//
// Created by prolog on 09.12.16.
//

#ifndef GARBAGECOLLECTOR_HEAP_H
#define GARBAGECOLLECTOR_HEAP_H

#include "descriptors/typeDescriptor.h"
#include "block.h"
#include <string>
#include <map>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Heap {
    using TypeDescriptorMap = map<string, TypeDescriptor *>;
public:
    static byte *alloc(string name) {
        TypeDescriptor *typeDescriptor = descriptors[name];
        Block *allocBlock = alloc(typeDescriptor->objSize);
        allocBlock->tag = (int *) &typeDescriptor;
        return allocBlock->data;
    }

    static void registered(string name, TypeDescriptor *typeDescriptor) {
        descriptors[name] = typeDescriptor;
    }

private:
    static TypeDescriptorMap descriptors;
    static Block *free;

    static Block *alloc(int size) {
        /*Block *start = free;
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
                p = createFreeBlock(p - 4 + p->len - size);
                p->len = size + 4;
                free->len = newLen;
            } else if (free == prev) { // last free block
                free = NULL;
            } else { // remove block from list
                prev->next = free->next;
                free = prev;
            }
            //Set all data bytes in block p to 0;
            //p->used = true;
        }*/
        return new Block();
    }
};

Heap::TypeDescriptorMap Heap::descriptors = [] {
    TypeDescriptorMap ret;
    return ret;
}();

Block *Heap::free = (Block *) calloc(32 * 1024, sizeof(byte));

#endif //GARBAGECOLLECTOR_HEAP_H
