#include "DirectedGraph.h"
#include "Queue.h"
#include <fstream>
#include <cstdlib>
#include <stdexcept>

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
    initializeMatrix(n);
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
    initializeMatrix(n);
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
    initializeMatrix(vertexCount);
    for (int i = 0; i < vertexCount; ++i) {
        for (int j = 0; j < vertexCount; ++j) {
            if (i != j) {
                double r = static_cast<double>(rand()) / RAND_MAX;
                if (r < density) {
                    adjacencyMatrix[i][j] = (rand() % 10) + 1;
                }
            }
        }
    }
}

void DirectedGraph::sortVertices(DynamicArray<int>& vertices) const {
    for (int i = 0; i < vertices.getSize() - 1; ++i) {
        for (int j = 0; j < vertices.getSize() - i - 1; ++j) {
            if (vertices[j] > vertices[j + 1]) {
                int temp = vertices[j];
                vertices[j] = vertices[j + 1];
                vertices[j + 1] = temp;
            }
        }
    }
}

DynamicArray<int> DirectedGraph::bfs(int startVertex) const {
    if (startVertex < 0 || startVertex >= vertexCount) {
        throw std::out_of_range("Неверный номер стартовой вершины");
    }
    DynamicArray<int> result;
    DynamicArray<bool> visited;
    for (int i = 0; i < vertexCount; ++i) {
        visited.pushBack(false);
    }
    Queue<int> q;
    q.push(startVertex);
    visited[startVertex] = true;
    while (!q.isEmpty()) {
        int current = q.front();
        q.pop();
        result.pushBack(current);
        DynamicArray<int> neighbors;
        for (int i = 0; i < vertexCount; ++i) {
            if (adjacencyMatrix[current][i] != 0 && !visited[i]) {
                neighbors.pushBack(i);
            }
        }
        sortVertices(neighbors);
        for (int i = 0; i < neighbors.getSize(); ++i) {
            int neighbor = neighbors[i];
            visited[neighbor] = true;
            q.push(neighbor);
        }
    }
    return result;
}

DynamicArray<int> DirectedGraph::bfsWithLevels(int startVertex) const {
    if (startVertex < 0 || startVertex >= vertexCount) {
        throw std::out_of_range("Неверный номер стартовой вершины");
    }
    DynamicArray<int> distances;
    for (int i = 0; i < vertexCount; ++i) {
        distances.pushBack(-1);
    }
    Queue<int> q;
    q.push(startVertex);
    distances[startVertex] = 0;
    while (!q.isEmpty()) {
        int current = q.front();
        q.pop();
        DynamicArray<int> neighbors;
        for (int i = 0; i < vertexCount; ++i) {
            if (adjacencyMatrix[current][i] != 0 && distances[i] == -1) {
                neighbors.pushBack(i);
            }
        }
        sortVertices(neighbors);
        for (int i = 0; i < neighbors.getSize(); ++i) {
            int neighbor = neighbors[i];
            distances[neighbor] = distances[current] + 1;
            q.push(neighbor);
        }
    }
    return distances;
}

DynamicArray<int> DirectedGraph::findCitiesWithMinTransfers(int startCity, int minTransfers) const {
    if (startCity < 0 || startCity >= vertexCount) {
        throw std::out_of_range("Неверный номер стартового города");
    }
    if (minTransfers < 0) {
        throw std::invalid_argument("Количество пересадок не может быть отрицательным");
    }
    DynamicArray<int> distances = bfsWithLevels(startCity);
    DynamicArray<int> result;
    int minEdges = minTransfers + 1;
    for (int i = 0; i < vertexCount; ++i) {
        if (i != startCity && distances[i] >= minEdges) {
            result.pushBack(i);
        }
    }
    return result;
}

void DirectedGraph::printBfsResult(std::ostream& out, int startVertex) const {
    DynamicArray<int> result = bfs(startVertex);
    out << "Поиск в ширину от вершины " << (startVertex + 1) << ":" << std::endl;
    out << "Порядок обхода: ";
    for (int i = 0; i < result.getSize(); ++i) {
        out << (result[i] + 1);
        if (i < result.getSize() - 1) out << " -> ";
    }
    out << std::endl;
    out << "Достигаемые вершины: ";
    bool first = true;
    for (int i = 0; i < result.getSize(); ++i) {
        int v = result[i];
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
    DynamicArray<int> result = findCitiesWithMinTransfers(startCity, minTransfers);
    out << "Города, до которых можно долететь не менее чем с " << minTransfers << " пересадками:" << std::endl;
    if (result.isEmpty()) {
        out << "-1" << std::endl;
    } else {
        for (int i = 0; i < result.getSize(); ++i) {
            out << (result[i] + 1);
            if (i < result.getSize() - 1) out << ", ";
        }
        out << std::endl;
    }
}