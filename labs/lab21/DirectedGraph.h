#pragma once
#include "Graph.h"
#include <vector>
#include <queue>

class DirectedGraph : public Graph {
public:
    DirectedGraph();
    DirectedGraph(int vertexCount);

    void loadFromFile(const std::string& filename) override;
    void loadFromConsole();
    void generateRandom(int vertexCount, double density);

    std::vector<int> bfs(int startVertex) const;
    std::vector<int> bfsWithLevels(int startVertex) const;
    std::vector<int> findCitiesWithMinTransfers(int startCity, int minTransfers) const;

    void printBfsResult(std::ostream& out, int startVertex) const;
    void printTransfersResult(std::ostream& out, int startCity, int minTransfers) const;
};