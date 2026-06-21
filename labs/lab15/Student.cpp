#include "Student.h"
#include <sstream>

Student::Student(const std::string& name) : name(name) {}

Student::Student(const std::string& name, const DynamicArray<int>& grades)
    : name(name), grades(grades) {}

Student::Student() : name("") {}

std::string Student::getName() const {
    return name;
}

const DynamicArray<int>& Student::getGrades() const {
    return grades;
}

void Student::setName(const std::string& name) {
    this->name = name;
}

void Student::setGrades(const DynamicArray<int>& grades) {
    this->grades = grades;
}

void Student::setGrade(int index, int grade) {
    if (index >= 0 && index < grades.getSize()) {
        grades[index] = grade;
    }
}

std::string Student::toString() const {
    std::ostringstream oss;
    oss << name << ":[";
    for (int i = 0; i < grades.getSize(); ++i) {
        oss << grades[i];
        if (i < grades.getSize() - 1) {
            oss << ",";
        }
    }
    oss << "]";
    return oss.str();
}