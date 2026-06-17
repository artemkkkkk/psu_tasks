#include "HuffmanNode.h"

HuffmanNode::HuffmanNode(char character, int frequency)
    : character(character), frequency(frequency), left(nullptr), right(nullptr) {}

HuffmanNode::~HuffmanNode() {}

bool HuffmanNode::isLeaf() const {
    return left == nullptr && right == nullptr;
}