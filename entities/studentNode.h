//
// Created by prolog on 09.12.16.
//

#ifndef GARBAGECOLLECTOR_STUDNODE_H
#define GARBAGECOLLECTOR_STUDNODE_H

#include "student.h"

class StudentNode {
public:
    StudentNode *next = NULL;
    Student *stud;

    StudentNode(Student *student) {
        stud = student;
    }
};


#endif //GARBAGECOLLECTOR_STUDNODE_H
