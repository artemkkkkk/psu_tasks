#ifndef POINT_H
#define POINT_H

class Point {
private:
    int x;
    int y;

public:
    Point(int xValue, int yValue);

    int getX() const;
    int getY() const;

    void setX(int xValue);
    void setY(int yValue);

    void toString(char* buffer, int bufferSize) const;
    void print() const;
};

#endif