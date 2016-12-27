//
// Created by Jürgen Ratzenböck on 27/12/2016.
//


#ifndef GARBAGECOLLECTOR_LECTRUEDESCRIPTOR_H
#define GARBAGECOLLECTOR_LECTRUEDESCRIPTOR_H

#include "typeDescriptor.h"

class StringDescriptor : public TypeDescriptor {
public:
    StringDescriptor() : TypeDescriptor(8) {
        pointers = new int[1];
        pointers[0] = -4;
    }
};

#endif //GARBAGECOLLECTOR_LECTRUEDESCRIPTOR_H
