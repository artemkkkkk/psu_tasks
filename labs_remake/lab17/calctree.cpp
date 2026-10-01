#include "calctree.h"
#include <iostream>

TNode* CalcTree::clone(TNode* node) {
    if (!node) {
        return 0;
    }

    TNode* copy = new TNode(node->getData());
    copy->setLeft(clone(node->getLeft()));
    copy->setRight(clone(node->getRight()));
    return copy;
}

void CalcTree::dispose(TNode* node) {
    if (!node) {
        return;
    }

    dispose(node->getLeft());
    dispose(node->getRight());
    delete node;
}

CalcTree::CalcTree() : root(0) {}

CalcTree::CalcTree(const CalcTree& other) : root(clone(other.root)) {}

CalcTree::~CalcTree() {
    dispose(root);
}

CalcTree& CalcTree::operator=(const CalcTree& other) {
    if (this != &other) {
        dispose(root);
        root = clone(other.root);
    }

    return *this;
}

bool CalcTree::isEmpty() const {
    return root == 0;
}

TNode* CalcTree::getRoot() const {
    return root;
}

void CalcTree::attachRoot(TNode* node) {
    dispose(root);
    root = node;
}

TNode* CalcTree::createNode(int value) {
    return new TNode(value);
}

void CalcTree::disposeNode(TNode* node) {
    dispose(node);
}

bool CalcTree::buildFromPostfix(const int* tokens, int count) {
    dispose(root);
    root = 0;

    if (count <= 0 || !tokens) {
        return false;
    }

    TNode** stack = new TNode*[count];
    int top = 0;
    bool ok = true;

    for (int i = 0; i < count && ok; ++i) {
        int t = tokens[i];

        if (t >= 0 && t <= 9) {
            stack[top++] = new TNode(t);
        } else if (t >= -3 && t <= -1) {
            if (top < 2) {
                ok = false;
                break;
            }

            TNode* right = stack[--top];
            TNode* left = stack[--top];

            char op = t == -1 ? '+' : (t == -2 ? '-' : '*');

            TNode* node = new TNode(op);
            node->setLeft(left);
            node->setRight(right);
            stack[top++] = node;
        } else {
            ok = false;
        }
    }

    if (!ok || top != 1) {
        for (int i = 0; i < top; ++i) {
            dispose(stack[i]);
        }

        delete[] stack;
        return false;
    }

    root = stack[0];
    delete[] stack;
    return true;
}

bool CalcTree::evalRec(TNode* node, int x, int& result) {
    if (!node) {
        return false;
    }

    if (node->isLeaf()) {
        if (node->isVariable()) {
            result = x;
            return true;
        }

        result = node->getData();
        return true;
    }

    int leftValue = 0;
    int rightValue = 0;

    if (!evalRec(node->getLeft(), x, leftValue)) {
        return false;
    }

    if (!evalRec(node->getRight(), x, rightValue)) {
        return false;
    }

    switch (node->getData()) {
        case '+':
            result = leftValue + rightValue;
            return true;
        case '-':
            result = leftValue - rightValue;
            return true;
        case '*':
            result = leftValue * rightValue;
            return true;
        case '/':
            if (rightValue == 0) {
                return false;
            }
            result = leftValue / rightValue;
            return true;
        case '%':
            if (rightValue == 0) {
                return false;
            }
            result = leftValue % rightValue;
            return true;
        case '^': {
            if (rightValue < 0) {
                return false;
            }

            int acc = 1;
            for (int i = 0; i < rightValue; ++i) {
                acc *= leftValue;
            }

            result = acc;
            return true;
        }
    }

    return false;
}

bool CalcTree::evaluate(int x, int& result) const {
    return evalRec(root, x, result);
}

void CalcTree::printSymbol(std::ostream& out, int data) {
    if (data == VAR_X) {
        out << 'x';
    } else if (data == '+' || data == '-' || data == '*' ||
               data == '/' || data == '%' || data == '^') {
        out << static_cast<char>(data);
    } else {
        out << data;
    }
}

void CalcTree::printGraphicalRec(TNode* node, int level, int parentValue, bool hasParent, std::ostream& out) {
    if (!node) {
        return;
    }

    printGraphicalRec(node->getRight(), level + 1, node->getData(), true, out);

    for (int i = 0; i < level; ++i) {
        out << "    ";
    }

    printSymbol(out, node->getData());

    if (hasParent) {
        out << " [<- ";
        printSymbol(out, parentValue);
        out << "]";
    } else {
        out << " [root]";
    }

    out << '\n';

    printGraphicalRec(node->getLeft(), level + 1, node->getData(), true, out);
}

void CalcTree::printGraphical(std::ostream& out) const {
    if (!root) {
        out << "(пустое дерево)\n";
        return;
    }

    printGraphicalRec(root, 0, 0, false, out);
}

void CalcTree::printPrefixRec(TNode* node, std::ostream& out, bool& first) {
    if (!node) {
        return;
    }

    if (!first) {
        out << ' ';
    }

    printSymbol(out, node->getData());
    first = false;

    printPrefixRec(node->getLeft(), out, first);
    printPrefixRec(node->getRight(), out, first);
}

void CalcTree::printPrefix(std::ostream& out) const {
    bool first = true;
    printPrefixRec(root, out, first);
}

void CalcTree::printPostfixRec(TNode* node, std::ostream& out, bool& first) {
    if (!node) {
        return;
    }

    printPostfixRec(node->getLeft(), out, first);
    printPostfixRec(node->getRight(), out, first);

    if (!first) {
        out << ' ';
    }

    printSymbol(out, node->getData());
    first = false;
}

void CalcTree::printPostfix(std::ostream& out) const {
    bool first = true;
    printPostfixRec(root, out, first);
}

void CalcTree::printInfixRec(TNode* node, std::ostream& out) {
    if (!node) {
        return;
    }

    if (node->isLeaf()) {
        printSymbol(out, node->getData());
        return;
    }

    out << '(';
    printInfixRec(node->getLeft(), out);
    out << static_cast<char>(node->getData());
    printInfixRec(node->getRight(), out);
    out << ')';
}

void CalcTree::printInfix(std::ostream& out) const {
    printInfixRec(root, out);
}

bool CalcTree::containsOpRec(TNode* node, int op) {
    if (!node) {
        return false;
    }

    if (node->getData() == op) {
        return true;
    }

    return containsOpRec(node->getLeft(), op) || containsOpRec(node->getRight(), op);
}

bool CalcTree::containsOperator(int op) const {
    return containsOpRec(root, op);
}

bool CalcTree::containsAxPlusXRec(TNode* node) {
    if (!node) {
        return false;
    }

    if (node->getData() == '+' && node->getRight() && node->getRight()->isVariable()) {
        return true;
    }

    return containsAxPlusXRec(node->getLeft()) || containsAxPlusXRec(node->getRight());
}

bool CalcTree::containsAxPlusX() const {
    return containsAxPlusXRec(root);
}

TNode* CalcTree::eliminateSubtractionRec(TNode* node) {
    if (!node) {
        return 0;
    }

    node->setLeft(eliminateSubtractionRec(node->getLeft()));
    node->setRight(eliminateSubtractionRec(node->getRight()));

    if (node->getData() == '-') {
        int value = 0;
        evalRec(node, 0, value);

        dispose(node->getLeft());
        dispose(node->getRight());

        node->setLeft(0);
        node->setRight(0);
        node->setData(value);
    }

    return node;
}

void CalcTree::eliminateSubtraction() {
    root = eliminateSubtractionRec(root);
}

TNode* CalcTree::swapAxRec(TNode* node) {
    if (!node) {
        return 0;
    }

    node->setLeft(swapAxRec(node->getLeft()));
    node->setRight(swapAxRec(node->getRight()));

    if (node->getData() == '+' && node->getRight() && node->getRight()->isVariable()) {
        TNode* temp = node->getLeft();
        node->setLeft(node->getRight());
        node->setRight(temp);
    }

    return node;
}

void CalcTree::swapAxToXa() {
    root = swapAxRec(root);
}