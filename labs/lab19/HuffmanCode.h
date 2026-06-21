#pragma once
#include "HuffmanNode.h"
#include "DynamicArray.h"
#include <string>
#include <iostream>

class HuffmanCode {
private:
    struct CodeEntry {
        char character;
        std::string code;
        CodeEntry() : character('\0'), code("") {}
        CodeEntry(char c, const std::string& cd) : character(c), code(cd) {}
    };

    HuffmanNode* root;
    DynamicArray<CodeEntry> codes;
    DynamicArray<CodeEntry> frequencies;
    std::string originalText;
    std::string encodedText;

    void buildTree();
    void generateCodes(HuffmanNode* node, const std::string& code);
    void destroyTree(HuffmanNode* node);
    HuffmanNode* copyTree(HuffmanNode* node);
    void printTree(HuffmanNode* node, const std::string& prefix, bool isLeft, std::ostream& out) const;

    int findFrequencyIndex(char c) const;
    int findCodeIndex(char c) const;

public:
    HuffmanCode();
    HuffmanCode(const HuffmanCode& other);
    HuffmanCode& operator=(const HuffmanCode& other);
    ~HuffmanCode();

    void setText(const std::string& text);
    void encode();
    std::string decode(const std::string& encoded);

    const DynamicArray<CodeEntry>& getCodes() const;
    const DynamicArray<CodeEntry>& getFrequencies() const;
    const std::string& getOriginalText() const;
    const std::string& getEncodedText() const;

    int getUniformCodingSize() const;
    int getHuffmanCodingSize() const;

    void printCodes(std::ostream& out) const;
    void printTree(std::ostream& out) const;
};