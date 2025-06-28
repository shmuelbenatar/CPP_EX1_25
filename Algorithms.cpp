// email:shmuel.benatar@msmail.ariel.ac.il
#include "Algorithms.h"
#include "Graph.h"
#include "DataStructures.h"


namespace graph {


/**
 * @brief Performs Breadth-First Search (BFS) on a graph starting from a given vertex.
 * @param g The input graph.
 * @param start The starting vertex for the BFS.
 * @return A BFS tree containing only the edges traversed by the BFS algorithm.
 */
Graph Algorithms::bfs(const Graph& g, int start) {
    int numVer = g.getNumVertices();
    if (start < 0 || start >= numVer) {
        throw std::out_of_range("Vertex " + std::to_string(start) + " is out of bounds");
    }

    Graph tree(numVer);
    tree.initializeVisitOrder();

    Queue q(numVer);

    colors* color = new colors[numVer];
    int* parent = new int[numVer];
    int* distance = new int[numVer];


    for (int i = 0; i < numVer; ++i) {
        color[i] = White;
        distance[i] = -1; // Infinite distance
        parent[i] = -1;   // No parent
    }

    q.enqueue(start);
    color[start] = Gray;
    distance[start] = 0; // Distance to start vertex is 0
    int index = 0;


    while (!q.isEmpty()) {
        int u = q.dequeue();
        tree.setVisitOrder(index++, u); // Set visit order for BFS

        Node* curr = g.getAdjList(u);

		// Check if vertex index is valid
		if(u < 0 || u >= numVer) {
			throw std::out_of_range("Invalid vertex index: " + std::to_string(u));
		}
        while (curr != nullptr) {
            int v = curr->vertex;
            if (color[v] == White) {
                color[v] = Gray;
                distance[v] = distance[u] + 1;
                parent[v] = u; 
                q.enqueue(v);
            }
            curr = curr->next;
        }
        color[u] = Black;
    }

    for (int i = 0; i < numVer; ++i) {
        if (parent[i] != -1) {
            tree.addEdge(parent[i], i, distance[i]); 
        }
    }

    delete[] color;
    delete[] distance;
    delete[] parent;

    std::cout << "BFS Tree built successfully" << std::endl;

    return tree;
}


/**
 * @brief Performs Depth-First Search (DFS) on a graph starting from a given vertex.
 * @param g The input graph.
 * @param start The starting vertex for the DFS.
 * @return A DFS tree or forest containing only the tree edges found by the DFS algorithm.
 */
Graph Algorithms::dfs(const Graph& g, int start) {
    int numVer = g.getNumVertices();
    Graph tree(numVer);
    tree.initializeVisitOrder();

    colors* color = new colors[numVer];
    int index = 0;

    for (int i = 0; i < numVer; ++i) {
        color[i] = White;
    }

    if (start < 0 || start >= numVer) {
        throw std::out_of_range("Vertex " + std::to_string(start) + " is out of bounds");
    }

    // Start DFS from the given vertex
    dfs_visit(g, tree, start, color, index);

    // If the graph is disconnected, we need to visit all vertices
    // that haven't been visited yet to ensure the DFS tree covers the entire graph
    for (int u = 0; u < numVer; ++u) {
        if (color[u] == White) {
            dfs_visit(g, tree, u, color, index);
        }
    }

    delete[] color;

    std::cout << "DFS Tree/Forest built successfully" << std::endl;
    return tree;
}
/**
 * @brief A recursive helper function for DFS traversal.
 * @param g The input graph.
 * @param tree The tree being built.
 * @param u The current vertex being visited.
 * @param color Array indicating the visit status of each vertex.
 * @param index The current index for visit order tracking.
 */
void Algorithms::dfs_visit(const Graph& g, Graph& tree, int u, colors* color, int& index) {
    // Check if vertex index is valid
    if (u < 0 || u >= g.getNumVertices()) {
        throw std::out_of_range("Invalid vertex index: " + std::to_string(u));
    }
    color[u] = Gray;
    tree.setVisitOrder(index++, u); // Set visit order for DFS    
    
    // Iterate through the adjacency list of vertex u
    // and recursively visit all unvisited neighbors
    Node* curr = g.getAdjList(u);
    while (curr != nullptr) {
        int v = curr->vertex;
        if (color[v] == White) {
            tree.addEdge(u, v, curr->weight); // Tree edge 
            dfs_visit(g, tree, v, color, index);
        }
        curr = curr->next;
    }

    color[u] = Black;
}
/**
 * @brief Finds the shortest paths from a source vertex to all other vertices using Dijkstra's algorithm.
 * @param g The input graph.
 * @param start The source vertex.
 * @return A shortest path tree representing the minimum distances from the source to each reachable vertex.
 * @throws std::invalid_argument If the graph contains negative weight edges.
 */
Graph Algorithms::dijkstra(const Graph& g, int start) {
    int numVer = g.getNumVertices();

    if (start < 0 || start >= numVer) {
        throw std::out_of_range("Start vertex " + std::to_string(start) + " is out of bounds");
    }

    int* distance = new int[numVer];
    int* prev = new int[numVer];

    for (int i = 0; i < numVer; ++i) {
        distance[i] = INT_MAX;
        prev[i] = -1;
    }

    PriorityQueue pq(numVer);
    bool* visited = new bool[numVer]();

    distance[start] = 0;
    pq.insert(start, 0);

    int index = 0;

    while (!pq.isEmpty()) {
        int u = pq.extractMin();

        if (visited[u]) continue;
        visited[u] = true;

        Node* curr = g.getAdjList(u);
        while (curr != nullptr) {
            int v = curr->vertex;
            int weight = curr->weight;

            if (weight < 0) {
                delete[] distance;
                delete[] prev;
                delete[] visited;
                throw std::invalid_argument("Negative edge weight detected. Dijkstra cannot handle negative weights.");
            }

            if (!visited[v] && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                prev[v] = u;

                if (pq.contains(v)) {
                    pq.decreasePriority(v, distance[v]);
                } else {
                    pq.insert(v, distance[v]);
                }
            }

            curr = curr->next;
        }
    }

    // Build the shortest path tree
    Graph tree(numVer);
    tree.initializeVisitOrder();

    for (int v = 0; v < numVer; ++v) {
        if (prev[v] != -1) {
            // Find the original weight from the graph
            int edgeWeight = 0;
            Node* curr = g.getAdjList(prev[v]);
            while (curr != nullptr) {
                if (curr->vertex == v) {
                    edgeWeight = curr->weight;
                    break;
                }
                curr = curr->next;
            }

            tree.addEdge(prev[v], v, edgeWeight);

            std::cout << "Added edge: " << prev[v] << " - " << v << " weight: " << edgeWeight << std::endl;


            tree.setVisitOrder(index++, v);
        }
    }

    delete[] distance;
    delete[] prev;
    delete[] visited;

    std::cout << "Dijkstra Tree built successfully" << std::endl;

    return tree;
}


/**
 * @brief Finds a Minimum Spanning Tree (MST) using Prim's algorithm.
 * @param g The input graph.
 * @return The MST of the graph.
 */
Graph Algorithms::prim(const Graph& g) {
    int n = g.getNumVertices();
    Graph tree(n);
    tree.initializeVisitOrder();

    PriorityQueue pq(n);
    bool* inTree = new bool[n]();
    int* key = new int[n];
    int* parent = new int[n];

    for (int i = 0; i < n; ++i) {
        key[i] = INT_MAX;
        parent[i] = -1;
    }

    key[0] = 0;
    pq.insert(0, 0);

    int index = 0;

    while (!pq.isEmpty()) {
        int u = pq.extractMin();

        if (inTree[u]) continue;
        inTree[u] = true;

        tree.setVisitOrder(index++, u);

        Node* curr = g.getAdjList(u);
        while (curr != nullptr) {
            int v = curr->vertex;
            int weight = curr->weight;

            if (!inTree[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;

                if (pq.contains(v)) {
                    pq.decreasePriority(v, key[v]);
                } else {
                    pq.insert(v, key[v]);
                }
            }

            curr = curr->next;
        }
    }

    for (int v = 1; v < n; ++v) {
        if (parent[v] != -1) {
            tree.addEdge(parent[v], v, key[v]);
        }
    }

    delete[] inTree;
    delete[] key;
    delete[] parent;

    return tree;
}
/**
 * @brief Finds a Minimum Spanning Tree (MST) using Kruskal's algorithm.
 * @param g The input graph.
 * @return The MST of the graph.
 */
Graph Algorithms::kruskal(const Graph& g) {
    int n = g.getNumVertices();
    Graph tree(n);
    tree.initializeVisitOrder();

    UnionFind uf(n);

    struct Edge {
        int u, v, w;
    };

    Edge* edges = new Edge[n * n];
    int edgeCount = 0;

    PriorityQueue pq(n * n);

    for (int u = 0; u < n; ++u) {
        Node* curr = g.getAdjList(u);
        while (curr != nullptr) {
            int v = curr->vertex;
            if (u < v) {
                edges[edgeCount] = {u, v, curr->weight};
                pq.insert(edgeCount, curr->weight);
                edgeCount++;
            }
            curr = curr->next;
        }
    }

    int index = 0;
    int edgesAdded = 0;

    bool* visited = new bool[n](); 

    while (!pq.isEmpty() && edgesAdded < n - 1) {
        int idx = pq.extractMin();
        Edge edge = edges[idx];
        int u = edge.u;
        int v = edge.v;

        if (uf.find(u) != uf.find(v)) {
            tree.addEdge(u, v, edge.w);
            uf.unite(u, v);

            if (!visited[u]) { 
                tree.setVisitOrder(index++, u);
                visited[u] = true;
            }
            if (!visited[v]) { 
                tree.setVisitOrder(index++, v);
                visited[v] = true;
            }

            edgesAdded++;
        }
    }

    delete[] edges;
    delete[] visited;

    return tree;
}

}