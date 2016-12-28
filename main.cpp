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

int main() {
    StudentListDescriptor *studentListDescriptor = new StudentListDescriptor();
    StudentNodeDescriptor *studentNodeDescriptor = new StudentNodeDescriptor();
    StudentDescriptor *studentDescriptor = new StudentDescriptor();
    LectureNodeDescriptor *lectureNodeDescriptor = new LectureNodeDescriptor();
    LectureDescriptor *lectureDescriptor = new LectureDescriptor();
    StringDescriptor *stringDescriptor = new StringDescriptor();

    Heap::registered("String", stringDescriptor);
    Heap::registered("StudentList", studentListDescriptor);
    Heap::registered("StudentNode", studentNodeDescriptor);
    Heap::registered("Student", studentDescriptor);
    Heap::registered("LectureNode", lectureNodeDescriptor);
    Heap::registered("Lecture", lectureDescriptor);

    StudentList *studentList = (StudentList *) Heap::alloc("StudentList");
    StudentNode *studentNode = (StudentNode *) Heap::alloc("StudentNode");
    studentNode->stud = (Student *) Heap::alloc("Student");
    studentNode->stud->name = (string *) Heap::alloc("String");
    studentList->add(studentNode);

    Pointer roots[2];
    roots[0] = (byte *) studentList;
    roots[1] = NULL;

    Heap::gc(roots);

    return 0;
}
