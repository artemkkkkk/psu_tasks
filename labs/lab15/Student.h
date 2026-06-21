#pragma once
#include <string>
#include "DynamicArray.h"

class Student {
private:
    std::string name;
    DynamicArray<int> grades;

public:
    Student(const std::string& name);
    Student(const std::string& name, const DynamicArray<int>& grades);
    Student();

    std::string getName() const;
    const DynamicArray<int>& getGrades() const;
    void setName(const std::string& name);
    void setGrades(const DynamicArray<int>& grades);
    void setGrade(int index, int grade);

    std::string toString() const;
};