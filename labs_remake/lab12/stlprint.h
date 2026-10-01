#ifndef STLPRINT_H
#define STLPRINT_H

#include <iostream>

template <typename Iterator>
void printRange(Iterator begin, Iterator end, bool& first) {
    for (Iterator it = begin; it != end; ++it) {
        if (!first) {
            std::cout << ' ';
        }

        std::cout << *it;
        first = false;
    }
}

#endif