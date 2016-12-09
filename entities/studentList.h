//
// Created by prolog on 09.12.16.
//

#ifndef GARBAGECOLLECTOR_STUDENTLIST_H
#define GARBAGECOLLECTOR_STUDENTLIST_H

#include "StudNode.h"

class StudentList {

public:
    StudNode *first = NULL;

    void add(Student student) {
        if (first == NULL) {
            first = new StudNode(student);
        } else {
            StudNode *current = first;
            while (current->next == NULL) {
                current = current->next;
            }
            current->next = new StudNode(student);
        }
    }

    void remove(Student student) {
        // TODO
    }
};

#endif //GARBAGECOLLECTOR_STUDENTLIST_H
