#pragma once
#include "DynamicArray.h"
#include <string>

class InputHandler {
public:
    static DynamicArray<int> inputFromConsole();
    static DynamicArray<int> inputFromFile(const std::string& filename);
    static DynamicArray<int> generateRandom(int count);

    static int readValidInteger(const std::string& prompt);
    static int readValidPositiveInteger(const std::string& prompt);
    static std::string readValidFilename(const std::string& prompt);
};