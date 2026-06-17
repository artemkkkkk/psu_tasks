#pragma once
#include <string>

class Validator {
public:
    static bool isValidHours(int value);
    static bool isValidMinutes(int value);
    static bool isValidUnsignedInt(const std::string& input);
    static bool isValidPositiveInt(const std::string& input);
    static bool isValidFilename(const std::string& filename);
    static bool isValidMenuChoice(int choice, int maxChoice);
    static bool isNotEmpty(const std::string& input);
};