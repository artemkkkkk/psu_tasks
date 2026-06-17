#include "Student.h"
#include <sstream>

Student::Student(const std::string& name) : name(name) {}

Student::Student(const std::string& name, const std::vector<int>& grades) 
    : name(name), grades(grades) {}

Student::Student() : name("") {}

std::string Student::getName() const {
    return name;
}

const std::vector<int>& Student::getGrades() const {
    return grades;
}

void Student::setName(const std::string& name) {
    this->name = name;
}

void Student::setGrades(const std::vector<int>& grades) {
    this->grades = grades;
}

void Student::setGrade(size_t index, int grade) {
    if (index < grades.size()) {
        grades[index] = grade;
    }
}

std::string Student::toString() const {
    std::ostringstream oss;
    oss << name << ":[";
    for (size_t i = 0; i < grades.size(); ++i) {
        oss << grades[i];
        if (i < grades.size() - 1) {
            oss << ",";
        }
    }
    oss << "]";
    return oss.str();
}