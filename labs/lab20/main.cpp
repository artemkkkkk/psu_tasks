#ifdef _WIN32
#include <windows.h>
#endif

#include "Time.h"
#include "InputHandler.h"
#include "Validator.h"
#include <iostream>
#include <stdexcept>
#include <ctime>

Time getInputTime(const std::string& description) {
    std::cout << "\n=== Ввод времени " << description << " ===" << std::endl;
    std::cout << "1. Ввод из консоли" << std::endl;
    std::cout << "2. Ввод из файла" << std::endl;
    std::cout << "3. Случайная генерация" << std::endl;
    std::cout << "0. Назад" << std::endl;

    int choice;
    std::cout << "Выберите способ ввода: ";
    std::cin >> choice;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        throw std::invalid_argument("Некорректный ввод");
    }

    switch (choice) {
        case 1:
            return InputHandler::inputTimeFromConsole();
        case 2: {
            std::string filename = InputHandler::readValidFilename("Введите имя файла: ");
            return InputHandler::inputTimeFromFile(filename);
        }
        case 3:
            return InputHandler::generateRandomTime();
        case 0:
            throw std::runtime_error("Отмена ввода");
        default:
            throw std::invalid_argument("Неверный выбор");
    }
}

unsigned int getInputMinutes(const std::string& description) {
    std::cout << "\n=== Ввод количества минут " << description << " ===" << std::endl;
    std::cout << "1. Ввод из консоли" << std::endl;
    std::cout << "2. Ввод из файла" << std::endl;
    std::cout << "3. Случайная генерация" << std::endl;
    std::cout << "0. Назад" << std::endl;

    int choice;
    std::cout << "Выберите способ ввода: ";
    std::cin >> choice;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        throw std::invalid_argument("Некорректный ввод");
    }

    switch (choice) {
        case 1:
            return InputHandler::inputMinutesFromConsole("Введите количество минут: ");
        case 2: {
            std::string filename = InputHandler::readValidFilename("Введите имя файла: ");
            return InputHandler::inputMinutesFromFile(filename);
        }
        case 3:
            return InputHandler::generateRandomMinutes();
        case 0:
            throw std::runtime_error("Отмена ввода");
        default:
            throw std::invalid_argument("Неверный выбор");
    }
}

void demonstrateConstructors() {
    std::cout << "\n========== Демонстрация конструкторов ==========" << std::endl;

    Time t1;
    std::cout << "Конструктор по умолчанию: " << t1 << std::endl;

    Time t2(14, 30);
    std::cout << "Конструктор (часы, минуты): " << t2 << std::endl;

    Time t3(150);
    std::cout << "Конструктор (общее количество минут = 150): " << t3 << std::endl;

    Time t4(25, 70);
    std::cout << "Конструктор с нормализацией (25:70): " << t4 << std::endl;
}

void demonstrateAddMinutes() {
    std::cout << "\n========== Добавление минут (метод addMinutes) ==========" << std::endl;

    try {
        Time time = getInputTime("(первое время)");
        unsigned int minutesToAdd = getInputMinutes("(для добавления)");

        Time result = time.addMinutes(minutesToAdd);
        std::cout << "\nИсходное время: " << time << std::endl;
        std::cout << "Добавляем " << minutesToAdd << " минут" << std::endl;
        std::cout << "Результат: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void demonstrateUnaryOperators() {
    std::cout << "\n========== Унарные операторы ++ и -- ==========" << std::endl;

    try {
        Time time = getInputTime("");

        std::cout << "\nИсходное время: " << time << std::endl;

        Time preInc = ++time;
        std::cout << "Префиксный инкремент (++time): " << preInc << std::endl;

        Time postInc = time++;
        std::cout << "Постфиксный инкремент (time++): " << postInc << " (текущее значение: " << time << ")" << std::endl;

        Time preDec = --time;
        std::cout << "Префиксный декремент (--time): " << preDec << std::endl;

        Time postDec = time--;
        std::cout << "Постфиксный декремент (time--): " << postDec << " (текущее значение: " << time << ")" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void demonstrateTypeConversions() {
    std::cout << "\n========== Операции приведения типа ==========" << std::endl;

    try {
        Time time = getInputTime("");

        short int hours = static_cast<short int>(time);
        std::cout << "\nИсходное время: " << time << std::endl;
        std::cout << "Явное приведение к short int (часы): " << hours << std::endl;

        bool isNonZero = static_cast<bool>(time);
        std::cout << "Явное приведение к bool (не нулевое?): " << (isNonZero ? "true" : "false") << std::endl;

        if (time) {
            std::cout << "Неявное приведение к bool в if: время не нулевое" << std::endl;
        } else {
            std::cout << "Неявное приведение к bool в if: время нулевое" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void demonstrateBinaryOperators() {
    std::cout << "\n========== Бинарные операторы + и - ==========" << std::endl;

    try {
        Time time1 = getInputTime("(первое время)");
        Time time2 = getInputTime("(второе время)");
        unsigned int minutes = getInputMinutes("(для операций)");

        std::cout << "\nПервое время: " << time1 << std::endl;
        std::cout << "Второе время: " << time2 << std::endl;
        std::cout << "Минуты: " << minutes << std::endl;

        std::cout << "\ntime1 + time2 = " << (time1 + time2) << std::endl;
        std::cout << "time1 + " << minutes << " = " << (time1 + minutes) << std::endl;
        std::cout << "time1 - time2 = " << (time1 - time2) << std::endl;
        std::cout << "time1 - " << minutes << " = " << (time1 - minutes) << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void demonstrateOutputOperator() {
    std::cout << "\n========== Оператор вывода ==========" << std::endl;

    try {
        Time time = getInputTime("");
        std::cout << "\nВывод через operator<<: " << time << std::endl;
        std::cout << "Вывод через toString(): " << time.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    srand(static_cast<unsigned>(time(nullptr)));

    int choice;
    do {
        std::cout << "\n==================== МЕНЮ ====================" << std::endl;
        std::cout << "1. Демонстрация конструкторов" << std::endl;
        std::cout << "2. Добавление минут (addMinutes)" << std::endl;
        std::cout << "3. Унарные операторы ++ и --" << std::endl;
        std::cout << "4. Операции приведения типа" << std::endl;
        std::cout << "5. Бинарные операторы + и -" << std::endl;
        std::cout << "6. Оператор вывода" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "==============================================" << std::endl;
        std::cout << "Выберите пункт меню: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Некорректный ввод. Попробуйте снова." << std::endl;
            continue;
        }

        if (!Validator::isValidMenuChoice(choice, 6)) {
            std::cout << "Неверный пункт меню. Попробуйте снова." << std::endl;
            continue;
        }

        switch (choice) {
            case 1:
                demonstrateConstructors();
                break;
            case 2:
                demonstrateAddMinutes();
                break;
            case 3:
                demonstrateUnaryOperators();
                break;
            case 4:
                demonstrateTypeConversions();
                break;
            case 5:
                demonstrateBinaryOperators();
                break;
            case 6:
                demonstrateOutputOperator();
                break;
            case 0:
                std::cout << "Выход из программы..." << std::endl;
                break;
        }
    } while (choice != 0);

    return 0;
}