#include "shapes.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>

std::string colorToString(Color c) {
    switch (c) {
        case Color::Red: return "Red";
        case Color::Green: return "Green";
        case Color::Blue: return "Blue";
        case Color::Yellow: return "Yellow";
        case Color::Black: return "Black";
        default: return "Unknown";
    }
}

Color stringToColor(const std::string& s) {
    static std::map<std::string, Color> m = {
        {"red", Color::Red}, {"green", Color::Green},
        {"blue", Color::Blue}, {"yellow", Color::Yellow},
        {"black", Color::Black}
    };
    auto it = m.find(s);
    if (it != m.end()) return it->second;
    return Color::Black;
}

void inputFigure(Figure& fig) {
    std::string colorStr;
    std::cout << "Цвет (red/green/blue/yellow/black): ";
    std::cin >> colorStr;
    fig.color = stringToColor(colorStr);

    std::cout << "Тип (0=CIRCLE, 1=SQUARE, 2=SEGMENT): ";
    int t; std::cin >> t;
    fig.type = static_cast<ShapeType>(t);

    if (fig.type == ShapeType::Circle) {
        std::cout << "Радиус (short): "; std::cin >> fig.data.radius;
    } else if (fig.type == ShapeType::Square) {
        std::cout << "Сторона (int): "; std::cin >> fig.data.side;
    } else if (fig.type == ShapeType::Segment) {
        std::cout << "Длина (float): "; std::cin >> fig.data.length;
    }
}

void saveFiguresToFile(const Figure* figures, int n, const char* filename) {
    std::ofstream fout(filename);
    for (int i = 0; i < n; ++i) {
        fout << static_cast<int>(figures[i].type) << " "
             << static_cast<int>(figures[i].color) << " ";
        if (figures[i].type == ShapeType::Circle)
            fout << figures[i].data.radius;
        else if (figures[i].type == ShapeType::Square)
            fout << figures[i].data.side;
        else
            fout << figures[i].data.length;
        fout << "\n";
    }
    fout.close();
}

void printFiguresTable(const Figure* figures, int n) {
    std::cout << "\nТаблица фигур:\n";
    std::cout << "Тип\t\tЦвет\t\tПараметр\n";
    std::cout << "----------------------------------------\n";
    for (int i = 0; i < n; ++i) {
        std::string typeStr;
        switch (figures[i].type) {
            case ShapeType::Circle: typeStr = "Круг"; break;
            case ShapeType::Square: typeStr = "Квадрат"; break;
            case ShapeType::Segment: typeStr = "Отрезок"; break;
        }
        std::string param;
        if (figures[i].type == ShapeType::Circle)
            param = std::to_string(figures[i].data.radius);
        else if (figures[i].type == ShapeType::Square)
            param = std::to_string(figures[i].data.side);
        else
            param = std::to_string(figures[i].data.length);

        std::cout << typeStr << "\t\t"
                  << colorToString(figures[i].color) << "\t\t"
                  << param << "\n";
    }
}