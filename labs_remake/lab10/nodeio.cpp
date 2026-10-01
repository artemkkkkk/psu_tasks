#include "nodeio.h"
#include <iostream>

void printNodePointer(const char* label, const TNode* node) {
    std::cout << label;

    if (node) {
        std::cout << static_cast<const void*>(node);
    } else {
        std::cout << "nullptr";
    }

    std::cout << '\n';
}

void printNodeValue(const char* label, const TNode* node) {
    std::cout << label;

    if (node) {
        std::cout << node->Data;
    } else {
        std::cout << "nullptr";
    }

    std::cout << '\n';
}