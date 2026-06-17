#ifdef _WIN32
#include <windows.h>
#endif

#include "TreeFun1.h"
#include "TreeFun3.h"
#include "TreeFun11.h"
#include "InputHandler.h"
#include "Validator.h"
#include <iostream>
#include <vector>
#include <stdexcept>

std::vector<int> getInputValues(const std::string& treeType) {
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
            return {};
        default:
            throw std::invalid_argument("Неверный выбор");
    }
}

void task1TreeFun1() {
    std::cout << "\n========== TreeFun1: BST -> двусвязный список ==========" << std::endl;

    try {
        std::vector<int> values = getInputValues("бинарного дерева поиска");
        if (values.empty()) {
            return;
        }

        if (!Validator::isValidTreeValues(values)) {
            std::cout << "Некорректные значения для дерева" << std::endl;
            return;
        }

        TreeFun1 tree;
        for (int value : values) {
            tree.insertSearch(value);
        }

        std::cout << "\nИсходное дерево поиска:" << std::endl;
        tree.printGraphical(std::cout);

        DoublyList list = tree.convertToList();

        std::cout << "\nРезультирующий двусвязный список:" << std::endl;
        list.printForward(std::cout);
        list.printBackward(std::cout);
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void task2TreeFun3() {
    std::cout << "\n========== TreeFun3: Итератор in-order ==========" << std::endl;

    try {
        std::vector<int> values = getInputValues("бинарного дерева");
        if (values.empty()) {
            return;
        }

        if (!Validator::isValidTreeValues(values)) {
            std::cout << "Некорректные значения для дерева" << std::endl;
            return;
        }

        TreeFun3 tree;
        for (int value : values) {
            tree.insertSearch(value);
        }

        std::cout << "\nДерево:" << std::endl;
        tree.printGraphical(std::cout);

        std::cout << "\nОбход in-order (лево-корень-право) через итератор:" << std::endl;
        std::cout << "[";
        TreeFun3Iterator it = tree.begin();
        bool first = true;
        while (it.hasNext()) {
            if (!first) {
                std::cout << ", ";
            }
            std::cout << it.next();
            first = false;
        }
        std::cout << "]" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void task3TreeFun11() {
    std::cout << "\n========== TreeFun11: Пожар в дереве ==========" << std::endl;

    try {
        std::vector<int> values = getInputValues("бинарного дерева");
        if (values.empty()) {
            return;
        }

        if (!Validator::isValidTreeValues(values)) {
            std::cout << "Некорректные значения для дерева" << std::endl;
            return;
        }

        TreeFun11 tree;
        for (int value : values) {
            tree.insertSearch(value);
        }

        std::cout << "\nДерево:" << std::endl;
        tree.printGraphical(std::cout);

        int startValue = InputHandler::readValidInteger("Введите значение узла, где начинается пожар: ");

        try {
            std::vector<std::vector<int>> levels = tree.simulateFire(tree.findNode(startValue));
            std::cout << "\nПорядок сгорания узлов по уровням:" << std::endl;
            for (size_t i = 0; i < levels.size(); ++i) {
                std::cout << "Время " << i << ": [";
                for (size_t j = 0; j < levels[i].size(); ++j) {
                    std::cout << levels[i][j];
                    if (j < levels[i].size() - 1) {
                        std::cout << ", ";
                    }
                }
                std::cout << "]" << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
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

    int choice;
    do {
        std::cout << "\n==================== МЕНЮ ====================" << std::endl;
        std::cout << "1. TreeFun1: BST -> двусвязный список" << std::endl;
        std::cout << "2. TreeFun3: Итератор in-order" << std::endl;
        std::cout << "3. TreeFun11: Пожар в дереве" << std::endl;
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
                task1TreeFun1();
                break;
            case 2:
                task2TreeFun3();
                break;
            case 3:
                task3TreeFun11();
                break;
            case 0:
                std::cout << "Выход из программы..." << std::endl;
                break;
        }
    } while (choice != 0);

    return 0;
}