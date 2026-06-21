#include "Graph.h"
#include <fstream>
#include <stdexcept>

Graph::Graph() : vertexCount(0) {}

Graph::Graph(int vertexCount) : vertexCount(vertexCount) {
    initializeMatrix(vertexCount);
}

Graph::~Graph() {}

void Graph::initializeMatrix(int n) {
    adjacencyMatrix = DynamicArray<DynamicArray<int>>();
    for (int i = 0; i < n; ++i) {
        DynamicArray<int> row;
        for (int j = 0; j < n; ++j) {
            row.pushBack(0);
        }
        adjacencyMatrix.pushBack(row);
    }
}

int Graph::getVertexCount() const {
    return vertexCount;
}

int Graph::getEdge(int i, int j) const {
    if (i < 0 || i >= vertexCount || j < 0 || j >= vertexCount) {
        throw std::out_of_range("Неверный индекс вершины");
    }
    return adjacencyMatrix[i][j];
}

void Graph::setEdge(int i, int j, int value) {
    if (i < 0 || i >= vertexCount || j < 0 || j >= vertexCount) {
        throw std::out_of_range("Неверный индекс вершины");
    }
    adjacencyMatrix[i][j] = value;
}

const DynamicArray<DynamicArray<int>>& Graph::getAdjacencyMatrix() const {
    return adjacencyMatrix;
}

void Graph::print(std::ostream& out) const {
    out << "Матрица смежности (" << vertexCount << "x" << vertexCount << "):" << std::endl;
    for (int i = 0; i < vertexCount; ++i) {
        for (int j = 0; j < vertexCount; ++j) {
            out << adjacencyMatrix[i][j];
            if (j < vertexCount - 1) out << " ";
        }
        out << std::endl;
    }
}