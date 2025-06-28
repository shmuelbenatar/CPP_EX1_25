// email:shmuel.benatar@msmail.ariel.ac.il

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
using namespace std;

namespace graph {

struct Node {
    int vertex;
    int weight;
    // Pointer to the next node in the adjacency list
    Node* next;
    

    Node(int d, int w, Node* n = nullptr)
        : vertex(d), weight(w), next(n) {}
};

class Graph {
private:
    int numVertices;
    Node** adjacencyList;
    int* visitOrder; // Array to store the order of visits for DFS/BFS
    int visitCount; 

public:
    Graph(int vertices);
    Graph(const Graph& other); // Deep copy constructor
    Graph& operator=(const Graph& other); // Assignment operator
    ~Graph();


    void addEdge(int from, int to, int weight = 1);
    void removeEdge(int from, int to);
    void print_graph() const;

    int getNumVertices() const;
    Node* getAdjList(int v) const;

    void initializeVisitOrder(); // Initialize visitOrder array
    void setVisitOrder(int index, int vertex);

    // Getters for visitOrder and visitCount
    int getVisitCount() const { return visitCount; }
    int getVisitOrderAt(int i) const { return visitOrder[i]; }

    

private:
    void removeEdgeFromList(int from, int to);
};

} // namespace graph
#endif