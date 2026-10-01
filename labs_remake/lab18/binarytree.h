#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "tnode.h"
#include <iosfwd>

class BinaryTree {
private:
    TNode* root;

    static TNode* clone(TNode* node);
    static void dispose(TNode* node);
    static void printGraphicalRec(TNode* node, int level, int parentValue, bool hasParent, std::ostream& out);
    static int countRec(TNode* node);

public:
    BinaryTree();
    BinaryTree(const BinaryTree& other);
    ~BinaryTree();

    BinaryTree& operator=(const BinaryTree& other);

    bool isEmpty() const;
    int count() const;
    TNode* getRoot() const;

    void attachRoot(TNode* node);
    TNode* release();

    bool insertBST(int value);

    void printGraphical(std::ostream& out) const;
    void fillLevelOrder(TNode** arr, TNode** parents) const;

    static TNode* createNode(int value);
    static void disposeNode(TNode* node);
};

#endif