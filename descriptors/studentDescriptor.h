//
// Created by prolog on 09.12.16.
//

#ifndef GARBAGECOLLECTOR_STUDENTDESCRIPTOR_H
#define GARBAGECOLLECTOR_STUDENTDESCRIPTOR_H

#include "typeDescriptor.h"

class StudentDescriptor : public TypeDescriptor {
public:
    StudentDescriptor() : TypeDescriptor(12) {
        pointers = new int[3];
        pointers[0] = 4;
        pointers[1] = 8;
        pointers[2] = -8;
    }
};

#endif //GARBAGECOLLECTOR_STUDENTDESCRIPTOR_H