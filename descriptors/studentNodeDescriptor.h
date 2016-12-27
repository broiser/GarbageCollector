//
// Created by prolog on 09.12.16.
//

#ifndef GARBAGECOLLECTOR_STUDENTNODEDESCRIPTOR_H
#define GARBAGECOLLECTOR_STUDENTNODEDESCRIPTOR_H

#include "typeDescriptor.h"

class StudentNodeDescriptor : public TypeDescriptor {
public:
    StudentNodeDescriptor() : TypeDescriptor(8) {
        pointers = new int[3];
        pointers[0] = 0;
        pointers[1] = 4;
        pointers[2] = -12;
    }
};

#endif //GARBAGECOLLECTOR_STUDENTNODEDESCRIPTOR_H
