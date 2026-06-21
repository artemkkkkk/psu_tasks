#include "Validator.h"

bool Validator::isValidBinaryBit(int bit) {
    return bit == 0 || bit == 1;
}

bool Validator::isValidText(const std::string& input) {
    return !input.empty();
}

bool Validator::isValidKey(const std::string& input) {
    if (input.empty()) {
        return false;
    }
    for (size_t i = 0; i < input.length(); ++i) {
        if (!std::isalpha(input[i])) {
            return false;
        }
    }
    return true;
}

bool Validator::isValidFilename(const std::string& filename) {
    if (filename.empty()) {
        return false;
    }
    for (size_t i = 0; i < filename.length(); ++i) {
        char c = filename[i];
        if (c == '<' || c == '>' || c == ':' || c == '"' || c == '|' || c == '?' || c == '*') {
            return false;
        }
    }
    return true;
}

bool Validator::isValidMenuChoice(int choice, int maxChoice) {
    return choice >= 0 && choice <= maxChoice;
}

bool Validator::isValidPosition(int position, int maxSize) {
    return position > 0 && position <= maxSize;
}

bool Validator::isNotEmpty(const std::string& input) {
    return !input.empty();
}

bool Validator::isValidBinaryData(const DynamicArray<int>& data) {
    for (int i = 0; i < data.getSize(); ++i) {
        if (!isValidBinaryBit(data[i])) {
            return false;
        }
    }
    return !data.isEmpty();
}