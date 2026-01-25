#include <iostream>

int main() {
    std::cout << "Введите координаты трех вершин прямоугольника (x1 y1 x2 y2 x3 y3): ";
    int x1, y1, x2, y2, x3, y3;
    std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

    int x4 = x1 ^ x2 ^ x3;
    int y4 = y1 ^ y2 ^ y3;

    std::cout << "Координаты четвертой вершины: (" << x4 << ", " << y4 << ")" << std::endl;

    return 0;
}