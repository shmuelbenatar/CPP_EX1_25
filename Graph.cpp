// email:shmuel.benatar@msmail.ariel.ac.il
#include "Graph.h"
#include <stdexcept>

namespace graph {


// Constructor
Graph::Graph(int vertices) : numVertices(vertices) {
    if (vertices <= 0){
        throw invalid_argument("Number of vertices must be positive");
    }
    this->adjacencyList = new Node*[this->numVertices];
    for (int i = 0; i < numVertices; ++i){
        // Initialize each adjacency list to nullptr
        adjacencyList[i] = nullptr;
    }
    this->visitOrder = new int[numVertices];
    this->visitCount = 0; // Initialize visit count to 0
}

// Deep Copy Constructor
Graph::Graph(const Graph& other) : numVertices(other.numVertices) {
    adjacencyList = new Node*[numVertices];

    // Copy each adjacency list
    for (int i = 0; i < numVertices; ++i) {
        adjacencyList[i] = nullptr;
        Node* current = other.adjacencyList[i];
        Node* last = nullptr;
        while (current != nullptr) {
            Node* newNode = new Node(current->vertex, current->weight);
            if (last == nullptr) {
                adjacencyList[i] = newNode;
            } else {
                last->next = newNode;
            }
            last = newNode;
            current = current->next;
        }
    }

    // Copy visitOrder
    this->visitOrder = new int[this->numVertices];
    for (int i = 0; i < other.visitCount; ++i) {
        this->visitOrder[i] = other.visitOrder[i];
    }
    this->visitCount = other.visitCount;
}

// Assignment Operator (Rule of Three)
Graph& Graph::operator=(const Graph& other) {
    if (this == &other)
        return *this;

    // Free old memory
    for (int i = 0; i < numVertices; ++i) {
        Node* current = adjacencyList[i];
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] adjacencyList;
    delete[] visitOrder;

    // Copy new data
    numVertices = other.numVertices;
    adjacencyList = new Node*[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        adjacencyList[i] = nullptr;
        Node* current = other.adjacencyList[i];
        Node* last = nullptr;
        while (current != nullptr) {
            Node* newNode = new Node(current->vertex, current->weight);
            if (last == nullptr) {
                adjacencyList[i] = newNode;
            } else {
                last->next = newNode;
            }
            last = newNode;
            current = current->next;
        }
    }

    // Copy visitOrder
    visitOrder = new int[numVertices];
    for (int i = 0; i < other.visitCount; ++i) {
        visitOrder[i] = other.visitOrder[i];
    }
    visitCount = other.visitCount;

    return *this;
}

// Destructor
Graph::~Graph() {
    // Free adjacency list memory
    for (int i = 0; i < this->numVertices; ++i) {
        Node* current = this->adjacencyList[i];
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

    // Free additional arrays
    delete[] this->adjacencyList;
    delete[] this->visitOrder;
}

// Add an edge to the graph
// If the edge already exists, throw an exception
// If the edge is a self-loop, throw an exception

void Graph::addEdge(int from, int to, int weight) {
    if (from < 0 || from >= this->numVertices || to < 0 || to >= this->numVertices)
        throw out_of_range("Invalid vertex index");

    if (from == to) {
        throw invalid_argument("Cannot add self-loop");
    }
    
    // Check if the edge already exists
    Node* current = this->adjacencyList[from];
    while (current != nullptr) {
        if (current->vertex == to) {
            throw invalid_argument("Edge already exists");
        }
        current = current->next;
    }
    // Add the edge to the adjacency list
    this->adjacencyList[from] = new Node(to, weight, this->adjacencyList[from]);
    this->adjacencyList[to] = new Node(from, weight, this->adjacencyList[to]); // undirected
}

// Remove an edge from the graph
// If the edge does not exist, throw an exception
// If the edge is a self-loop, throw an exception
// If the vertex indices are invalid, throw an exception
void Graph::removeEdge(int from, int to) {
    if (from < 0 || from >= numVertices || to < 0 || to >= numVertices){
        throw out_of_range("Invalid vertex index");
    }
    if (from == to) {
        throw invalid_argument("Cannot remove self-loop");
    }
    if (adjacencyList[from] == nullptr || adjacencyList[to] == nullptr) {
        throw invalid_argument("Edge does not exist");
    }
    // Remove the edge from both vertices
    removeEdgeFromList(from, to); // removes to from from's list
    removeEdgeFromList(to, from); // and vice versa
}

// Helper function to remove an edge from the adjacency list
void Graph::removeEdgeFromList(int from, int to) {
    Node* prev = nullptr;
    Node* curr = adjacencyList[from];

    while (curr != nullptr) {
        if (curr->vertex == to) {
            if (prev == nullptr)
                adjacencyList[from] = curr->next;
            else
                prev->next = curr->next;
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    throw invalid_argument("Edge does not exist");
}

// Print the graph in a readable format
// Each vertex and its edges are printed in the format: vertex: (neighbor, weight)
// If the vertex has no edges, print "vertex: "
void Graph::print_graph() const {
    for (int i = 0; i < this->visitCount; ++i) {
        int u = this->visitOrder[i];
        cout << u << ": ";
        Node* curr = adjacencyList[u];
        while (curr != nullptr) {
            cout << "(" << curr->vertex << ", w=" << curr->weight << ") ";
            curr = curr->next;
        }
        cout << endl;
    }
}
// Initialize the visitOrder array and visitCount
// This function should be called before any DFS/BFS traversal
void Graph::initializeVisitOrder() { 
    this->visitCount = 0;
} 

// Set the visit order at a specific index
// This function is used during DFS/BFS traversal to keep track of the order of visits
void Graph::setVisitOrder(int index, int vertex) { 
    this->visitOrder[index] = vertex;
    this->visitCount++;
}

// Get the number of vertices in the graph
int Graph::getNumVertices() const {
    return numVertices;
}

// Get the adjacency list for a specific vertex
Node* Graph::getAdjList(int v) const {
    if (v < 0 || v >= numVertices)
        throw out_of_range("Invalid vertex index");
    return adjacencyList[v];
}

} // namespace graph
