//
// Created by prolog on 28.12.16.
//

#ifndef GARBAGECOLLECTOR_STRINGDESCRIPTOR_H
#define GARBAGECOLLECTOR_STRINGDESCRIPTOR_H

#include "typeDescriptor.h"

class StringDescriptor : public TypeDescriptor {
public:
    StringDescriptor() : TypeDescriptor(12) {
        pointers = new int[1];
        pointers[0] = -4;
    }
};

#endif //GARBAGECOLLECTOR_STRINGDESCRIPTOR_H
