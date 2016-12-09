//
// Created by prolog on 09.12.16.
//

#ifndef GARBAGECOLLECTOR_LECTURENODEDESCRIPTOR_H
#define GARBAGECOLLECTOR_LECTURENODEDESCRIPTOR_H

#include "typeDescriptor.h"

class LectureNodeDescriptor : public TypeDescriptor {
public:
    LectureNodeDescriptor() : TypeDescriptor(8) {
        pointers = new int[3];
        pointers[0] = 0;
        pointers[1] = 4;
        pointers[2] = -4;
    }
};

#endif //GARBAGECOLLECTOR_LECTURENODEDESCRIPTOR_H
