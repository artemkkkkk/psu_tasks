#pragma once
#include <string>

class InputHandler {
public:
    static std::string inputExpressionFromConsole();
    static std::string inputExpressionFromFile(const std::string& filename);
    static std::string generateRandomExpression();

    static int readValidInteger(const std::string& prompt);
    static std::string readValidFilename(const std::string& prompt);
};