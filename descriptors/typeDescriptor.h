//
// Created by prolog on 09.12.16.
//

#ifndef GARBAGECOLLECTOR_TYPEDESCRIPTOR_H
#define GARBAGECOLLECTOR_TYPEDESCRIPTOR_H

#define TAG_LENGTH 0

class TypeDescriptor {
public:
    int objSize;
    int *pointers;

    TypeDescriptor(int size){
        objSize = size + TAG_LENGTH;
    };
};

#endif //GARBAGECOLLECTOR_TYPEDESCRIPTOR_H
