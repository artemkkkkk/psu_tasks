#include "Validator.h"
#include <cctype>

bool Validator::isValidInteger(const std::string& input) {
    if (input.empty()) {
        return false;
    }
    size_t start = 0;
    if (input[0] == '-' || input[0] == '+') {
        start = 1;
    }
    if (start >= input.size()) {
        return false;
    }
    for (size_t i = start; i < input.size(); ++i) {
        if (!std::isdigit(static_cast<unsigned char>(input[i]))) {
            return false;
        }
    }
    return true;
}

bool Validator::isValidExpression(const std::string& expression) {
    return !expression.empty();
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