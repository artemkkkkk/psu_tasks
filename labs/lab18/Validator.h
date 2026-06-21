#pragma once
#include <string>
#include "DynamicArray.h"

class Validator {
public:
    static bool isValidInteger(const std::string& input);
    static bool isValidPositiveInteger(const std::string& input);
    static bool isValidFilename(const std::string& filename);
    static bool isValidMenuChoice(int choice, int maxChoice);
    static bool isValidTreeValues(const DynamicArray<int>& values);
    static bool isNotEmpty(const std::string& input);
};