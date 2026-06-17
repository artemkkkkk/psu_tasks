#pragma once
#include <string>

class VigenereCipher {
private:
    std::string key;

    char shiftChar(char c, int shift, bool encrypt) const;
    int charToShift(char c) const;

public:
    VigenereCipher();
    VigenereCipher(const std::string& key);

    void setKey(const std::string& key);
    std::string getKey() const;

    std::string encrypt(const std::string& text) const;
    std::string decrypt(const std::string& text) const;
};