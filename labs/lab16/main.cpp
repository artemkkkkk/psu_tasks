#ifdef _WIN32
#include <windows.h>
#endif

#include "BinaryTree.h"
#include "InputHandler.h"
#include "Validator.h"
#include <iostream>
#include <stdexcept>
#include <ctime>

void buildTreeFromValues(BinaryTree& tree, const DynamicArray<int>& values, bool isSearchTree) {
    for (int i = 0; i < values.getSize(); ++i) {
        if (isSearchTree) {
            tree.insertSearch(values[i]);
        } else {
            tree.insertLevelOrder(values[i]);
        }
    }
}

DynamicArray<int> getInputValues(const std::string& treeType) {
    std::cout << "\n=== Ввод данных для " << treeType << " ===" << std::endl;
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
            return InputHandler::inputFromConsole();
        case 2: {
            std::string filename = InputHandler::readValidFilename("Введите имя файла: ");
            return InputHandler::inputFromFile(filename);
        }
        case 3: {
            int count = InputHandler::readValidPositiveInteger("Введите количество элементов: ");
            return InputHandler::generateRandom(count);
        }
        case 0:
            return DynamicArray<int>();
        default:
            throw std::invalid_argument("Неверный выбор");
    }
}

void task1PostOrder() {
    std::cout << "\n========== TreeWork1: Концевой обход ==========" << std::endl;

    try {
        DynamicArray<int> values = getInputValues("бинарного дерева");
        if (values.isEmpty()) {
            return;
        }

        BinaryTree tree;
        buildTreeFromValues(tree, values, false);

        std::cout << "\nГрафическое представление дерева:" << std::endl;
        tree.printGraphical(std::cout);

        std::cout << "\nРезультат концевого обхода (снизу-вверх):" << std::endl;
        tree.printPostOrder(std::cout);
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void task2Depth() {
    std::cout << "\n========== TreeWork14: Глубина дерева ==========" << std::endl;

    try {
        DynamicArray<int> values = getInputValues("бинарного дерева");
        if (values.isEmpty()) {
            return;
        }

        BinaryTree tree;
        buildTreeFromValues(tree, values, false);

        std::cout << "\nГрафическое представление дерева:" << std::endl;
        tree.printGraphical(std::cout);

        std::cout << "\nГлубина дерева: " << tree.getDepth() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void task3SecondMinimum() {
    std::cout << "\n========== TreeWork17: Второе минимальное значение ==========" << std::endl;

    try {
        DynamicArray<int> values = getInputValues("дерева поиска");
        if (values.isEmpty()) {
            return;
        }

        BinaryTree tree;
        buildTreeFromValues(tree, values, true);

        std::cout << "\nГрафическое представление дерева поиска:" << std::endl;
        tree.printGraphical(std::cout);

        try {
            int secondMin = tree.getSecondMinimum();
            std::cout << "\nВторое минимальное значение: " << secondMin << std::endl;
        } catch (const std::exception& e) {
            std::cout << "\nОшибка: " << e.what() << std::endl;
        }
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
        std::cout << "1. TreeWork1: Концевой обход бинарного дерева" << std::endl;
        std::cout << "2. TreeWork14: Глубина бинарного дерева" << std::endl;
        std::cout << "3. TreeWork17: Второе минимальное в дереве поиска" << std::endl;
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
                task1PostOrder();
                break;
            case 2:
                task2Depth();
                break;
            case 3:
                task3SecondMinimum();
                break;
            case 0:
                std::cout << "Выход из программы..." << std::endl;
                break;
        }
    } while (choice != 0);

    return 0;
}