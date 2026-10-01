#ifndef HAMMING_H
#define HAMMING_H

#include <iosfwd>

int hammingParityBits(int k);
bool hammingIsPowerOfTwo(int x);
void hammingEncodeWithSteps(const char* msg, int* code, int n, std::ostream& out);
int hammingSyndrome(const int* code, int n);
void hammingExtract(const int* code, int n, char* msg);
void hammingPrintCode(const int* code, int n, std::ostream& out);

#endif