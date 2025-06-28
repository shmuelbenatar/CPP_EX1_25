// email:shmuel.benatar@msmail.ariel.ac.il
#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "Graph.h"
#include "DataStructures.h"
#define INT_MAX 2147483647

namespace graph {

    enum colors {
        White,
        Gray,
        Black
    };

class Algorithms {
public:
    static Graph bfs(const Graph& graph, int start);
    static Graph dfs(const Graph& graph, int start);
    static void dfs_visit(const Graph &g, Graph &tree, int u, colors *color, int &index);
    
    static Graph dijkstra(const Graph &graph, int start);
    static Graph prim(const Graph& graph);
    static Graph kruskal(const Graph& graph);
};

} // namespace graph

#endif
