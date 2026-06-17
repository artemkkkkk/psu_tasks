#include "DirectedGraph.h"
#include <fstream>
#include <random>
#include <stdexcept>
#include <algorithm>
#include <set>

DirectedGraph::DirectedGraph() : Graph() {}

DirectedGraph::DirectedGraph(int vertexCount) : Graph(vertexCount) {}

void DirectedGraph::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }
    int n;
    if (!(file >> n) || n <= 0) {
        throw std::runtime_error("Некорректное количество вершин");
    }
    vertexCount = n;
    adjacencyMatrix.assign(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!(file >> adjacencyMatrix[i][j])) {
                throw std::runtime_error("Некорректный формат матрицы смежности");
            }
        }
    }
}

void DirectedGraph::loadFromConsole() {
    int n;
    std::cout << "Введите количество вершин: ";
    std::cin >> n;
    if (n <= 0) {
        throw std::invalid_argument("Количество вершин должно быть положительным");
    }
    vertexCount = n;
    adjacencyMatrix.assign(n, std::vector<int>(n, 0));
    std::cout << "Введите матрицу смежности (" << n << "x" << n << "):" << std::endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> adjacencyMatrix[i][j];
        }
    }
}

void DirectedGraph::generateRandom(int vertexCount, double density) {
    if (vertexCount <= 0) {
        throw std::invalid_argument("Количество вершин должно быть положительным");
    }
    this->vertexCount = vertexCount;
    adjacencyMatrix.assign(vertexCount, std::vector<int>(vertexCount, 0));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    std::uniform_int_distribution<> weightDis(1, 10);
    for (int i = 0; i < vertexCount; ++i) {
        for (int j = 0; j < vertexCount; ++j) {
            if (i != j && dis(gen) < density) {
                adjacencyMatrix[i][j] = weightDis(gen);
            }
        }
    }
}

std::vector<int> DirectedGraph::bfs(int startVertex) const {
    if (startVertex < 0 || startVertex >= vertexCount) {
        throw std::out_of_range("Неверный номер стартовой вершины");
    }
    std::vector<int> result;
    std::vector<bool> visited(vertexCount, false);
    std::queue<int> q;
    q.push(startVertex);
    visited[startVertex] = true;
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        result.push_back(current);
        std::vector<int> neighbors;
        for (int i = 0; i < vertexCount; ++i) {
            if (adjacencyMatrix[current][i] != 0 && !visited[i]) {
                neighbors.push_back(i);
            }
        }
        std::sort(neighbors.begin(), neighbors.end());
        for (int neighbor : neighbors) {
            visited[neighbor] = true;
            q.push(neighbor);
        }
    }
    return result;
}

std::vector<int> DirectedGraph::bfsWithLevels(int startVertex) const {
    if (startVertex < 0 || startVertex >= vertexCount) {
        throw std::out_of_range("Неверный номер стартовой вершины");
    }
    std::vector<int> distances(vertexCount, -1);
    std::queue<int> q;
    q.push(startVertex);
    distances[startVertex] = 0;
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        std::vector<int> neighbors;
        for (int i = 0; i < vertexCount; ++i) {
            if (adjacencyMatrix[current][i] != 0 && distances[i] == -1) {
                neighbors.push_back(i);
            }
        }
        std::sort(neighbors.begin(), neighbors.end());
        for (int neighbor : neighbors) {
            distances[neighbor] = distances[current] + 1;
            q.push(neighbor);
        }
    }
    return distances;
}

std::vector<int> DirectedGraph::findCitiesWithMinTransfers(int startCity, int minTransfers) const {
    if (startCity < 0 || startCity >= vertexCount) {
        throw std::out_of_range("Неверный номер стартового города");
    }
    if (minTransfers < 0) {
        throw std::invalid_argument("Количество пересадок не может быть отрицательным");
    }
    std::vector<int> distances = bfsWithLevels(startCity);
    std::vector<int> result;
    int minEdges = minTransfers + 1;
    for (int i = 0; i < vertexCount; ++i) {
        if (i != startCity && distances[i] >= minEdges) {
            result.push_back(i);
        }
    }
    return result;
}

void DirectedGraph::printBfsResult(std::ostream& out, int startVertex) const {
    std::vector<int> result = bfs(startVertex);
    out << "Поиск в ширину от вершины " << (startVertex + 1) << ":" << std::endl;
    out << "Порядок обхода: ";
    for (size_t i = 0; i < result.size(); ++i) {
        out << (result[i] + 1);
        if (i < result.size() - 1) out << " -> ";
    }
    out << std::endl;
    out << "Достигаемые вершины: ";
    bool first = true;
    for (int v : result) {
        if (v != startVertex) {
            if (!first) out << ", ";
            out << (v + 1);
            first = false;
        }
    }
    if (first) out << "(нет)";
    out << std::endl;
}

void DirectedGraph::printTransfersResult(std::ostream& out, int startCity, int minTransfers) const {
    std::vector<int> result = findCitiesWithMinTransfers(startCity, minTransfers);
    out << "Города, до которых можно долететь не менее чем с " << minTransfers << " пересадками:" << std::endl;
    if (result.empty()) {
        out << "-1" << std::endl;
    } else {
        for (size_t i = 0; i < result.size(); ++i) {
            out << (result[i] + 1);
            if (i < result.size() - 1) out << ", ";
        }
        out << std::endl;
    }
}