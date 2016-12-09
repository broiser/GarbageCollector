#include <iostream>
#include <map>
#include <list>

using byte = unsigned char;

class TypeDescriptor {
public:
    int objSize;
    int *pointers;

    TypeDescriptor(int objsize) : objSize(objSize) {}
};

class StudentDescriptor : public TypeDescriptor {
public:
    StudentDescriptor() : TypeDescriptor(12) {
        pointers = new int[3];
        pointers[0] = 4;
        pointers[1] = 8;
        pointers[2] = -8;
    }
};

class LectureDescriptor : public TypeDescriptor {
public:
    LectureDescriptor() : TypeDescriptor(12) {
        pointers = new int[2];
        pointers[0] = 4;
        pointers[1] = -4;
    }
};

class Block {
public:
    TypeDescriptor *descriptor;
    int size;
    byte *data;
};

class Heap {
    //static Block free = new Block(32 * 1024);

    //static std::map<char *, Block> descriptors;

public:
    static byte *alloc(char *name) {
        //Block typeBlock = descriptors[name];
        //Block allocBlock = alloc(typeBlock.objSize);
        //return (int *) allocBlock;
    }

    static void registered(char *name, TypeDescriptor *typeDescriptor) {
        // Block block = alloc(typeDescriptor.objSize);
        //block.data = typeDescriptor;
        //descriptors[name] = block;
        //return (int *) block;
    }

};

int main() {
    StudentDescriptor *studentDescriptor = new StudentDescriptor();
    LectureDescriptor *lectureDescriptor = new LectureDescriptor();
    Heap::registered("Student", studentDescriptor);
    Heap::registered("Lecture", lectureDescriptor);
    return 0;
}
