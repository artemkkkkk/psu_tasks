#pragma once
#include "Point.h"
#include "Line.h"
#include "Student.h"
#include <string>
#include <vector>

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
    
private:
    static std::string generateRandomName();
    static std::vector<int> generateRandomGrades();
};