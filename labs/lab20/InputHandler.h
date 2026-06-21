#pragma once
#include "Time.h"
#include <string>

class InputHandler {
public:
    static Time inputTimeFromConsole();
    static Time inputTimeFromFile(const std::string& filename);
    static Time generateRandomTime();

    static unsigned int inputMinutesFromConsole(const std::string& prompt);
    static unsigned int inputMinutesFromFile(const std::string& filename);
    static unsigned int generateRandomMinutes();

    static int readValidInteger(const std::string& prompt);
    static unsigned int readValidUnsignedInt(const std::string& prompt);
    static std::string readValidFilename(const std::string& prompt);
};