#include "utf8.h"
#include <cstring>

static int utf8CharLength(unsigned char c) {
    if (c < 0x80) {
        return 1;
    }

    if ((c & 0xE0) == 0xC0) {
        return 2;
    }

    if ((c & 0xF0) == 0xE0) {
        return 3;
    }

    return 4;
}

int parseSymbols(const char* text, Symbol* out, int maxSymbols) {
    int count = 0;
    int i = 0;
    int len = static_cast<int>(std::strlen(text));

    while (i < len && count < maxSymbols) {
        int l = utf8CharLength(static_cast<unsigned char>(text[i]));

        Symbol s;
        int j = 0;

        for (; j < l && text[i + j]; ++j) {
            s.bytes[j] = text[i + j];
        }

        s.bytes[j] = '\0';

        out[count++] = s;
        i += l;
    }

    return count;
}

bool symbolsEqual(const Symbol& a, const Symbol& b) {
    return std::strcmp(a.bytes, b.bytes) == 0;
}