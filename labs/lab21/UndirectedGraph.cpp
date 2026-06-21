#include "UndirectedGraph.h"
#include <fstream>
#include <cstdlib>
#include <stdexcept>

UndirectedGraph::UndirectedGraph() : Graph() {}

UndirectedGraph::UndirectedGraph(int vertexCount) : Graph(vertexCount) {}

void UndirectedGraph::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }
    int n;
    if (!(file >> n) || n <= 0) {
        throw std::runtime_error("Некорректное количество вершин");
    }
    vertexCount = n;
    initializeMatrix(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!(file >> adjacencyMatrix[i][j])) {
                throw std::runtime_error("Некорректный формат матрицы смежности");
            }
            if (adjacencyMatrix[i][j] != 0 && adjacencyMatrix[i][j] != 1) {
                throw std::runtime_error("Матрица смежности должна содержать 0 или 1");
            }
        }
    }
}

void UndirectedGraph::loadFromConsole() {
    int n;
    std::cout << "Введите количество вершин: ";
    std::cin >> n;
    if (n <= 0) {
        throw std::invalid_argument("Количество вершин должно быть положительным");
    }
    vertexCount = n;
    initializeMatrix(n);
    std::cout << "Введите матрицу смежности (" << n << "x" << n << "):" << std::endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> adjacencyMatrix[i][j];
            if (adjacencyMatrix[i][j] != 0 && adjacencyMatrix[i][j] != 1) {
                throw std::invalid_argument("Матрица смежности должна содержать 0 или 1");
            }
        }
    }
}

void UndirectedGraph::generateRandom(int vertexCount, double density) {
    if (vertexCount <= 0) {
        throw std::invalid_argument("Количество вершин должно быть положительным");
    }
    this->vertexCount = vertexCount;
    initializeMatrix(vertexCount);
    for (int i = 0; i < vertexCount; ++i) {
        for (int j = i; j < vertexCount; ++j) {
            if (i == j) {
                double r = static_cast<double>(rand()) / RAND_MAX;
                adjacencyMatrix[i][j] = (r < density * 0.1) ? 1 : 0;
            } else {
                double r = static_cast<double>(rand()) / RAND_MAX;
                int value = (r < density) ? 1 : 0;
                adjacencyMatrix[i][j] = value;
                adjacencyMatrix[j][i] = value;
            }
        }
    }
}

DynamicArray<int> UndirectedGraph::calculateDegrees() const {
    DynamicArray<int> degrees;
    for (int i = 0; i < vertexCount; ++i) {
        degrees.pushBack(0);
    }
    for (int i = 0; i < vertexCount; ++i) {
        for (int j = 0; j < vertexCount; ++j) {
            if (adjacencyMatrix[i][j] != 0) {
                if (i == j) {
                    degrees[i] += 2;
                } else {
                    degrees[i] += 1;
                }
            }
        }
    }
    return degrees;
}

void UndirectedGraph::printDegrees(std::ostream& out) const {
    DynamicArray<int> degrees = calculateDegrees();
    out << "Степени вершин:" << std::endl;
    for (int i = 0; i < vertexCount; ++i) {
        out << "Вершина " << (i + 1) << ": " << degrees[i] << std::endl;
    }
}