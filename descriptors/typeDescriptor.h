//
// Created by prolog on 09.12.16.
//

#ifndef GARBAGECOLLECTOR_TYPEDESCRIPTOR_H
#define GARBAGECOLLECTOR_TYPEDESCRIPTOR_H

class TypeDescriptor {
public:
    int objSize;
    int *pointers;

    TypeDescriptor(int size){
        objSize = size;
    };
};

#endif //GARBAGECOLLECTOR_TYPEDESCRIPTOR_H
