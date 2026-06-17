#pragma once

class HuffmanNode {
public:
    char character;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char character, int frequency);
    ~HuffmanNode();

    bool isLeaf() const;
};