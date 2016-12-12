//
// Created by prolog on 11.12.16.
//

#ifndef GARBAGECOLLECTOR_BLOCK_H
#define GARBAGECOLLECTOR_BLOCK_H

#include "descriptors/typeDescriptor.h"

using byte = unsigned char;

class Block {
public:
    int *tag;
    int len;
    Block *next;
    byte *data;


    bool isFree() {
        return ((*tag) & (1 << (1))) == (1 << (1));
    }

    bool isMarked() {
        return ((*tag) & (1 << (0))) == (1 << (0));
    }

    void setFree(bool free) {
        if (free) {
            *tag = *tag | 1 << 1;
        } else {
            *tag = *tag & ~(1 << 1);
        }
    }

    void setMarked(bool marked) {
        if (marked) {
            *tag = *tag | 1 << 0;
        } else {
            *tag = *tag & ~(1 << 0);
        }
    }
};

#endif //GARBAGECOLLECTOR_BLOCK_H
