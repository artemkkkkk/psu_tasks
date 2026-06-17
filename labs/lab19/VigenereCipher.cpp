#include "VigenereCipher.h"
#include <stdexcept>
#include <cctype>

VigenereCipher::VigenereCipher() : key("") {}

VigenereCipher::VigenereCipher(const std::string& key) : key(key) {}

void VigenereCipher::setKey(const std::string& key) {
    this->key = key;
}

std::string VigenereCipher::getKey() const {
    return key;
}

int VigenereCipher::charToShift(char c) const {
    if (std::islower(c)) {
        return c - 'a';
    } else if (std::isupper(c)) {
        return c - 'A';
    }
    return 0;
}

char VigenereCipher::shiftChar(char c, int shift, bool encrypt) const {
    if (std::islower(c)) {
        if (encrypt) {
            return 'a' + (c - 'a' + shift) % 26;
        } else {
            return 'a' + (c - 'a' - shift + 26) % 26;
        }
    } else if (std::isupper(c)) {
        if (encrypt) {
            return 'A' + (c - 'A' + shift) % 26;
        } else {
            return 'A' + (c - 'A' - shift + 26) % 26;
        }
    }
    return c;
}

std::string VigenereCipher::encrypt(const std::string& text) const {
    if (key.empty()) {
        throw std::runtime_error("Ключ не задан");
    }
    
    std::string result = text;
    int keyIndex = 0;
    
    for (size_t i = 0; i < text.length(); ++i) {
        if (std::isalpha(text[i])) {
            int shift = charToShift(key[keyIndex % key.length()]);
            result[i] = shiftChar(text[i], shift, true);
            keyIndex++;
        }
    }
    
    return result;
}

std::string VigenereCipher::decrypt(const std::string& text) const {
    if (key.empty()) {
        throw std::runtime_error("Ключ не задан");
    }
    
    std::string result = text;
    int keyIndex = 0;
    
    for (size_t i = 0; i < text.length(); ++i) {
        if (std::isalpha(text[i])) {
            int shift = charToShift(key[keyIndex % key.length()]);
            result[i] = shiftChar(text[i], shift, false);
            keyIndex++;
        }
    }
    
    return result;
}