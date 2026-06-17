#include "Validator.h"
#include <cctype>

bool Validator::isValidHours(int value) {
    return value >= 0 && value < 24;
}

bool Validator::isValidMinutes(int value) {
    return value >= 0 && value < 60;
}

bool Validator::isValidUnsignedInt(const std::string& input) {
    if (input.empty()) {
        return false;
    }
    for (char c : input) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    return true;
}

bool Validator::isValidPositiveInt(const std::string& input) {
    if (!isValidUnsignedInt(input)) {
        return false;
    }
    try {
        return std::stoi(input) > 0;
    } catch (...) {
        return false;
    }
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

bool Validator::isNotEmpty(const std::string& input) {
    return !input.empty();
}