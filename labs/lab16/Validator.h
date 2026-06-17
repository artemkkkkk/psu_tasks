#pragma once
#include <string>
#include <vector>

class Validator {
public:
    static bool isValidInteger(const std::string& input);
    static bool isValidPositiveInteger(const std::string& input);
    static bool isValidFilename(const std::string& filename);
    static bool isValidMenuChoice(int choice, int maxChoice);
    static bool isValidTreeValues(const std::vector<int>& values);
    static bool isNotEmpty(const std::string& input);
};