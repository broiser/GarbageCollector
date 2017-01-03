//
// Created by prolog on 09.12.16.
//

#ifndef GARBAGECOLLECTOR_TYPEDESCRIPTOR_H
#define GARBAGECOLLECTOR_TYPEDESCRIPTOR_H

#include "string"

using namespace std;

class TypeDescriptor {
public:
//    string typeName;
    int objSize;
    int *pointers;
};

#endif //GARBAGECOLLECTOR_TYPEDESCRIPTOR_H
