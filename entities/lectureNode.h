//
// Created by prolog on 09.12.16.
//

#ifndef GARBAGECOLLECTOR_LECTNODE_H
#define GARBAGECOLLECTOR_LECTNODE_H

#include "lecture.h"

class LectureNode {
public:
    LectureNode *next = NULL;
    Lecture *lect;
};

#endif //GARBAGECOLLECTOR_LECTNODE_H
