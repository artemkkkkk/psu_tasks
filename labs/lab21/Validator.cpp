#include "Validator.h"
#include <cctype>
#include <cstdlib>

bool Validator::isValidPositiveInteger(const std::string& input) {
    if (input.empty()) {
        return false;
    }
    for (size_t i = 0; i < input.size(); ++i) {
        if (!std::isdigit(static_cast<unsigned char>(input[i]))) {
            return false;
        }
    }
    int value = std::atoi(input.c_str());
    return value > 0;
}

bool Validator::isValidNonNegativeInteger(const std::string& input) {
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