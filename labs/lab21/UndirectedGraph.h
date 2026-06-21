#pragma once
#include "Graph.h"

class UndirectedGraph : public Graph {
public:
    UndirectedGraph();
    UndirectedGraph(int vertexCount);

    void loadFromFile(const std::string& filename) override;
    void loadFromConsole();
    void generateRandom(int vertexCount, double density);

    DynamicArray<int> calculateDegrees() const;
    void printDegrees(std::ostream& out) const;
};