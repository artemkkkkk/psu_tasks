#include <iostream>

int main() {
    int N;
    double R;

    std::cout << "Введите количество точек N: ";
    std::cin >> N;
    std::cout << "Введите радиус круга R: ";
    std::cin >> R;

    int inside_count = 0;

    for (int i = 0; i < N; ++i) {
        double x, y;
        std::cout << "Введите координаты точки " << i + 1 << " (x y): ";
        std::cin >> x >> y;

        double distance_squared = x * x + y * y;

        if (distance_squared <= R * R) {
            inside_count++;
        }
    }

    std::cout << "Количество точек, лежащих внутри круга: " << inside_count << std::endl;

    return 0;
}