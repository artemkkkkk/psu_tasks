#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "utf8.h"
#include <iosfwd>

void huffmanBuildAndReport(const char* text, std::ostream& out);

#endif