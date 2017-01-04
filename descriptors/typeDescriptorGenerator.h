//
// Created by prolog on 30.12.16.
//

#ifndef GARBAGECOLLECTOR_TYPEDESCRIPTORGENERATOR_H
#define GARBAGECOLLECTOR_TYPEDESCRIPTORGENERATOR_H

#include "typeDescriptor.h"

class TypeDescriptorGenerator {
public :
    static TypeDescriptor *createStudentDescriptor() {
        int *descriptor = new int[3];
        descriptor[0] = 44;
        descriptor[1] = 0;
        descriptor[2] = -8;
        return (TypeDescriptor *) descriptor;
    }

    static TypeDescriptor *createStudentNodeDescriptor() {
        int *descriptor = new int[4];
        descriptor[0] = 16;
        descriptor[1] = 0;
        descriptor[2] = 8;
        descriptor[3] = -12;
        return (TypeDescriptor *) descriptor;
    }

    static TypeDescriptor *createStudentListDescriptor() {
        int *descriptor = new int[3];
        descriptor[0] = 8;
        descriptor[1] = 0;
        descriptor[2] = -8;
        return (TypeDescriptor *) descriptor;
    }

    static TypeDescriptor *createLectureDescriptor() {
        int *descriptor = new int[2];
        descriptor[0] = 40;
        descriptor[1] = -4;
        return (TypeDescriptor *) descriptor;
    }

    static TypeDescriptor *createLectureNodeDescriptor() {
        int *descriptor = new int[4];
        descriptor[0] = 16;
        descriptor[1] = 0;
        descriptor[2] = 8;
        descriptor[3] = -12;
        return (TypeDescriptor *) descriptor;
    }

};

#endif //GARBAGECOLLECTOR_TYPEDESCRIPTORGENERATOR_H
