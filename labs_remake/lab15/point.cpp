#include "point.h"
#include <iostream>
#include <cstdio>

Point::Point(int xValue, int yValue) : x(xValue), y(yValue) {}

int Point::getX() const {
    return x;
}

int Point::getY() const {
    return y;
}

void Point::setX(int xValue) {
    x = xValue;
}

void Point::setY(int yValue) {
    y = yValue;
}

void Point::toString(char* buffer, int bufferSize) const {
    if (!buffer || bufferSize <= 0) {
        return;
    }

    std::snprintf(buffer, bufferSize, "{%d;%d}", x, y);
}

void Point::print() const {
    char buffer[64];
    toString(buffer, 64);
    std::cout << buffer << '\n';
}