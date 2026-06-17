#pragma once
#include <string>

class Validator {
public:
    static bool isValidPositiveInteger(const std::string& input);
    static bool isValidNonNegativeInteger(const std::string& input);
    static bool isValidVertexNumber(int value, int vertexCount);
    static bool isValidDensity(double value);
    static bool isValidFilename(const std::string& filename);
    static bool isValidMenuChoice(int choice, int maxChoice);
};