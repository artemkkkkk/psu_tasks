#pragma once
#include <string>
#include <vector>

class Student {
private:
    std::string name;
    std::vector<int> grades;

public:
    Student(const std::string& name);
    Student(const std::string& name, const std::vector<int>& grades);
    Student();
    
    std::string getName() const;
    const std::vector<int>& getGrades() const;
    void setName(const std::string& name);
    void setGrades(const std::vector<int>& grades);
    void setGrade(size_t index, int grade);
    
    std::string toString() const;
};