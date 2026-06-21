#pragma once
#include <string>

class Validator {
public:
    static bool isValidInteger(const std::string& input);
    static bool isValidPositiveInteger(const std::string& input);
    static bool isValidFilename(const std::string& filename);
    static bool isValidMenuChoice(int choice, int maxChoice);
    static bool isNotEmpty(const std::string& input);
};