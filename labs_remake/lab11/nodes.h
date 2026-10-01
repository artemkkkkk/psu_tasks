#ifndef NODES_H
#define NODES_H

struct TNode {
    int Data;
    TNode* Next;

    TNode(int value = 0) : Data(value), Next(0) {}
};

struct TNode2 {
    int Data;
    TNode2* Next;
    TNode2* Prev;

    TNode2(int value = 0) : Data(value), Next(0), Prev(0) {}
};

struct NameNode {
    char Name[64];
    NameNode* Next;

    NameNode(const char* name = "") {
        int i = 0;

        if (name) {
            for (; i < 63 && name[i]; ++i) {
                Name[i] = name[i];
            }
        }

        Name[i] = '\0';
        Next = 0;
    }
};

#endif