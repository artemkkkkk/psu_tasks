#include "Validator.h"
#include <cctype>
#include <cstdlib>

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
    for (size_t i = 0; i < input.size(); ++i) {
        if (!std::isdigit(static_cast<unsigned char>(input[i]))) {
            return false;
        }
    }
    return true;
}

bool Validator::isValidPositiveInt(const std::string& input) {
    if (!isValidUnsignedInt(input)) {
        return false;
    }
    int value = std::atoi(input.c_str());
    return value > 0;
}

bool Validator::isValidFilename(const std::string& filename) {
    if (filename.empty()) {
        return false;
    }
    for (size_t i = 0; i < filename.size(); ++i) {
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

bool Validator::isNotEmpty(const std::string& input) {
    return !input.empty();
}