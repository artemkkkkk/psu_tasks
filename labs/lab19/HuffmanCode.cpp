#include "HuffmanCode.h"
#include <iostream>
#include <queue>
#include <stdexcept>
#include <functional>

HuffmanCode::HuffmanCode() : root(nullptr) {}

HuffmanCode::HuffmanCode(const HuffmanCode& other) : root(copyTree(other.root)), codes(other.codes),
    frequencies(other.frequencies), originalText(other.originalText), encodedText(other.encodedText) {}

HuffmanCode& HuffmanCode::operator=(const HuffmanCode& other) {
    if (this != &other) {
        destroyTree(root);
        root = copyTree(other.root);
        codes = other.codes;
        frequencies = other.frequencies;
        originalText = other.originalText;
        encodedText = other.encodedText;
    }
    return *this;
}

HuffmanCode::~HuffmanCode() {
    destroyTree(root);
}

void HuffmanCode::destroyTree(HuffmanNode* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

HuffmanNode* HuffmanCode::copyTree(HuffmanNode* node) {
    if (node == nullptr) {
        return nullptr;
    }
    HuffmanNode* newNode = new HuffmanNode(node->character, node->frequency);
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);
    return newNode;
}

void HuffmanCode::setText(const std::string& text) {
    originalText = text;
    frequencies.clear();
    for (char c : text) {
        frequencies[c]++;
    }
}

void HuffmanCode::buildTree() {
    auto cmp = [](HuffmanNode* left, HuffmanNode* right) {
        return left->frequency > right->frequency;
    };
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, decltype(cmp)> pq(cmp);

    for (const auto& pair : frequencies) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();

        HuffmanNode* newNode = new HuffmanNode('\0', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;
        pq.push(newNode);
    }

    if (!pq.empty()) {
        root = pq.top();
    }
}

void HuffmanCode::generateCodes(HuffmanNode* node, const std::string& code) {
    if (node == nullptr) {
        return;
    }
    if (node->isLeaf()) {
        codes[node->character] = code.empty() ? "0" : code;
        return;
    }
    generateCodes(node->left, code + "0");
    generateCodes(node->right, code + "1");
}

void HuffmanCode::encode() {
    destroyTree(root);
    root = nullptr;
    codes.clear();

    if (originalText.empty()) {
        return;
    }

    buildTree();
    generateCodes(root, "");

    encodedText.clear();
    for (char c : originalText) {
        encodedText += codes[c];
    }
}

std::string HuffmanCode::decode(const std::string& encoded) {
    std::string decoded;
    HuffmanNode* current = root;

    for (char bit : encoded) {
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }

        if (current->isLeaf()) {
            decoded += current->character;
            current = root;
        }
    }

    return decoded;
}

const std::map<char, std::string>& HuffmanCode::getCodes() const {
    return codes;
}

const std::map<char, int>& HuffmanCode::getFrequencies() const {
    return frequencies;
}

const std::string& HuffmanCode::getOriginalText() const {
    return originalText;
}

const std::string& HuffmanCode::getEncodedText() const {
    return encodedText;
}

int HuffmanCode::getUniformCodingSize() const {
    if (frequencies.empty()) {
        return 0;
    }
    int bitsPerChar = 1;
    while ((1 << bitsPerChar) < frequencies.size()) {
        bitsPerChar++;
    }
    return originalText.length() * bitsPerChar;
}

int HuffmanCode::getHuffmanCodingSize() const {
    return encodedText.length();
}

void HuffmanCode::printCodes(std::ostream& out) const {
    out << "Коды символов:" << std::endl;
    for (const auto& pair : codes) {
        char displayChar = pair.first;
        if (displayChar == ' ') {
            out << "' ' (пробел)";
        } else if (displayChar == '\n') {
            out << "'\\n' (перевод строки)";
        } else {
            out << "'" << displayChar << "'";
        }
        out << ": " << pair.second << " (частота: " << frequencies.at(pair.first) << ")" << std::endl;
    }
}

void HuffmanCode::printTree(HuffmanNode* node, const std::string& prefix, bool isLeft, std::ostream& out) const {
    if (node == nullptr) {
        return;
    }
    out << prefix;
    out << (isLeft ? "├── " : "└── ");
    if (node->isLeaf()) {
        if (node->character == ' ') {
            out << "' ' (пробел)";
        } else if (node->character == '\n') {
            out << "'\\n'";
        } else {
            out << "'" << node->character << "'";
        }
    } else {
        out << "[уз]";
    }
    out << " (" << node->frequency << ")" << std::endl;
    printTree(node->left, prefix + (isLeft ? "│   " : "    "), true, out);
    printTree(node->right, prefix + (isLeft ? "│   " : "    "), false, out);
}

void HuffmanCode::printTree(std::ostream& out) const {
    if (root == nullptr) {
        out << "(пустое дерево)" << std::endl;
        return;
    }
    printTree(root, "", true, out);
}