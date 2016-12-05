#include <iostream>
#include <map>

class TypeDescriptor {

public:
    TypeDescriptor(int objsize) : objSize(objSize) {}

    int objSize;
};

class Block {
    int len;
    bool used;
    Block next;
    int* data;

public:
    Block(int len) : len(len), used(false) {}
};

class Heap {
    static Block free = new Block(32 * 1024);

    static std::map<char *, Block> descriptors;


    static int alloc(int size) {
        Block start = free;
        Block prev = free;
        free = free.next;
        while (free.len < size + 4 && free != start) {
            prev = free;
            free = free.next;
        }
        if (free.len < size + 4) {
            exit(-5); // TODO: throw error
        } else {
            Block p = free;
            int newLen = p.len - (size + 4);
            if (newLen >= 8) { // split block
                p = new Block(p - 4 + p.len - size);
                p.len = size + 4;
                free.len = newLen;
            } else if (free == prev) { // last free block
                free = null;
            } else { // remove block from list
                prev.next = free.next;
                free = prev;
            }
            //Set all data bytes in block p to 0;
            p.used = true;
            return p;
        }

    }

public:
    static int alloc(char *name) {
        Block typeBlock = descriptors[name];
        Block allocBlock = alloc(typeBlock.objSize);
        return (int *) allocBlock;
    }

    static int registered(char *name, TypeDescriptor typeDescriptor) {
        Block block = alloc(typeDescriptor.objSize);
        block.data = typeDescriptor;
        descriptors[name] = block;
        return (int *) block;
    }

};

int main() {
    TypeDescriptor typeDesc(10);

    Heap::registedr(typeDesc);

    return 0;
}