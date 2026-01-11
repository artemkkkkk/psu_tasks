#include "cars.h"
#include <iostream>
#include <algorithm>
#include <numeric>

std::vector<Car> carList;

void addCar() {
    Car c;
    std::cout << "Марка: "; std::cin >> c.brand;
    std::cout << "Модель: "; std::cin >> c.model;
    std::cout << "Год выпуска: "; std::cin >> c.year;
    carList.push_back(c);
    std::cout << "Автомобиль добавлен.\n";
}

void printAllCars() {
    if (carList.empty()) {
        std::cout << "Нет автомобилей.\n";
        return;
    }
    for (size_t i = 0; i < carList.size(); ++i) {
        std::cout << i + 1 << ". " << carList[i].brand << " "
                  << carList[i].model << " (" << carList[i].year << ")\n";
    }
}

void searchByBrand() {
    std::string brand;
    std::cout << "Введите марку: "; std::cin >> brand;
    int count = 0;
    for (const auto& car : carList)
        if (car.brand == brand) ++count;
    std::cout << "Найдено: " << count << " авто марки " << brand << "\n";
}

void searchByYearRange() {
    int y1, y2;
    std::cout << "Год от: "; std::cin >> y1;
    std::cout << "Год до: "; std::cin >> y2;
    if (y1 > y2) std::swap(y1, y2);
    bool found = false;
    for (const auto& car : carList) {
        if (car.year >= y1 && car.year <= y2) {
            std::cout << car.brand << " " << car.model << " (" << car.year << ")\n";
            found = true;
        }
    }
    if (!found) std::cout << "Ничего не найдено.\n";
}

double averageYear() {
    if (carList.empty()) return 0.0;
    double sum = std::accumulate(carList.begin(), carList.end(), 0,
        [](int acc, const Car& c) { return acc + c.year; });
    return sum / carList.size();
}

void editCar() {
    printAllCars();
    if (carList.empty()) return;
    int idx;
    std::cout << "Номер для редактирования: "; std::cin >> idx;
    if (idx < 1 || idx > (int)carList.size()) {
        std::cout << "Неверный номер.\n";
        return;
    }
    --idx;
    std::cout << "Новая марка (" << carList[idx].brand << "): ";
    std::string s; std::cin >> s;
    if (!s.empty()) carList[idx].brand = s;
    std::cout << "Новая модель (" << carList[idx].model << "): ";
    std::cin >> s;
    if (!s.empty()) carList[idx].model = s;
    std::cout << "Новый год (" << carList[idx].year << "): ";
    int y; std::cin >> y;
    carList[idx].year = y;
    std::cout << "Изменено.\n";
}

void deleteCar() {
    printAllCars();
    if (carList.empty()) return;
    int idx;
    std::cout << "Номер для удаления: "; std::cin >> idx;
    if (idx < 1 || idx > (int)carList.size()) {
        std::cout << "Неверный номер.\n";
        return;
    }
    carList.erase(carList.begin() + idx - 1);
    std::cout << "Удалено.\n";
}

void runCarManager() {
    int choice;
    do {
        std::cout << "\n=== Управление автомобилями ===\n";
        std::cout << "1. Добавить\n";
        std::cout << "2. Показать все\n";
        std::cout << "3. Поиск по марке\n";
        std::cout << "4. Поиск по диапазону лет\n";
        std::cout << "5. Средний год выпуска\n";
        std::cout << "6. Редактировать\n";
        std::cout << "7. Удалить\n";
        std::cout << "0. Назад\n";
        std::cout << "Выбор: ";
        std::cin >> choice;

        switch (choice) {
            case 1: addCar(); break;
            case 2: printAllCars(); break;
            case 3: searchByBrand(); break;
            case 4: searchByYearRange(); break;
            case 5: std::cout << "Средний год: " << averageYear() << "\n"; break;
            case 6: editCar(); break;
            case 7: deleteCar(); break;
            case 0: break;
            default: std::cout << "Неверный выбор.\n";
        }
    } while (choice != 0);
}