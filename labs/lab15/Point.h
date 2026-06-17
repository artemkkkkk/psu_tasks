#pragma once
#include <string>

class Point {
private:
    double x;
    double y;

public:
    Point(double x, double y);
    Point();
    
    double getX() const;
    double getY() const;
    void setX(double x);
    void setY(double y);
    
    std::string toString() const;
    double distanceTo(const Point& other) const;
};