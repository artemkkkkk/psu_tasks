#pragma once
#include "DynamicArray.h"
#include <string>

class HammingCode {
private:
    DynamicArray<int> data;
    DynamicArray<int> encoded;
    int parityBitsCount;

    int calculateParityBitsCount(int dataSize) const;
    void calculateParityBits();
    int detectError() const;

public:
    HammingCode();
    HammingCode(const DynamicArray<int>& data);

    void setData(const DynamicArray<int>& data);
    void encode();
    void decode();

    const DynamicArray<int>& getData() const;
    const DynamicArray<int>& getEncoded() const;

    void introduceError(int position);
    bool hasError() const;

    std::string toString() const;
    std::string encodedToString() const;
};