#include "Point.h"
#include <cmath>
#include <sstream>

Point::Point(double x, double y) : x(x), y(y) {}

Point::Point() : x(0), y(0) {}

double Point::getX() const {
    return x;
}

double Point::getY() const {
    return y;
}

void Point::setX(double x) {
    this->x = x;
}

void Point::setY(double y) {
    this->y = y;
}

std::string Point::toString() const {
    std::ostringstream oss;
    oss << "{" << x << ";" << y << "}";
    return oss.str();
}

double Point::distanceTo(const Point& other) const {
    double dx = x - other.x;
    double dy = y - other.y;
    return std::sqrt(dx * dx + dy * dy);
}