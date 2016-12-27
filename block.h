//
// Created by prolog on 11.12.16.
//

#ifndef GARBAGECOLLECTOR_BLOCK_H
#define GARBAGECOLLECTOR_BLOCK_H

#include "descriptors/typeDescriptor.h"

using byte = unsigned char;

class Block {
public:
    TypeDescriptor *tag;
    int len;
    Block *next;
    byte *data;

    void initData() {
        data = new byte[len];
        for (int i = 0; i < len; i++) {
            *(data + i) = 0;
        }
    }

    bool isFree() {
        uintptr_t address = (uintptr_t) tag;
        return ((address) & 2) == 2;
    }

    bool isMarked() {
        uintptr_t address = (uintptr_t) tag;
        return ((address) & 1) == 1;
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
