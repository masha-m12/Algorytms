#include "../../../OOP/BoolVector/BoolVector/BoolVector.h" 
#include "../../../OOP/BoolMatrix/BoolMatrix/BoolMatrix.h"  
#include <iostream>  
#include <vector>  

bool topologicalSortUtil(int v, const BoolMatrix& graph, std::vector<int>& visited, std::vector<int>& result) {
    visited[v] = 1;

    for (int i = 0; i < graph.getRows(); ++i) {
        if (graph[v][i]) {
            if (visited[i] == 1) {
                return false;
            }
            if (visited[i] == 0) {
                if (!topologicalSortUtil(i, graph, visited, result)) {
                    return false;
                }
            }
        }
    }

    visited[v] = 2;
    result.push_back(v);
    return true;
}

bool topologicalSort(const BoolMatrix& graph, std::vector<int>& result) {
    int numVertices = graph.getRows();
    std::vector<int> visited(numVertices, 0);

    for (int i = 0; i < numVertices; ++i) {
        if (visited[i] == 0) {
            if (!topologicalSortUtil(i, graph, visited, result)) {
                return false;
            }
        }
    }

    std::reverse(result.begin(), result.end());
    return true;
}

int main() {
    setlocale(LC_ALL, "Russian");

    const int vertices = 6;
    BoolMatrix graph(vertices, vertices, false);

    graph.set(0, 1, true);
    graph.set(0, 2, true);
    graph.set(1, 3, true);
    graph.set(2, 3, true);
    graph.set(3, 4, true);
    graph.set(4, 5, true);

    std::vector<int> sortedOrder;
    if (!topologicalSort(graph, sortedOrder)) {
        std::cout << "Граф содержит цикл" << "\n";
    }
    else {
        std::cout << "Топологическая сортировка: ";
        for (int v : sortedOrder) {
            std::cout << v << " ";
        }
        std::cout << "\n";
    }

    return 0;
}