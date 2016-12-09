
#include "descriptor/studentListDescriptor.h"
#include "descriptor/studentNodeDescriptor.h"
#include "descriptor/studentDescriptor.h"
#include "descriptor/lectureNodeDescriptor.h"
#include "descriptor/lectrueDescriptor.h"

#include "entities/student.h"

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

    //Student *student = (Student *) Heap::alloc("Student");
    return 0;
}
