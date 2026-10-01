#include "hamming.h"
#include <iostream>

bool hammingIsPowerOfTwo(int x) {
    return x > 0 && (x & (x - 1)) == 0;
}

int hammingParityBits(int k) {
    int r = 0;

    while ((1 << r) < k + r + 1) {
        ++r;
    }

    return r;
}

void hammingEncodeWithSteps(const char* msg, int* code, int n, std::ostream& out) {
    for (int i = 1; i <= n; ++i) {
        code[i] = 0;
    }

    int m = 0;

    for (int i = 1; i <= n && msg[m]; ++i) {
        if (!hammingIsPowerOfTwo(i)) {
            code[i] = msg[m] - '0';
            ++m;
        }
    }

    for (int p = 1; p <= n; p <<= 1) {
        int parity = 0;

        out << "Контрольный бит p" << p << " покрывает позиции:";

        bool first = true;

        for (int j = 1; j <= n; ++j) {
            if (j != p && (j & p)) {
                out << (first ? " " : ", ") << j;
                first = false;
                parity ^= code[j];
            }
        }

        code[p] = parity;
        out << " -> значение " << parity << '\n';
    }
}

int hammingSyndrome(const int* code, int n) {
    int syndrome = 0;

    for (int p = 1; p <= n; p <<= 1) {
        int check = 0;

        for (int j = 1; j <= n; ++j) {
            if (j & p) {
                check ^= code[j];
            }
        }

        if (check) {
            syndrome += p;
        }
    }

    return syndrome;
}

void hammingExtract(const int* code, int n, char* msg) {
    int idx = 0;

    for (int i = 1; i <= n; ++i) {
        if (!hammingIsPowerOfTwo(i)) {
            msg[idx++] = static_cast<char>('0' + code[i]);
        }
    }

    msg[idx] = '\0';
}

void hammingPrintCode(const int* code, int n, std::ostream& out) {
    for (int i = 1; i <= n; ++i) {
        out << code[i];
    }

    out << '\n';
}