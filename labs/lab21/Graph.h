#pragma once
#include "DynamicArray.h"
#include <string>
#include <iostream>

class Graph {
protected:
    int vertexCount;
    DynamicArray<DynamicArray<int>> adjacencyMatrix;

    void initializeMatrix(int n);

public:
    Graph();
    Graph(int vertexCount);
    virtual ~Graph();

    int getVertexCount() const;
    int getEdge(int i, int j) const;
    void setEdge(int i, int j, int value);
    const DynamicArray<DynamicArray<int>>& getAdjacencyMatrix() const;

    virtual void loadFromFile(const std::string& filename) = 0;
    virtual void print(std::ostream& out) const;
};