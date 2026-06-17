#pragma once
#include <vector>
#include <string>

class InputHandler {
public:
    static std::vector<int> inputBinaryDataFromConsole();
    static std::vector<int> inputBinaryDataFromFile(const std::string& filename);
    static std::vector<int> generateRandomBinaryData(int count);

    static std::string inputTextFromConsole();
    static std::string inputTextFromFile(const std::string& filename);
    static std::string generateRandomText();

    static std::string inputKeyFromConsole();
    static std::string inputKeyFromFile(const std::string& filename);

    static int readValidInteger(const std::string& prompt);
    static std::string readValidFilename(const std::string& prompt);
};