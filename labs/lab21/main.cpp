#ifdef _WIN32
#include <windows.h>
#endif

#include "UndirectedGraph.h"
#include "DirectedGraph.h"
#include "InputHandler.h"
#include "Validator.h"
#include <iostream>
#include <stdexcept>

void task1Graf1() {
    std::cout << "\n========== Graf1: Степени вершин неориентированного графа ==========" << std::endl;

    try {
        std::cout << "\n=== Ввод данных ===" << std::endl;
        std::cout << "1. Ввод из консоли" << std::endl;
        std::cout << "2. Ввод из файла" << std::endl;
        std::cout << "3. Случайная генерация" << std::endl;
        std::cout << "0. Назад" << std::endl;

        int choice;
        std::cout << "Выберите способ ввода: ";
        std::cin >> choice;

        UndirectedGraph graph;
        switch (choice) {
            case 1:
                graph.loadFromConsole();
                break;
            case 2: {
                std::string filename = InputHandler::readValidFilename("Введите имя файла: ");
                graph.loadFromFile(filename);
                break;
            }
            case 3: {
                int vertexCount = InputHandler::readValidPositiveInteger("Введите количество вершин: ");
                double density = InputHandler::readValidDensity("Введите плотность графа (0.0-1.0): ");
                graph.generateRandom(vertexCount, density);
                break;
            }
            case 0:
                return;
            default:
                throw std::invalid_argument("Неверный выбор");
        }

        std::cout << "\n";
        graph.print(std::cout);
        std::cout << "\n";
        graph.printDegrees(std::cout);
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void task2Graf4() {
    std::cout << "\n========== Graf4: Поиск в ширину в ориентированном графе ==========" << std::endl;

    try {
        std::cout << "\n=== Ввод данных ===" << std::endl;
        std::cout << "1. Ввод из консоли" << std::endl;
        std::cout << "2. Ввод из файла" << std::endl;
        std::cout << "3. Случайная генерация" << std::endl;
        std::cout << "0. Назад" << std::endl;

        int choice;
        std::cout << "Выберите способ ввода: ";
        std::cin >> choice;

        DirectedGraph graph;
        switch (choice) {
            case 1:
                graph.loadFromConsole();
                break;
            case 2: {
                std::string filename = InputHandler::readValidFilename("Введите имя файла: ");
                graph.loadFromFile(filename);
                break;
            }
            case 3: {
                int vertexCount = InputHandler::readValidPositiveInteger("Введите количество вершин: ");
                double density = InputHandler::readValidDensity("Введите плотность графа (0.0-1.0): ");
                graph.generateRandom(vertexCount, density);
                break;
            }
            case 0:
                return;
            default:
                throw std::invalid_argument("Неверный выбор");
        }

        std::cout << "\n";
        graph.print(std::cout);

        int startVertex = InputHandler::readValidVertexNumber("Введите номер стартовой вершины (1-" + std::to_string(graph.getVertexCount()) + "): ", graph.getVertexCount());

        std::cout << "\n";
        graph.printBfsResult(std::cout, startVertex - 1);
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void task3Graf8() {
    std::cout << "\n========== Graf8: Города с минимальным количеством пересадок ==========" << std::endl;

    try {
        std::cout << "\n=== Ввод данных ===" << std::endl;
        std::cout << "1. Ввод из консоли" << std::endl;
        std::cout << "2. Ввод из файла" << std::endl;
        std::cout << "3. Случайная генерация" << std::endl;
        std::cout << "0. Назад" << std::endl;

        int choice;
        std::cout << "Выберите способ ввода: ";
        std::cin >> choice;

        DirectedGraph graph;
        switch (choice) {
            case 1:
                graph.loadFromConsole();
                break;
            case 2: {
                std::string filename = InputHandler::readValidFilename("Введите имя файла: ");
                graph.loadFromFile(filename);
                break;
            }
            case 3: {
                int vertexCount = InputHandler::readValidPositiveInteger("Введите количество вершин: ");
                double density = InputHandler::readValidDensity("Введите плотность графа (0.0-1.0): ");
                graph.generateRandom(vertexCount, density);
                break;
            }
            case 0:
                return;
            default:
                throw std::invalid_argument("Неверный выбор");
        }

        std::cout << "\n";
        graph.print(std::cout);

        int startCity = InputHandler::readValidVertexNumber("Введите номер стартового города (1-" + std::to_string(graph.getVertexCount()) + "): ", graph.getVertexCount());
        int minTransfers = InputHandler::readValidNonNegativeInteger("Введите минимальное количество пересадок L: ");

        std::cout << "\n";
        graph.printTransfersResult(std::cout, startCity - 1, minTransfers);
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
        std::cout << "1. Graf1: Степени вершин неориентированного графа" << std::endl;
        std::cout << "2. Graf4: Поиск в ширину в ориентированном графе" << std::endl;
        std::cout << "3. Graf8: Города с минимальным количеством пересадок" << std::endl;
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
                task1Graf1();
                break;
            case 2:
                task2Graf4();
                break;
            case 3:
                task3Graf8();
                break;
            case 0:
                std::cout << "Выход из программы..." << std::endl;
                break;
        }
    } while (choice != 0);

    return 0;
}