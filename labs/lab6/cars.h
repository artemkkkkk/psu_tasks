#ifndef CARS_H
#define CARS_H

#include <vector>
#include <string>

struct Car {
    std::string brand;
    std::string model;
    int year;
};

void runCarManager();

#endif // CARS_H