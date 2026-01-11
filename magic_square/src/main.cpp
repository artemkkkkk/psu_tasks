#include "../include/magic_square.h"
#include "../include/file_io.h"
#include <iostream>
#include <string>
#include <limits>
#include <sstream>
#include <iomanip>

// Вспомогательная функция для безопасного ввода целого числа
bool ReadInt(int& out, const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    if (!std::getline(std::cin, line)) {
        return false;
    }
    std::istringstream iss(line);
    if (!(iss >> out) || !iss.eof()) {
        return false;
    }
    return true;
}

// Отображение текущего квадрата
void DisplaySquare(const std::vector<std::vector<int>>& square) {
    if (square.empty()) {
        std::cout << "Квадрат ещё не создан.\n";
        return;
    }

    int n = square.size();
    int width = static_cast<int>(std::to_string(n * n).length()) + 1;

    for (const auto& row : square) {
        for (int val : row) {
            std::cout << std::setw(width) << val;
        }
        std::cout << '\n';
    }
}

// Отображение сумм
void DisplaySums(const std::vector<std::vector<int>>& square) {
    if (square.empty()) {
        std::cout << "Нет данных для отображения сумм.\n";
        return;
    }

    auto rows = GetRowSums(square);
    auto cols = GetColumnSums(square);
    auto diags = GetDiagonalSums(square);

    std::cout << "\nСуммы строк: ";
    for (int s : rows) std::cout << s << " ";
    std::cout << "\nСуммы столбцов: ";
    for (int s : cols) std::cout << s << " ";
    std::cout << "\nГлавная диагональ: " << diags.first;
    std::cout << "\nПобочная диагональ: " << diags.second << "\n\n";
}

// Главное меню
void ShowMenu() {
    std::cout << "\n=== Магический квадрат ===\n";
    std::cout << "1. Создать новый магический квадрат\n";
    std::cout << "2. Показать квадрат\n";
    std::cout << "3. Проверить корректность\n";
    std::cout << "4. Показать суммы строк, столбцов и диагоналей\n";
    std::cout << "5. Сохранить квадрат в файл\n";
    std::cout << "6. Выход\n";
    std::cout << "Выберите пункт меню (1–6): ";
}

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // Включаем UTF-8 в выводе консоли
    SetConsoleCP(CP_UTF8);        // (опционально) для ввода
#endif

    std::vector<std::vector<int>> current_square;
    int choice;

    while (true) {
        ShowMenu();
        if (!ReadInt(choice, "")) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка: введите число от 1 до 6.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                int n;
                if (!ReadInt(n, "Введите нечётный порядок квадрата (n > 0): ")) {
                    std::cout << "Ошибка: введите корректное целое число.\n";
                    break;
                }
                try {
                    current_square = GenerateMagicSquare(n);
                    std::cout << "Магический квадрат " << n << "x" << n
                              << " успешно создан!\n";
                } catch (const std::exception& e) {
                    std::cout << "Ошибка: " << e.what() << "\n";
                    current_square.clear();
                }
                break;
            }
            case 2:
                DisplaySquare(current_square);
                break;
            case 3:
                if (current_square.empty()) {
                    std::cout << "Сначала создайте квадрат (пункт 1).\n";
                } else {
                    if (IsMagicSquare(current_square)) {
                        std::cout << "✅ Квадрат корректен (является магическим)!\n";
                    } else {
                        std::cout << "❌ Квадрат НЕ является магическим.\n";
                    }
                }
                break;
            case 4:
                DisplaySums(current_square);
                break;
            case 5: {
                if (current_square.empty()) {
                    std::cout << "Сначала создайте квадрат (пункт 1).\n";
                    break;
                }
                std::string basename;
                std::cout << "Введите имя файла для сохранения (например, test_square): ";
                std::getline(std::cin, basename);
                if (basename.empty()) {
                    basename = "magic_square";
                }

                size_t last_dot = basename.find_last_of('.');
                if (last_dot != std::string::npos && last_dot > 0 && last_dot < basename.length() - 1) {
                    basename = basename.substr(0, last_dot);
                }

                std::string filename = basename + ".txt";

                if (SaveSquareToFile(current_square, filename)) {
                    std::cout << "Квадрат успешно сохранён в файл '" << filename << "'.\n";
                } else {
                    std::cout << "Ошибка: не удалось записать файл '" << filename << "'.\n";
                }
                break;
            }
            case 6:
                std::cout << "Выход из программы. До свидания!\n";
                return 0;
            default:
                std::cout << "Неверный выбор. Введите число от 1 до 6.\n";
        }
    }
}