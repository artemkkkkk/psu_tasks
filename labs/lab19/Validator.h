#pragma once
#include <string>
#include <vector>

class Validator {
public:
    static bool isValidBinaryString(const std::string& input);
    static bool isValidText(const std::string& input);
    static bool isValidKey(const std::string& input);
    static bool isValidFilename(const std::string& filename);
    static bool isValidMenuChoice(int choice, int maxChoice);
    static bool isValidPosition(int position, int maxSize);
    static bool isNotEmpty(const std::string& input);
};