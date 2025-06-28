// email:shmuel.benatar@msmail.ariel.ac.il
#include "Graph.h"
#include "Algorithms.h"
#include <iostream>

using namespace std;
using namespace graph;

int main() {
    Graph g(5);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 4, 4);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 5);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 4, 3);

    cout << "Original Graph:" << endl;
    g.print_graph();

    cout << "\nKruskal's MST:" << endl;
    Graph mstKruskal = Algorithms::kruskal(g);
    mstKruskal.print_graph();

    cout << "\nPrim's MST:" << endl;
    Graph mstPrim = Algorithms::prim(g);
    mstPrim.print_graph();

    cout << "\nDijkstra's Shortest Paths from Node 0:" << endl;
    Graph dijkstraPaths = Algorithms::dijkstra(g, 0);
    dijkstraPaths.print_graph();

    return 0;
}
