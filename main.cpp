#include "descriptors/studentListDescriptor.h"
#include "descriptors/studentNodeDescriptor.h"
#include "descriptors/studentDescriptor.h"
#include "descriptors/lectureNodeDescriptor.h"
#include "descriptors/lectrueDescriptor.h"

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

    Heap::registered("StudentList", studentListDescriptor);
    Heap::registered("StudentNode", studentNodeDescriptor);
    Heap::registered("Student", studentDescriptor);

    Heap::registered("LectureNode", lectureNodeDescriptor);
    Heap::registered("Lecture", lectureDescriptor);

    Student* student = (Student*) Heap::alloc("Student");
    //StudentList* studentList = (StudentList *) Heap::alloc("StudentList");
    return 0;
}
