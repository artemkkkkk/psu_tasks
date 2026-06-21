#pragma once
#include "Graph.h"

class DirectedGraph : public Graph {
public:
    DirectedGraph();
    DirectedGraph(int vertexCount);

    void loadFromFile(const std::string& filename) override;
    void loadFromConsole();
    void generateRandom(int vertexCount, double density);

    DynamicArray<int> bfs(int startVertex) const;
    DynamicArray<int> bfsWithLevels(int startVertex) const;
    DynamicArray<int> findCitiesWithMinTransfers(int startCity, int minTransfers) const;

    void printBfsResult(std::ostream& out, int startVertex) const;
    void printTransfersResult(std::ostream& out, int startCity, int minTransfers) const;

private:
    void sortVertices(DynamicArray<int>& vertices) const;
};