//
// Created by prolog on 09.12.16.
//

#ifndef GARBAGECOLLECTOR_STUDNODE_H
#define GARBAGECOLLECTOR_STUDNODE_H

#include "student.h"

class StudNode {
public:
    StudNode *next = NULL;
    Student stud;

    StudNode(Student student) {
        stud = student;
    }
};


#endif //GARBAGECOLLECTOR_STUDNODE_H
