//
// Created by prolog on 09.12.16.
//

#ifndef GARBAGECOLLECTOR_STUDENTLIST_H
#define GARBAGECOLLECTOR_STUDENTLIST_H

#include "studentNode.h"

class StudentList {

public:
    StudentNode *first = NULL;

    void add(Student student) {
        if (first == NULL) {
            first = new StudentNode(student);
        } else {
            StudentNode *current = first;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = new StudentNode(student);
        }
    }

    void remove(Student student) {
        if (first == NULL) {
            return;
        } else if (first->stud.id == student.id) {
            first = first->next;
        } else {
            StudentNode *current = (first)->next;
            StudentNode *previous = first;
            while (current != NULL && previous != NULL) {
                if (current->stud.id == student.id) {
                    previous->next = current->next;
                    return;
                }
                previous = current;
                current = current->next;
            }
        }
    }
};

#endif //GARBAGECOLLECTOR_STUDENTLIST_H
