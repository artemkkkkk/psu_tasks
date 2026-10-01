#include "tnode.h"

TNode::TNode(int value) : data(value), left(0), right(0) {}

int TNode::getData() const {
    return data;
}

void TNode::setData(int value) {
    data = value;
}

TNode* TNode::getLeft() const {
    return left;
}

void TNode::setLeft(TNode* node) {
    left = node;
}

TNode* TNode::getRight() const {
    return right;
}

void TNode::setRight(TNode* node) {
    right = node;
}

bool TNode::isLeaf() const {
    return left == 0 && right == 0;
}