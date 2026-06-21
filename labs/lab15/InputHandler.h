#pragma once
#include "Point.h"
#include "Line.h"
#include "Student.h"
#include "DynamicArray.h"
#include <string>

class InputHandler {
public:
    static Point inputPointFromConsole();
    static Line inputLineFromConsole();
    static Student inputStudentFromConsole();

    static Point inputPointFromFile(const std::string& filename);
    static Line inputLineFromFile(const std::string& filename);
    static Student inputStudentFromFile(const std::string& filename);

    static Point generateRandomPoint();
    static Line generateRandomLine();
    static Student generateRandomStudent();

    static double readValidDouble(const std::string& prompt);
    static int readValidInteger(const std::string& prompt);
    static int readValidPositiveInteger(const std::string& prompt);
    static std::string readValidFilename(const std::string& prompt);

private:
    static std::string generateRandomName();
    static DynamicArray<int> generateRandomGrades();
};