#include "descriptors/typeDescriptorGenerator.h"
#include "entities/studentList.h"
#include "heap.h"

int main() {
    TypeDescriptor *studentDescriptor = TypeDescriptorGenerator::createStudentDescriptor();
    TypeDescriptor *studentNodeDescriptor = TypeDescriptorGenerator::createStudentNodeDescriptor();
    TypeDescriptor *studentListDescriptor = TypeDescriptorGenerator::createStudentListDescriptor();

    TypeDescriptor *lectureDescriptor = TypeDescriptorGenerator::createLectureDescriptor();
    TypeDescriptor *lectureNodeDescriptor = TypeDescriptorGenerator::createLectureNodeDescriptor();

    Heap::registered("Student", studentDescriptor);
    Heap::registered("StudentNode", studentNodeDescriptor);
    Heap::registered("StudentList", studentListDescriptor);

    Heap::registered("Lecture", lectureDescriptor);
    Heap::registered("LectureNode", lectureNodeDescriptor);

    StudentList *studentList = (StudentList *) Heap::alloc("StudentList");
    StudentNode *studentNode = (StudentNode *) Heap::alloc("StudentNode");
    //studentNode->stud = (Student *) Heap::alloc("Student");
    studentList->add(studentNode);

    Pointer roots[2];
    roots[0] = (Pointer) studentList;
    roots[1] = NULL;

    Heap::gc(roots);

    return 0;
}


