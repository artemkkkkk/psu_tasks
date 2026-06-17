#include "Validator.h"
#include <cctype>

bool Validator::isValidBinaryString(const std::string& input) {
    if (input.empty()) {
        return false;
    }
    for (char c : input) {
        if (c != '0' && c != '1' && c != ' ') {
            return false;
        }
    }
    return true;
}

bool Validator::isValidText(const std::string& input) {
    return !input.empty();
}

bool Validator::isValidKey(const std::string& input) {
    if (input.empty()) {
        return false;
    }
    for (char c : input) {
        if (!std::isalpha(c)) {
            return false;
        }
    }
    return true;
}

bool Validator::isValidFilename(const std::string& filename) {
    if (filename.empty()) {
        return false;
    }
    for (char c : filename) {
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