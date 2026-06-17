#pragma once
#include "HuffmanNode.h"
#include <string>
#include <map>
#include <vector>

class HuffmanCode {
private:
    HuffmanNode* root;
    std::map<char, std::string> codes;
    std::map<char, int> frequencies;
    std::string originalText;
    std::string encodedText;

    void buildTree();
    void generateCodes(HuffmanNode* node, const std::string& code);
    void destroyTree(HuffmanNode* node);
    HuffmanNode* copyTree(HuffmanNode* node);
    void printTree(HuffmanNode* node, const std::string& prefix, bool isLeft, std::ostream& out) const;

public:
    HuffmanCode();
    HuffmanCode(const HuffmanCode& other);
    HuffmanCode& operator=(const HuffmanCode& other);
    ~HuffmanCode();

    void setText(const std::string& text);
    void encode();
    std::string decode(const std::string& encoded);

    const std::map<char, std::string>& getCodes() const;
    const std::map<char, int>& getFrequencies() const;
    const std::string& getOriginalText() const;
    const std::string& getEncodedText() const;

    int getUniformCodingSize() const;
    int getHuffmanCodingSize() const;

    void printCodes(std::ostream& out) const;
    void printTree(std::ostream& out) const;
};