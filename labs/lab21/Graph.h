#pragma once
#include <vector>
#include <string>
#include <iostream>

class Graph {
protected:
    int vertexCount;
    std::vector<std::vector<int>> adjacencyMatrix;

public:
    Graph();
    Graph(int vertexCount);
    virtual ~Graph();

    int getVertexCount() const;
    int getEdge(int i, int j) const;
    void setEdge(int i, int j, int value);
    const std::vector<std::vector<int>>& getAdjacencyMatrix() const;

    virtual void loadFromFile(const std::string& filename) = 0;
    virtual void print(std::ostream& out) const;
};