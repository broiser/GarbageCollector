//
// Created by prolog on 09.12.16.
//

#ifndef GARBAGECOLLECTOR_STUDENTLISTDESCRIPTOR_H
#define GARBAGECOLLECTOR_STUDENTLISTDESCRIPTOR_H

#include "typeDescriptor.h"

class StudentListDescriptor : public TypeDescriptor {
public:
    StudentListDescriptor() : TypeDescriptor(4) {
        pointers = new int[2];
        pointers[0] = 0;
        pointers[1] = -0;
    }
};


#endif //GARBAGECOLLECTOR_STUDENTLISTDESCRIPTOR_H
