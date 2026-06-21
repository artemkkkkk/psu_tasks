#include "HuffmanCode.h"
#include "PriorityQueue.h"
#include <stdexcept>

int compareHuffmanNodes(HuffmanNode* const& a, HuffmanNode* const& b) {
    if (a->frequency != b->frequency) {
        return a->frequency - b->frequency;
    }
    return static_cast<int>(a->character) - static_cast<int>(b->character);
}

HuffmanCode::HuffmanCode() : root(nullptr) {}

HuffmanCode::HuffmanCode(const HuffmanCode& other)
    : root(copyTree(other.root)), codes(other.codes), frequencies(other.frequencies),
      originalText(other.originalText), encodedText(other.encodedText) {}

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
    frequencies = DynamicArray<CodeEntry>();
    for (size_t i = 0; i < text.length(); ++i) {
        char c = text[i];
        int idx = findFrequencyIndex(c);
        if (idx == -1) {
            frequencies.pushBack(CodeEntry(c, "1"));
        } else {
            int currentCount = 0;
            for (size_t j = 0; j < frequencies[idx].code.length(); ++j) {
                currentCount++;
            }
            std::string newCount;
            for (int k = 0; k < currentCount + 1; ++k) {
                newCount += "1";
            }
            frequencies[idx].code = newCount;
        }
    }
    for (int i = 0; i < frequencies.getSize(); ++i) {
        frequencies[i].code = std::to_string(frequencies[i].code.length());
    }
}

int HuffmanCode::findFrequencyIndex(char c) const {
    for (int i = 0; i < frequencies.getSize(); ++i) {
        if (frequencies[i].character == c) {
            return i;
        }
    }
    return -1;
}

int HuffmanCode::findCodeIndex(char c) const {
    for (int i = 0; i < codes.getSize(); ++i) {
        if (codes[i].character == c) {
            return i;
        }
    }
    return -1;
}

void HuffmanCode::buildTree() {
    PriorityQueue<HuffmanNode*> pq(compareHuffmanNodes);

    for (int i = 0; i < frequencies.getSize(); ++i) {
        int freq = std::stoi(frequencies[i].code);
        pq.push(new HuffmanNode(frequencies[i].character, freq));
    }

    while (pq.getSize() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();

        HuffmanNode* newNode = new HuffmanNode('\0', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;
        pq.push(newNode);
    }

    if (!pq.isEmpty()) {
        root = pq.top();
    }
}

void HuffmanCode::generateCodes(HuffmanNode* node, const std::string& code) {
    if (node == nullptr) {
        return;
    }
    if (node->isLeaf()) {
        codes.pushBack(CodeEntry(node->character, code.empty() ? "0" : code));
        return;
    }
    generateCodes(node->left, code + "0");
    generateCodes(node->right, code + "1");
}

void HuffmanCode::encode() {
    destroyTree(root);
    root = nullptr;
    codes = DynamicArray<CodeEntry>();

    if (originalText.empty()) {
        return;
    }

    buildTree();
    generateCodes(root, "");

    encodedText.clear();
    for (size_t i = 0; i < originalText.length(); ++i) {
        int idx = findCodeIndex(originalText[i]);
        if (idx != -1) {
            encodedText += codes[idx].code;
        }
    }
}

std::string HuffmanCode::decode(const std::string& encoded) {
    std::string decoded;
    HuffmanNode* current = root;

    for (size_t i = 0; i < encoded.length(); ++i) {
        char bit = encoded[i];
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

const DynamicArray<HuffmanCode::CodeEntry>& HuffmanCode::getCodes() const {
    return codes;
}

const DynamicArray<HuffmanCode::CodeEntry>& HuffmanCode::getFrequencies() const {
    return frequencies;
}

const std::string& HuffmanCode::getOriginalText() const {
    return originalText;
}

const std::string& HuffmanCode::getEncodedText() const {
    return encodedText;
}

int HuffmanCode::getUniformCodingSize() const {
    if (frequencies.isEmpty()) {
        return 0;
    }
    int bitsPerChar = 1;
    while ((1 << bitsPerChar) < frequencies.getSize()) {
        bitsPerChar++;
    }
    return originalText.length() * bitsPerChar;
}

int HuffmanCode::getHuffmanCodingSize() const {
    return encodedText.length();
}

void HuffmanCode::printCodes(std::ostream& out) const {
    out << "Коды символов:" << std::endl;
    for (int i = 0; i < codes.getSize(); ++i) {
        char displayChar = codes[i].character;
        int freqIdx = findFrequencyIndex(displayChar);
        std::string freqStr = (freqIdx != -1) ? frequencies[freqIdx].code : "?";
        if (displayChar == ' ') {
            out << "' ' (пробел)";
        } else if (displayChar == '\n') {
            out << "'\\n' (перевод строки)";
        } else {
            out << "'" << displayChar << "'";
        }
        out << ": " << codes[i].code << " (частота: " << freqStr << ")" << std::endl;
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