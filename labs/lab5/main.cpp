#include <iostream>
#include <string>
#include <fstream>
#include "string_tasks.h"
#include "password_gen.h"
#include "checker.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // Включаем UTF-8 в выводе консоли
    SetConsoleCP(CP_UTF8);        // (опционально) для ввода
#endif

    std::cout << "=== Лабораторная работа №5 (Вариант 1) ===\n\n";

    // Задача 1: String41
    std::string s1;
    std::cout << "[String41] Введите строку из русских слов:\n";
    getline(std::cin, s1);
    std::cout << "Количество слов: " << CountWords(s1) << "\n\n";

    // Задача 2: Str13
    std::string s2;
    std::cout << "[Str13] Введите строку с < и >:\n";
    getline(std::cin, s2);
    std::cout << "Результат: " << ReplaceAngleBrackets(s2) << "\n\n";

    // Задача 3: Str22
    char ch;
    std::cout << "[Str22] Введите один символ: ";
    std::cin >> ch;
    auto ct = CheckCharType(ch);
    std::cout << "1) Буква: " << (ct.isLetter ? "True" : "False") << "\n";
    std::cout << "2) Цифра: " << (ct.isDigit ? "True" : "False") << "\n";
    std::cout << "3) Строчная: " << (ct.isLower ? "True" : "False") << "\n";
    std::cout << "4) Заглавная: " << (ct.isUpper ? "True" : "False") << "\n";
    std::cout << "5) Управляющий (0–32): " << (ct.isControl ? "True" : "False") << "\n\n";

    // Задача 4: Str36
    std::string s3;
    std::cout << "[Str36] Введите строку:\n";
    std::cin.ignore();
    getline(std::cin, s3);
    auto [cnt, chars] = CountUniqueNonPunctChars(s3);
    std::cout << "Уникальных символов (без пунктуации): " << cnt << "\n";
    std::cout << "Символы: " << chars << "\n\n";

    // Задача 5: Str26
    std::string bin;
    std::cout << "[Str26] Введите двоичное число: ";
    std::cin >> bin;
    if (IsValidBinary(bin)) {
        std::cout << "Десятичное значение: " << BinaryToDecimal(bin) << "\n\n";
    } else {
        std::cout << "False\n\n";
    }

    // Задача 6: Генератор паролей
    int level;
    std::cout << "[Задача 6] Выберите уровень сложности (1–3):\n";
    std::cout << "1 — простой (8 строчных букв)\n";
    std::cout << "2 — средний (12 букв+цифр)\n";
    std::cout << "3 — сложный (16 символов всех типов)\n";
    std::cout << "Ваш выбор: ";
    std::cin >> level;
    try {
        std::cout << "Ваш пароль: " << GeneratePassword(level) << "\n\n";
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << "\n\n";
    }

    // Задача 7: Five1
    std::cout << "[Five1] Проверка домашней работы первоклассника.\n";
    std::cout << "Убедитесь, что файл FN1.txt существует в папке проекта.\n";
    try {
        CheckFirstGraderHomework("FN1.txt", "FN2.txt");
        std::cout << "Результат записан в FN2.txt\n\n";
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при проверке: " << e.what() << "\n\n";
    }

    std::cout << "\n";
    std::cout << "≽^•⩊•^≼ \n\n";
    std::cout << "Введите любой символ для завершения \n";
    std::cin >> ch;
    return 0;
}