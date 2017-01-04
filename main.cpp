#include "descriptors/typeDescriptorGenerator.h"
#include "entities/studentList.h"
#include "heap.h"

int main() {
    TypeDescriptor *studentDescriptor = TypeDescriptorGenerator::createStudentDescriptor();
    TypeDescriptor *studentNodeDescriptor = TypeDescriptorGenerator::createStudentNodeDescriptor();
    TypeDescriptor *studentListDescriptor = TypeDescriptorGenerator::createStudentListDescriptor();

    TypeDescriptor *lectureDescriptor = TypeDescriptorGenerator::createLectureDescriptor();
    TypeDescriptor *lectureNodeDescriptor = TypeDescriptorGenerator::createLectureNodeDescriptor();

    char studentType[32] = "Student";
    char studentNodeType[32] = "StudentNode";
    char studentListType[32] = "StudentList";
    char lectureType[32] = "Lecture";
    char lectureNodeType[32] = "LectureNode";

    Heap::registered(studentType, studentDescriptor);
    Heap::registered(studentNodeType, studentNodeDescriptor);
    Heap::registered(studentListType, studentListDescriptor);
    Heap::registered(lectureType, lectureDescriptor);
    Heap::registered(lectureNodeType, lectureNodeDescriptor);

    StudentList *studentList = (StudentList *) Heap::alloc(studentListType);
    StudentNode *studentNode = (StudentNode *) Heap::alloc(studentNodeType);
    Student *student = (Student *) Heap::alloc(studentType);
    LectureNode *lectureNode1 = (LectureNode *) Heap::alloc(lectureNodeType);
    Lecture *lecture1 = (Lecture *) Heap::alloc(lectureType);

    LectureNode *lectureNode2 = (LectureNode*) Heap::alloc(lectureNodeType);
    Lecture *lecture2 = (Lecture *) Heap::alloc(lectureType);

    studentNode->stud = student;
    studentNode->stud->id = 1;
    studentNode->stud->name = "Jürgen";

    lectureNode1->lect = lecture1;
    lectureNode1->lect->id = 1;
    lectureNode1->lect->name = "System Software";
    lectureNode1->lect->semester = 9;

//    lectureNode2->lect = lecture2;
//    lectureNode2->lect->id = 2;
//    lectureNode2->lect->name = "Multimedia Search and Retrieval";
//    lectureNode2->lect->semester = 9;

    student->add(lectureNode1);
//    student->add(lectureNode2);

    studentList->add(studentNode);

    Pointer roots[2];
    roots[0] = (Pointer) studentList;
    roots[1] = NULL;

    printf("First run\n\n");
    Heap::gc(roots);
    Heap::dump();

    studentNode->stud = NULL;

    printf("Second run\n\n");
    Heap::gc(roots);
    Heap::dump();

    roots[0] = NULL;

    printf("Third run\n\n");
    Heap::gc(roots);

    Heap::dump();

    return 0;
}


