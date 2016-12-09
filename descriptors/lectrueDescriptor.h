//
// Created by prolog on 09.12.16.
//

#ifndef GARBAGECOLLECTOR_LECTRUEDESCRIPTOR_H
#define GARBAGECOLLECTOR_LECTRUEDESCRIPTOR_H

#include "typeDescriptor.h"

class LectureDescriptor : public TypeDescriptor {
public:
    LectureDescriptor() : TypeDescriptor(12) {
        pointers = new int[2];
        pointers[0] = 4;
        pointers[1] = -4;
    }
};

#endif //GARBAGECOLLECTOR_LECTRUEDESCRIPTOR_H
