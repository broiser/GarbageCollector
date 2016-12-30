#include "descriptors/typeDescriptorGenerator.h"

#include "entities/studentList.h"

#include "heap.h"

int main() {
    TypeDescriptor *studentDescriptor = TypeDescriptorGenerator::createStudentDescriptor();
    TypeDescriptor *studentNodeDescriptor = TypeDescriptorGenerator::createStudentNodeDescriptor();
    TypeDescriptor *studentListDescriptor = TypeDescriptorGenerator::createStudentListDescriptor();
    TypeDescriptor *lectureDescriptor = TypeDescriptorGenerator::createLectureDescriptor();
    TypeDescriptor *lectureNodeDescriptor = TypeDescriptorGenerator::createLectureNodeDescriptor();

    //StringDescriptor *stringDescriptor = new StringDescriptor();

    //Heap::registered("String", stringDescriptor);

    Heap::registered("Student", studentDescriptor);
    Heap::registered("StudentNode", studentNodeDescriptor);
    Heap::registered("StudentList", studentListDescriptor);

    //Heap::registered("LectureNode", lectureNodeDescriptor);
    //Heap::registered("Lecture", lectureDescriptor);

    StudentList *studentList = (StudentList *) Heap::alloc("StudentList");
    //Student *student = (Student *) Heap::alloc("Student");
    StudentNode *studentNode = (StudentNode *) Heap::alloc("StudentNode");
    //studentNode->stud = student;
    //studentNode->stud->name = (string *) Heap::alloc("String");;
    studentList->add(studentNode);

    Pointer roots[2];
    roots[0] = (byte *) studentList;
    roots[1] = NULL;

    Heap::gc(roots);

    return 0;
}


