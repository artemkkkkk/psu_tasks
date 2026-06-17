#include "HammingCode.h"
#include <cmath>
#include <stdexcept>
#include <sstream>

HammingCode::HammingCode() : parityBitsCount(0) {}

HammingCode::HammingCode(const std::vector<int>& data) : data(data), parityBitsCount(0) {
    parityBitsCount = calculateParityBitsCount(data.size());
}

int HammingCode::calculateParityBitsCount(int dataSize) const {
    int r = 0;
    while ((1 << r) < dataSize + r + 1) {
        r++;
    }
    return r;
}

void HammingCode::encode() {
    parityBitsCount = calculateParityBitsCount(data.size());
    encoded.assign(data.size() + parityBitsCount, 0);
    
    int dataIndex = 0;
    for (int i = 1; i <= encoded.size(); ++i) {
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
        
        for (int j = 1; j <= encoded.size(); ++j) {
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
    
    data.clear();
    for (int i = 1; i <= encoded.size(); ++i) {
        if ((i & (i - 1)) != 0) {
            data.push_back(encoded[i - 1]);
        }
    }
}

int HammingCode::detectError() const {
    int syndrome = 0;
    
    for (int i = 0; i < parityBitsCount; ++i) {
        int parityPos = (1 << i);
        int parity = 0;
        
        for (int j = 1; j <= encoded.size(); ++j) {
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

void HammingCode::setData(const std::vector<int>& data) {
    this->data = data;
    parityBitsCount = calculateParityBitsCount(data.size());
}

const std::vector<int>& HammingCode::getData() const {
    return data;
}

const std::vector<int>& HammingCode::getEncoded() const {
    return encoded;
}

void HammingCode::introduceError(int position) {
    if (position > 0 && position <= encoded.size()) {
        encoded[position - 1] ^= 1;
    }
}

bool HammingCode::hasError() const {
    return detectError() != 0;
}

std::string HammingCode::toString() const {
    std::ostringstream oss;
    for (size_t i = 0; i < data.size(); ++i) {
        oss << data[i];
        if (i < data.size() - 1) oss << " ";
    }
    return oss.str();
}

std::string HammingCode::encodedToString() const {
    std::ostringstream oss;
    for (size_t i = 0; i < encoded.size(); ++i) {
        oss << encoded[i];
        if (i < encoded.size() - 1) oss << " ";
    }
    return oss.str();
}