//
// Created by prolog on 09.12.16.
//

#ifndef GARBAGECOLLECTOR_STUDENT_H
#define GARBAGECOLLECTOR_STUDENT_H

#include "lectureNode.h"

class Student{
private:
    bool equalLecture(LectureNode *lectureNode1, LectureNode *lectureNode2) {
        return lectureNode1->lect->id == lectureNode2->lect->id;
    }
public:
    int id;
    string name;
    LectureNode *lect = NULL;

    Student(int id, string name, LectureNode *lect) {
        this->id = id;
        this->name = name;
        this->lect = lect;
    }

    void add(LectureNode *lectureNode){
        if (lect == NULL) {
            lect = lectureNode;
        } else {
            LectureNode *current = lect;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = lectureNode;
        }
    }

    void remove(LectureNode *lectureNode){
        if (lect == NULL) {
            return;
        } else if (equalLecture(lect, lectureNode)) {
            lect = lect->next;
        } else {
            LectureNode *current = lect->next;
            LectureNode *previous = lect;
            while (current != NULL && previous != NULL) {
                if (equalLecture(current, lectureNode)) {
                    previous->next = current->next;
                    return;
                }
                previous = current;
                current = current->next;
            }
        }
    }
};

#endif //GARBAGECOLLECTOR_STUDENT_H
