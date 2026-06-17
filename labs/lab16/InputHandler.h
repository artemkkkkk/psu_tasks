#pragma once
#include <vector>
#include <string>

class InputHandler {
public:
    static std::vector<int> inputFromConsole();
    static std::vector<int> inputFromFile(const std::string& filename);
    static std::vector<int> generateRandom(int count);

    static int readValidInteger(const std::string& prompt);
    static int readValidPositiveInteger(const std::string& prompt);
    static std::string readValidFilename(const std::string& prompt);
};