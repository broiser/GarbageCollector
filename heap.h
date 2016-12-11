//
// Created by prolog on 09.12.16.
//

#ifndef GARBAGECOLLECTOR_HEAP_H
#define GARBAGECOLLECTOR_HEAP_H

#include "descriptors/typeDescriptor.h"
#include "block.h"
#include <string>
#include <map>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Heap {
    using TypeDescriptorMap = map<string, TypeDescriptor *>;
public:
    static byte *alloc(string name) {
        TypeDescriptor *typeDescriptor = descriptors[name];
        Block *allocBlock = alloc(typeDescriptor->objSize);
        allocBlock->descriptor = typeDescriptor;
        return allocBlock->data;
    }

    static void registered(string name, TypeDescriptor *typeDescriptor) {
        descriptors[name] = typeDescriptor;
    }

private:
    static TypeDescriptorMap descriptors;
    static Block *free;

    static Block *alloc(int size) {
        return new Block();
    }
};

Heap::TypeDescriptorMap Heap::descriptors = [] {
    TypeDescriptorMap ret;
    return ret;
}();

Block *Heap::free = (Block *) calloc(32 * 1024, sizeof(byte));

#endif //GARBAGECOLLECTOR_HEAP_H
