#include <stdlib.h>
#include "descriptors/studentListDescriptor.h"
#include "descriptors/studentNodeDescriptor.h"
#include "descriptors/studentDescriptor.h"
#include "descriptors/lectureNodeDescriptor.h"
#include "descriptors/lectrueDescriptor.h"
#include "descriptors/stringDescriptor.h"

#include "entities/studentList.h"
#include "entities/studentNode.h"
#include "entities/student.h"
#include "entities/lectureNode.h"
#include "entities/lecture.h"

#include "heap.h"
#include "stdlib.h"

StudentNodeDescriptor * createStudentNodeDescriptor();

StudentDescriptor * createStudentDescriptor();

int main() {
    //StudentListDescriptor *studentListDescriptor = new StudentListDescriptor();
    //StudentNodeDescriptor *studentNodeDescriptor = new StudentNodeDescriptor();
    //StudentDescriptor *studentDescriptor = new StudentDescriptor();
    //LectureNodeDescriptor *lectureNodeDescriptor = new LectureNodeDescriptor();
    //LectureDescriptor *lectureDescriptor = new LectureDescriptor();
    //StringDescriptor *stringDescriptor = new StringDescriptor();

    //Heap::registered("String", stringDescriptor);
    //Heap::registered("StudentList", studentListDescriptor);
    Heap::registered("Student", createStudentDescriptor());
    Heap::registered("StudentNode", createStudentNodeDescriptor());

    //Heap::registered("LectureNode", lectureNodeDescriptor);
    //Heap::registered("Lecture", lectureDescriptor);

    //StudentList *studentList = (StudentList *) Heap::alloc("StudentList");
    Student * student = (Student *) Heap::alloc("Student");
    StudentNode *studentNode = (StudentNode *) Heap::alloc("StudentNode");
    studentNode->stud = student;
    //studentNode->stud->name = (string *) Heap::alloc("String");;
   // studentList->add(studentNode);

    Pointer roots[2];
    roots[0] = (byte *) studentNode;
    roots[1] = NULL;

    Heap::gc(roots);

    return 0;
}

StudentNodeDescriptor * createStudentNodeDescriptor(){
    int* descriptor = new int[4];
    descriptor[0] = 16;
    descriptor[1] = 0;
    descriptor[2] = 8;
    descriptor[3] = -12;
    return (StudentNodeDescriptor * )descriptor;
}

StudentDescriptor * createStudentDescriptor(){
    int* descriptor = new int[4];
    descriptor[0] = 20;
    descriptor[1] = 4;
    descriptor[2] = 12;
    descriptor[3] = -12;
    return (StudentDescriptor * )descriptor;
}
