#ifndef TNODE_H
#define TNODE_H

class TNode {
private:
    int data;
    TNode* left;
    TNode* right;

public:
    TNode(int value);

    int getData() const;
    void setData(int value);

    TNode* getLeft() const;
    void setLeft(TNode* node);

    TNode* getRight() const;
    void setRight(TNode* node);

    bool isLeaf() const;
};

#endif