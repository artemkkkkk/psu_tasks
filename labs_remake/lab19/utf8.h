#ifndef UTF8_H
#define UTF8_H

struct Symbol {
    char bytes[8];
};

int parseSymbols(const char* text, Symbol* out, int maxSymbols);
bool symbolsEqual(const Symbol& a, const Symbol& b);

#endif