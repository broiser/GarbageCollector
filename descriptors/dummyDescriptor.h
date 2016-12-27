//
// Created by prolog on 12.12.16.
//

#ifndef GARBAGECOLLECTOR_DUMMYDESCRIPTOR_H
#define GARBAGECOLLECTOR_DUMMYDESCRIPTOR_H

#include "typeDescriptor.h"

class DummyDescriptor : public TypeDescriptor {
public:
    DummyDescriptor() : TypeDescriptor(8) {
        pointers = new int[1];
        pointers[0] = -4;
    }
};

#endif //GARBAGECOLLECTOR_DUMMYDESCRIPTOR_H
