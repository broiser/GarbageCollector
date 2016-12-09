//
// Created by prolog on 09.12.16.
//

#ifndef GARBAGECOLLECTOR_HEAP_H
#define GARBAGECOLLECTOR_HEAP_H

#include "descriptors/typeDescriptor.h"
#include <string>
#include <map>

using namespace std;
using byte = unsigned char;

class Block {
public:
    TypeDescriptor *descriptor;
    int size;
    byte *data;
};

class Heap {
    using TypeDescriptorMap = map<string, TypeDescriptor *>;
public:
    static byte *alloc(string name) {
        TypeDescriptor *typeDescriptor = descriptors[name];
        Block *allocBlock = alloc(typeDescriptor->objSize);
        return allocBlock->data;
    }

    static void registered(string name, TypeDescriptor *typeDescriptor) {
        descriptors[name] = typeDescriptor;
    }

private:
    static TypeDescriptorMap descriptors;

    static Block *alloc(int size) {
        return new Block();
    }
};

Heap::TypeDescriptorMap Heap::descriptors = [] {
    TypeDescriptorMap ret;
    return ret;
}();

#endif //GARBAGECOLLECTOR_HEAP_H
