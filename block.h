//
// Created by prolog on 11.12.16.
//

#ifndef GARBAGECOLLECTOR_BLOCK_H
#define GARBAGECOLLECTOR_BLOCK_H

#include "descriptors/typeDescriptor.h"

using byte = unsigned char;

class Block {
public:
    TypeDescriptor **tag;
    int len;
    Block *next;
    byte *data;

    void initData() {
        data = {};
    }

    bool isFree() {
        int *pointer = (int*) tag;
        return ((*pointer) & 2) == 2;
    }

    bool isMarked() {
        int *pointer = (int*) tag;
        return ((*pointer) & 1) == 1;
    }

    void setFree(bool free) {
        int *address = (int*) tag;
        if (free) {
            *address = *address | (1 << 1);
        } else {
            *address = *address & ~(1 << 1);
        }
    }

    void setMarked(bool marked) {
        int *address = (int*) tag;
        if (marked) {
            *address = *address | (1 << 0);
        } else {
            *address = *address & ~(1 << 0);
        }
    }
};

#endif //GARBAGECOLLECTOR_BLOCK_H
