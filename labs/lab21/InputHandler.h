#pragma once
#include <string>

class InputHandler {
public:
    static int readValidPositiveInteger(const std::string& prompt);
    static int readValidNonNegativeInteger(const std::string& prompt);
    static int readValidVertexNumber(const std::string& prompt, int vertexCount);
    static double readValidDensity(const std::string& prompt);
    static std::string readValidFilename(const std::string& prompt);
};