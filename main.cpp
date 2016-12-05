#include <iostream>

class TypeDescriptor {

    public:
        TypeDescriptor(int objsize) : objSize(objSize) {}

    int objSize;
};

class Block {
    int len;
    Block next;
    bool markBit;

    public:
        Block(int len, const Block &next) : len(len), next(next) {}
    };

class Heap {
    int size;
    Block free;

    public:
        Heap(int size) : size(size), free(free) {}

};

int main() {
    TypeDescriptor typeDesc(10);
    printf("%d", typeDesc.objSize);
    return 0;
}