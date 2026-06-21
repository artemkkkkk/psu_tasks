#ifdef _WIN32
#include <windows.h>
#endif

#include "HammingCode.h"
#include "HuffmanCode.h"
#include "VigenereCipher.h"
#include "InputHandler.h"
#include "Validator.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <ctime>

void task1HammingCode() {
    std::cout << "\n========== Задача 1: Код Хемминга ==========" << std::endl;

    try {
        std::cout << "\n=== Ввод данных ===" << std::endl;
        std::cout << "1. Ввод из консоли" << std::endl;
        std::cout << "2. Ввод из файла" << std::endl;
        std::cout << "3. Случайная генерация" << std::endl;
        std::cout << "0. Назад" << std::endl;

        int choice;
        std::cout << "Выберите способ ввода: ";
        std::cin >> choice;

        DynamicArray<int> data;
        switch (choice) {
            case 1:
                data = InputHandler::inputBinaryDataFromConsole();
                break;
            case 2: {
                std::string filename = InputHandler::readValidFilename("Введите имя файла: ");
                data = InputHandler::inputBinaryDataFromFile(filename);
                break;
            }
            case 3: {
                int count = InputHandler::readValidInteger("Введите количество бит: ");
                data = InputHandler::generateRandomBinaryData(count);
                break;
            }
            case 0:
                return;
            default:
                throw std::invalid_argument("Неверный выбор");
        }

        HammingCode hamming(data);

        std::cout << "\nИсходные данные: " << hamming.toString() << std::endl;

        hamming.encode();
        std::cout << "Закодированные данные: " << hamming.encodedToString() << std::endl;

        int errorPos = InputHandler::readValidInteger("Введите позицию для внесения ошибки (0 - без ошибки): ");
        if (errorPos > 0) {
            hamming.introduceError(errorPos);
            std::cout << "Данные с ошибкой: " << hamming.encodedToString() << std::endl;
            std::cout << "Обнаружена ошибка: " << (hamming.hasError() ? "Да" : "Нет") << std::endl;
        }

        hamming.decode();
        std::cout << "Декодированные данные: " << hamming.toString() << std::endl;

    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void task2HuffmanCode() {
    std::cout << "\n========== Задача 2: Код Хаффмана ==========" << std::endl;

    try {
        std::cout << "\n=== Ввод данных ===" << std::endl;
        std::cout << "1. Ввод из консоли" << std::endl;
        std::cout << "2. Ввод из файла" << std::endl;
        std::cout << "3. Случайная генерация" << std::endl;
        std::cout << "0. Назад" << std::endl;

        int choice;
        std::cout << "Выберите способ ввода: ";
        std::cin >> choice;

        std::string text;
        switch (choice) {
            case 1:
                text = InputHandler::inputTextFromConsole();
                break;
            case 2: {
                std::string filename = InputHandler::readValidFilename("Введите имя файла: ");
                text = InputHandler::inputTextFromFile(filename);
                break;
            }
            case 3:
                text = InputHandler::generateRandomText();
                break;
            case 0:
                return;
            default:
                throw std::invalid_argument("Неверный выбор");
        }

        HuffmanCode huffman;
        huffman.setText(text);
        huffman.encode();

        std::cout << "\nИсходный текст: " << huffman.getOriginalText() << std::endl;
        std::cout << "Длина исходного текста: " << huffman.getOriginalText().length() << " символов" << std::endl;

        std::cout << "\n";
        huffman.printCodes(std::cout);

        std::cout << "\nДерево кодирования:" << std::endl;
        huffman.printTree(std::cout);

        std::cout << "\nЗакодированный текст: " << huffman.getEncodedText() << std::endl;

        std::cout << "\nРазмер при равномерном кодировании: " << huffman.getUniformCodingSize() << " бит" << std::endl;
        std::cout << "Размер при кодировании Хаффмана: " << huffman.getHuffmanCodingSize() << " бит" << std::endl;

        if (huffman.getUniformCodingSize() > 0) {
            double compression = (1.0 - static_cast<double>(huffman.getHuffmanCodingSize()) / huffman.getUniformCodingSize()) * 100;
            std::cout << "Степень сжатия: " << compression << "%" << std::endl;
        }

        std::string decoded = huffman.decode(huffman.getEncodedText());
        std::cout << "\nДекодированный текст: " << decoded << std::endl;
        std::cout << "Совпадает с исходным: " << (decoded == huffman.getOriginalText() ? "Да" : "Нет") << std::endl;

    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void task3VigenereCipher() {
    std::cout << "\n========== Задача 3: Шифр Виженера ==========" << std::endl;

    try {
        std::cout << "\n=== Ввод ключа ===" << std::endl;
        std::cout << "1. Ввод из консоли" << std::endl;
        std::cout << "2. Ввод из файла" << std::endl;
        std::cout << "0. Назад" << std::endl;

        int keyChoice;
        std::cout << "Выберите способ ввода ключа: ";
        std::cin >> keyChoice;

        std::string key;
        switch (keyChoice) {
            case 1:
                key = InputHandler::inputKeyFromConsole();
                break;
            case 2: {
                std::string filename = InputHandler::readValidFilename("Введите имя файла с ключом: ");
                key = InputHandler::inputKeyFromFile(filename);
                break;
            }
            case 0:
                return;
            default:
                throw std::invalid_argument("Неверный выбор");
        }

        std::cout << "\n=== Ввод текста ===" << std::endl;
        std::cout << "1. Ввод из консоли" << std::endl;
        std::cout << "2. Ввод из файла" << std::endl;
        std::cout << "3. Случайная генерация" << std::endl;
        std::cout << "0. Назад" << std::endl;

        int textChoice;
        std::cout << "Выберите способ ввода текста: ";
        std::cin >> textChoice;

        std::string text;
        switch (textChoice) {
            case 1:
                text = InputHandler::inputTextFromConsole();
                break;
            case 2: {
                std::string filename = InputHandler::readValidFilename("Введите имя файла с текстом: ");
                text = InputHandler::inputTextFromFile(filename);
                break;
            }
            case 3:
                text = InputHandler::generateRandomText();
                break;
            case 0:
                return;
            default:
                throw std::invalid_argument("Неверный выбор");
        }

        VigenereCipher cipher(key);

        std::cout << "\nКлюч: " << cipher.getKey() << std::endl;
        std::cout << "Исходный текст: " << text << std::endl;

        std::string encrypted = cipher.encrypt(text);
        std::cout << "Зашифрованный текст: " << encrypted << std::endl;

        std::string decrypted = cipher.decrypt(encrypted);
        std::cout << "Дешифрованный текст: " << decrypted << std::endl;

        std::cout << "Совпадает с исходным: " << (decrypted == text ? "Да" : "Нет") << std::endl;

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
        std::cout << "1. Код Хемминга" << std::endl;
        std::cout << "2. Код Хаффмана" << std::endl;
        std::cout << "3. Шифр Виженера" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "==============================================" << std::endl;
        std::cout << "Выберите пункт меню: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Некорректный ввод. Попробуйте снова." << std::endl;
            continue;
        }

        if (!Validator::isValidMenuChoice(choice, 3)) {
            std::cout << "Неверный пункт меню. Попробуйте снова." << std::endl;
            continue;
        }

        switch (choice) {
            case 1:
                task1HammingCode();
                break;
            case 2:
                task2HuffmanCode();
                break;
            case 3:
                task3VigenereCipher();
                break;
            case 0:
                std::cout << "Выход из программы..." << std::endl;
                break;
        }
    } while (choice != 0);

    return 0;
}