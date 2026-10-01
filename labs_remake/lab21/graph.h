#ifndef GRAPH_H
#define GRAPH_H

const int MAX_N = 25;

struct Graph {
    int n;
    int m[MAX_N][MAX_N];
};

bool readGraphManual(Graph& g, bool symmetric, int maxValue);
bool readGraphRandom(Graph& g, bool symmetric, int maxValue);
bool readGraphFile(Graph& g, const char* fileName, int* extra, int extraCount);
void printGraph(const Graph& g);

#endif