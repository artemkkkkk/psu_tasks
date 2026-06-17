#pragma once
#include <vector>
#include <string>

class HammingCode {
private:
    std::vector<int> data;
    std::vector<int> encoded;
    int parityBitsCount;

    int calculateParityBitsCount(int dataSize) const;
    void calculateParityBits();
    int detectError() const;

public:
    HammingCode();
    HammingCode(const std::vector<int>& data);

    void setData(const std::vector<int>& data);
    void encode();
    void decode();

    const std::vector<int>& getData() const;
    const std::vector<int>& getEncoded() const;

    void introduceError(int position);
    bool hasError() const;

    std::string toString() const;
    std::string encodedToString() const;
};