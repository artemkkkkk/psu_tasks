#pragma once
#include "DynamicArray.h"
#include <string>

class InputHandler {
public:
    static DynamicArray<int> inputBinaryDataFromConsole();
    static DynamicArray<int> inputBinaryDataFromFile(const std::string& filename);
    static DynamicArray<int> generateRandomBinaryData(int count);

    static std::string inputTextFromConsole();
    static std::string inputTextFromFile(const std::string& filename);
    static std::string generateRandomText();

    static std::string inputKeyFromConsole();
    static std::string inputKeyFromFile(const std::string& filename);

    static int readValidInteger(const std::string& prompt);
    static std::string readValidFilename(const std::string& prompt);
};