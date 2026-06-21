#include "HammingCode.h"
#include <sstream>

HammingCode::HammingCode() : parityBitsCount(0) {}

HammingCode::HammingCode(const DynamicArray<int>& data) : data(data), parityBitsCount(0) {
    parityBitsCount = calculateParityBitsCount(data.getSize());
}

int HammingCode::calculateParityBitsCount(int dataSize) const {
    int r = 0;
    while ((1 << r) < dataSize + r + 1) {
        r++;
    }
    return r;
}

void HammingCode::encode() {
    parityBitsCount = calculateParityBitsCount(data.getSize());
    encoded = DynamicArray<int>();
    for (int i = 0; i < data.getSize() + parityBitsCount; ++i) {
        encoded.pushBack(0);
    }

    int dataIndex = 0;
    for (int i = 1; i <= encoded.getSize(); ++i) {
        if ((i & (i - 1)) != 0) {
            encoded[i - 1] = data[dataIndex++];
        }
    }

    calculateParityBits();
}

void HammingCode::calculateParityBits() {
    for (int i = 0; i < parityBitsCount; ++i) {
        int parityPos = (1 << i) - 1;
        int parity = 0;

        for (int j = 1; j <= encoded.getSize(); ++j) {
            if ((j & (parityPos + 1)) != 0) {
                parity ^= encoded[j - 1];
            }
        }

        encoded[parityPos] = parity;
    }
}

void HammingCode::decode() {
    int errorPos = detectError();

    if (errorPos > 0) {
        encoded[errorPos - 1] ^= 1;
    }

    data = DynamicArray<int>();
    for (int i = 1; i <= encoded.getSize(); ++i) {
        if ((i & (i - 1)) != 0) {
            data.pushBack(encoded[i - 1]);
        }
    }
}

int HammingCode::detectError() const {
    int syndrome = 0;

    for (int i = 0; i < parityBitsCount; ++i) {
        int parityPos = (1 << i);
        int parity = 0;

        for (int j = 1; j <= encoded.getSize(); ++j) {
            if ((j & parityPos) != 0) {
                parity ^= encoded[j - 1];
            }
        }

        if (parity != 0) {
            syndrome += parityPos;
        }
    }

    return syndrome;
}

void HammingCode::setData(const DynamicArray<int>& data) {
    this->data = data;
    parityBitsCount = calculateParityBitsCount(data.getSize());
}

const DynamicArray<int>& HammingCode::getData() const {
    return data;
}

const DynamicArray<int>& HammingCode::getEncoded() const {
    return encoded;
}

void HammingCode::introduceError(int position) {
    if (position > 0 && position <= encoded.getSize()) {
        encoded[position - 1] ^= 1;
    }
}

bool HammingCode::hasError() const {
    return detectError() != 0;
}

std::string HammingCode::toString() const {
    std::ostringstream oss;
    for (int i = 0; i < data.getSize(); ++i) {
        oss << data[i];
        if (i < data.getSize() - 1) oss << " ";
    }
    return oss.str();
}

std::string HammingCode::encodedToString() const {
    std::ostringstream oss;
    for (int i = 0; i < encoded.getSize(); ++i) {
        oss << encoded[i];
        if (i < encoded.getSize() - 1) oss << " ";
    }
    return oss.str();
}