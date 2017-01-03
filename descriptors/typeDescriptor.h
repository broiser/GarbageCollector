//
// Created by prolog on 09.12.16.
//

#ifndef GARBAGECOLLECTOR_TYPEDESCRIPTOR_H
#define GARBAGECOLLECTOR_TYPEDESCRIPTOR_H

#include "string"

using namespace std;

class TypeDescriptor {
public:
    int objSize;
//    char *typeName;
    int *pointers;
};

#endif //GARBAGECOLLECTOR_TYPEDESCRIPTOR_H
