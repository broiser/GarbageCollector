//
// Created by prolog on 09.12.16.
//

#ifndef GARBAGECOLLECTOR_STUDENTLIST_H
#define GARBAGECOLLECTOR_STUDENTLIST_H

#include "studentNode.h"

class StudentList {
private:
    bool equalStudent(StudentNode *studentNode1, StudentNode *studentNode2) {
        return studentNode1->stud->id == studentNode2->stud->id;
    }
public:
    StudentNode *first = NULL;

    void add(StudentNode *studentNode) {
        if (first == NULL) {
            first = studentNode;
        } else {
            StudentNode *current = first;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = studentNode;
        }
    }

    void remove(StudentNode *studentNode) {
        if (first == NULL) {
            return;
        } else if (equalStudent(first, studentNode)) {
            first = first->next;
        } else {
            StudentNode *current = (first)->next;
            StudentNode *previous = first;
            while (current != NULL && previous != NULL) {
                if (equalStudent(current, studentNode)) {
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
