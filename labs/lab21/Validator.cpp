#include "Validator.h"
#include <cctype>

bool Validator::isValidPositiveInteger(const std::string& input) {
    if (input.empty()) {
        return false;
    }
    for (char c : input) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    try {
        return std::stoi(input) > 0;
    } catch (...) {
        return false;
    }
}

bool Validator::isValidNonNegativeInteger(const std::string& input) {
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

bool Validator::isValidVertexNumber(int value, int vertexCount) {
    return value >= 1 && value <= vertexCount;
}

bool Validator::isValidDensity(double value) {
    return value >= 0.0 && value <= 1.0;
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