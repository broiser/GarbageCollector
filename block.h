//
// Created by prolog on 11.12.16.
//

#ifndef GARBAGECOLLECTOR_BLOCK_H
#define GARBAGECOLLECTOR_BLOCK_H

#include "descriptors/typeDescriptor.h"

using byte = unsigned char;

class Block {
public:
    TypeDescriptor *descriptor;
    int size;
    byte *data;
};

#endif //GARBAGECOLLECTOR_BLOCK_H
