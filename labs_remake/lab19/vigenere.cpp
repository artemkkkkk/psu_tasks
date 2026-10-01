#include "vigenere.h"
#include "utf8.h"
#include <cstring>

static const char* ALPHA[32] = {
    "А", "Б", "В", "Г", "Д", "Е", "Ж", "З",
    "И", "Й", "К", "Л", "М", "Н", "О", "П",
    "Р", "С", "Т", "У", "Ф", "Х", "Ц", "Ч",
    "Ш", "Щ", "Ъ", "Ы", "Ь", "Э", "Ю", "Я"
};

static int alphaIndex(const Symbol& s) {
    for (int i = 0; i < 32; ++i) {
        if (std::strcmp(ALPHA[i], s.bytes) == 0) {
            return i;
        }
    }

    return -1;
}

bool vigenereKeyValid(const char* key) {
    Symbol keySyms[64];
    int count = parseSymbols(key, keySyms, 64);

    for (int i = 0; i < count; ++i) {
        if (alphaIndex(keySyms[i]) >= 0) {
            return true;
        }
    }

    return false;
}

void vigenereCrypt(const char* message, const char* key, char* out, int outSize, bool encrypt) {
    Symbol keySyms[64];
    int keyCount = parseSymbols(key, keySyms, 64);

    int keyIdx[64];
    int keyLen = 0;

    for (int i = 0; i < keyCount; ++i) {
        int a = alphaIndex(keySyms[i]);

        if (a >= 0) {
            keyIdx[keyLen++] = a;
        }
    }

    if (keyLen == 0) {
        if (outSize > 0) {
            out[0] = '\0';
        }

        return;
    }

    Symbol msgSyms[512];
    int msgCount = parseSymbols(message, msgSyms, 512);

    int pos = 0;
    int keyPos = 0;

    for (int i = 0; i < msgCount; ++i) {
        const char* src = msgSyms[i].bytes;
        int a = alphaIndex(msgSyms[i]);

        if (a >= 0) {
            int shift = keyIdx[keyPos % keyLen];
            ++keyPos;

            int idx = encrypt ? (a + shift) % 32 : (a - shift + 32) % 32;
            src = ALPHA[idx];
        }

        for (int j = 0; src[j] && pos < outSize - 1; ++j) {
            out[pos++] = src[j];
        }
    }

    out[pos] = '\0';
}