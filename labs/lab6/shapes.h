#ifndef SHAPES_H
#define SHAPES_H

#include <string>

enum class Color {
    Red, Green, Blue, Yellow, Black
};

enum class ShapeType {
    Circle, Square, Segment
};

union ShapeData {
    short radius;      // for Circle
    int side;          // for Square
    float length;      // for Segment

    ShapeData() {}
    ~ShapeData() {}
};

struct Figure {
    Color color;
    ShapeType type;
    ShapeData data;
};

std::string colorToString(Color c);
Color stringToColor(const std::string& s);
void inputFigure(Figure& fig);
void saveFiguresToFile(const Figure* figures, int n, const char* filename);
void printFiguresTable(const Figure* figures, int n);

#endif // SHAPES_H