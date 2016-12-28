//
// Created by prolog on 11.12.16.
//

#ifndef GARBAGECOLLECTOR_BLOCK_H
#define GARBAGECOLLECTOR_BLOCK_H

#include "descriptors/typeDescriptor.h"

#define OFFSET_TAG 0
#define OFFSET_LENGTH 4
#define OFFSET_NEXT 8
#define OFFSET_DATA 12

using byte = unsigned char;
using Pointer = byte *;

class Block {
public:
    TypeDescriptor *tag;
    int len;
    Block *next;
    Pointer data;

    bool isFree() {
        return (((uintptr_t) tag) & 2) == 2;
    }

    void setFree(bool free) {
        uintptr_t address = (uintptr_t) tag;
        if (free) {
            address = address | (1 << 1);
        } else {
            address = address & ~(1 << 1);
        }
        tag = (TypeDescriptor *) address;
    }

    bool isMarked() {
        return (((uintptr_t) tag) & 1) == 1;
    }

    void setMarked(bool marked) {
        uintptr_t address = (uintptr_t) tag;
        if (marked) {
            address = address | (1 << 0);
        } else {
            address = address & ~(1 << 0);
        }
        tag = (TypeDescriptor *) address;
        TypeDescriptor *desc = getTypeDescriptor();
    }

    TypeDescriptor* getTypeDescriptor() {
        uintptr_t address = (uintptr_t) tag;
        uintptr_t typeDescriptorAddress = address & -4;
        return (TypeDescriptor *) typeDescriptorAddress;
    }
};

#endif //GARBAGECOLLECTOR_BLOCK_H
