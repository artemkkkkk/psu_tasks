#ifndef CALCTREE_H
#define CALCTREE_H

#include "tnode.h"
#include <iosfwd>

class CalcTree {
private:
    TNode* root;

    static TNode* clone(TNode* node);
    static void dispose(TNode* node);
    static void printGraphicalRec(TNode* node, int level, int parentValue, bool hasParent, std::ostream& out);
    static void printSymbol(std::ostream& out, int data);
    static bool evalRec(TNode* node, int x, int& result);
    static void printPrefixRec(TNode* node, std::ostream& out, bool& first);
    static void printPostfixRec(TNode* node, std::ostream& out, bool& first);
    static void printInfixRec(TNode* node, std::ostream& out);
    static bool containsOpRec(TNode* node, int op);
    static bool containsAxPlusXRec(TNode* node);
    static TNode* eliminateSubtractionRec(TNode* node);
    static TNode* swapAxRec(TNode* node);

public:
    CalcTree();
    CalcTree(const CalcTree& other);
    ~CalcTree();

    CalcTree& operator=(const CalcTree& other);

    bool isEmpty() const;
    TNode* getRoot() const;
    void attachRoot(TNode* node);

    bool buildFromPostfix(const int* tokens, int count);

    bool evaluate(int x, int& result) const;

    void printGraphical(std::ostream& out) const;
    void printPrefix(std::ostream& out) const;
    void printPostfix(std::ostream& out) const;
    void printInfix(std::ostream& out) const;

    bool containsOperator(int op) const;
    bool containsAxPlusX() const;

    void eliminateSubtraction();
    void swapAxToXa();

    static TNode* createNode(int value);
    static void disposeNode(TNode* node);
};

#endif