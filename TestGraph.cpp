
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "Graph.h"
#include "Algorithms.h"
#include "DataStructures.h"
#include "doctest.h"
using namespace graph;

TEST_CASE("Kruskal Test - Check total weight") {
    Graph g(5);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 4, 4);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 5);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 4, 3);

    Graph mst = Algorithms::kruskal(g);
    int totalWeight = 0;

    // Iterate only over visited vertices in the MST
    for (int i = 0; i < mst.getVisitCount(); ++i) {
        int u = mst.getVisitOrderAt(i);
        std::cout << "Visit Order [" << i << "] = " << u << std::endl; // הוסף שורה זו
        Node* curr = mst.getAdjList(u);
        while (curr != nullptr) {
            totalWeight += curr->weight;
            curr = curr->next;
        }
    }

    CHECK(totalWeight / 2 == 7);
}


TEST_CASE("Prim Test - Check total weight") {
    Graph g(5);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 4, 4);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 5);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 4, 3);

    Graph mst = Algorithms::prim(g);
    int totalWeight = 0;

    for (int u = 0; u < mst.getNumVertices(); ++u) {
        Node* curr = mst.getAdjList(u);
        while (curr != nullptr) {
            totalWeight += curr->weight;
            curr = curr->next;
        }
    }

    CHECK(totalWeight / 2 == 7);
}

TEST_CASE("Dijkstra Test - Check minimal total edge weight from start node") {
    using namespace graph;

    Graph g(5);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 4, 4);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 5);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 4, 3);

    Graph shortestPaths = Algorithms::dijkstra(g, 0);

    // Calculate total weight of edges in the result graph
    int totalWeight = 0;

    // Iterate over all vertices in the graph (not only visited)
    for (int u = 0; u < shortestPaths.getNumVertices(); ++u) {
        Node* curr = shortestPaths.getAdjList(u);
        while (curr != nullptr) {
            totalWeight += curr->weight;
            curr = curr->next;
        }
    }

    // Each edge is counted twice in an undirected graph
    totalWeight /= 2;

    std::cout << "Total weight in tree: " << totalWeight << std::endl;

    // The expected total weight is the sum of the edges in the shortest path tree:
    // Edges:
    // 0 - 1 (1)
    // 0 - 4 (4)
    // 1 - 2 (2)
    // 2 - 3 (1)
    // Total: 1 + 4 + 2 + 1 = 8
    int expectedTotal = 8;

    CHECK(totalWeight == expectedTotal);
}


    

TEST_CASE("Negative Edge Test") {
    Graph g(5);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 4, 4);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 5);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 4, 3);
    g.addEdge(2, 4, -1);
    CHECK_THROWS_AS(Algorithms::dijkstra(g, 0), std::invalid_argument);
}

TEST_CASE("Graph Add Edge with Invalid Vertices") {
    Graph g(3);
    CHECK_THROWS_AS(g.addEdge(3, 0, 1), std::out_of_range);
    CHECK_THROWS_AS(g.addEdge(0, 3, 1), std::out_of_range);
    CHECK_THROWS_AS(g.addEdge(-1, 0, 1), std::out_of_range);
}

TEST_CASE("Graph Remove Non-Existing Edge") {
    Graph g(3);
    g.addEdge(0, 1, 1);
    CHECK_THROWS_AS(g.removeEdge(1, 2), std::invalid_argument);
}

TEST_CASE("Graph Add Existing Edge") {
    Graph g(3);
    g.addEdge(0, 1, 1);
    CHECK_THROWS_AS(g.addEdge(0, 1, 1), std::invalid_argument);
}

TEST_CASE("Graph with One Vertex") {
    Graph g(1);
    Graph mst = Algorithms::kruskal(g);
    CHECK(mst.getNumVertices() == 1);
}

TEST_CASE("Graph with Zero Vertices") {
    CHECK_THROWS_AS(Graph g(0), std::invalid_argument);
}

TEST_CASE("Dijkstra Start Out of Range") {
    Graph g(3);
    g.addEdge(0, 1, 1);
    CHECK_THROWS_AS(Algorithms::dijkstra(g, 3), std::out_of_range);
}

TEST_CASE("Union Find Union Elements Already Connected") {
    UnionFind uf(5);
    uf.unite(0, 1);
    uf.unite(1, 2);
    CHECK(uf.find(0) == uf.find(2));
    uf.unite(0, 2);
    CHECK(uf.find(0) == uf.find(2));
}

TEST_CASE("Union Find Find Returns Correct Root") {
    UnionFind uf(5);
    uf.unite(0, 1);
    uf.unite(2, 3);
    CHECK(uf.find(0) == uf.find(1));
    CHECK(uf.find(2) == uf.find(3));
    CHECK(uf.find(0) != uf.find(2));
}

TEST_CASE("Priority Queue Extract Min from Empty Queue") {
    PriorityQueue pq(5);
    CHECK_THROWS_AS(pq.extractMin(), std::out_of_range);
}

TEST_CASE("Priority Queue Decrease Priority of Non-Existing Element") {
    PriorityQueue pq(5);
    CHECK_THROWS_AS(pq.decreasePriority(3, 1), std::invalid_argument);
}

TEST_CASE("Priority Queue Insert and Extract") {
    PriorityQueue pq(5);
    pq.insert(1, 10);
    pq.insert(2, 5);
    pq.insert(3, 15);
    CHECK(pq.extractMin() == 2);
    CHECK(pq.extractMin() == 1);
    CHECK(pq.extractMin() == 3);
}

TEST_CASE("Priority Queue Contains Check") {
    PriorityQueue pq(5);
    pq.insert(1, 10);
    pq.insert(2, 5);
    CHECK(pq.contains(1));
    CHECK(pq.contains(2));
    CHECK(!pq.contains(3));
}

TEST_CASE("Priority Queue Decrease Priority") {
    PriorityQueue pq(5);
    pq.insert(1, 10);
    pq.insert(2, 5);
    pq.decreasePriority(1, 3);
    CHECK(pq.extractMin() == 1);
    CHECK(pq.extractMin() == 2);
}

TEST_CASE("Priority Queue Decrease Priority to Higher Value") {
    PriorityQueue pq(5);
    pq.insert(1, 10);
    CHECK_THROWS_AS(pq.decreasePriority(1, 15), std::invalid_argument);
}

TEST_CASE("Priority Queue Decrease Priority to Same Value") {
    PriorityQueue pq(5);
    pq.insert(1, 10);
    CHECK_NOTHROW(pq.decreasePriority(1, 10));
}

TEST_CASE("Priority Queue Contains After Decrease Priority") {
    PriorityQueue pq(5);
    pq.insert(1, 10);
    pq.insert(2, 5);
    pq.decreasePriority(1, 3);
    CHECK(pq.contains(1));
    CHECK(pq.contains(2));
}

TEST_CASE("Priority Queue Full") {
    PriorityQueue pq(5);
    pq.insert(1, 10);
    pq.insert(2, 5);
    pq.insert(3, 15);
    pq.insert(4, 20);
    pq.insert(5, 25);
    CHECK_THROWS_AS(pq.insert(6, 30), std::overflow_error);
}

TEST_CASE("Queue Enqueue and Dequeue") {
    Queue q(5);
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    CHECK(q.dequeue() == 1);
    CHECK(q.dequeue() == 2);
    CHECK(q.dequeue() == 3);
}

TEST_CASE("Queue Dequeue from Empty Queue") {
    Queue q(5);
    CHECK_THROWS_AS(q.dequeue(), std::out_of_range);
}

TEST_CASE("Queue Enqueue After Dequeue") {
    Queue q(5);
    q.enqueue(10);
    CHECK(q.dequeue() == 10);
    q.enqueue(20);
    CHECK(q.dequeue() == 20);
}

TEST_CASE("Queue Contains Check") {
    Queue q(5);
    q.enqueue(1);
    q.enqueue(2);
    CHECK(q.contains(1));
    CHECK(q.contains(2));
    CHECK(!q.contains(3));
}

TEST_CASE("Queue Full") {
    Queue q(5);
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    q.enqueue(5);
    CHECK_THROWS_AS(q.enqueue(6), std::overflow_error);
}

TEST_CASE("Queue Empty Check") {
    Queue q(5);
    CHECK(q.isEmpty());
    q.enqueue(1);
    CHECK(!q.isEmpty());
    q.dequeue();
    CHECK(q.isEmpty());
}

TEST_CASE("Queue Contains After Enqueue and Dequeue") {
    Queue q(5);
    q.enqueue(1);
    q.enqueue(2);
    CHECK(q.contains(1));
    CHECK(q.contains(2));
    q.dequeue();
    CHECK(q.contains(2));
    CHECK(!q.contains(1));
}

TEST_CASE("Queue Wrap-Around") {
    Queue q(5);
    for (int i = 0; i < 5; ++i) {
        q.enqueue(i);
    }
    for (int i = 0; i < 5; ++i) {
        CHECK(q.dequeue() == i);
    }
}

TEST_CASE("Queue Wrap-Around with Enqueue After Dequeue") {
    Queue q(5);
    for (int i = 0; i < 5; ++i) {
        q.enqueue(i);
    }
    for (int i = 0; i < 3; ++i) {
        CHECK(q.dequeue() == i);
    }
    q.enqueue(5);
    CHECK(q.dequeue() == 3);
    CHECK(q.dequeue() == 4);
    CHECK(q.dequeue() == 5);
}

TEST_CASE("Queue Contains After Dequeue") {
    Queue q(5);
    for (int i = 0; i < 5; ++i) {
        q.enqueue(i);
    }
    CHECK(q.contains(0));
    CHECK(q.contains(1));
    CHECK(q.contains(2));
    CHECK(q.contains(3));
    CHECK(q.contains(4));
    q.dequeue();
    CHECK(!q.contains(0));
    CHECK(q.contains(1));
}

TEST_CASE("Queue Contains After Multiple Enqueues") {
    Queue q(5);
    for (int i = 0; i < 5; ++i) {
        q.enqueue(i);
    }
    for (int i = 0; i < 5; ++i) {
        CHECK(q.contains(i));
    }
    
    q.dequeue();
    CHECK(!q.contains(0));
    
    q.enqueue(5);
    CHECK(q.contains(5));
}


TEST_CASE("Queue Contains After Enqueue") {
    Queue q(5);
    for (int i = 0; i < 5; ++i) {
        q.enqueue(i);
        CHECK(q.contains(i));
    }
}

TEST_CASE("Queue Contains After Wrap-Around") {
    Queue q(5);
    for (int i = 0; i < 5; ++i) {
        q.enqueue(i);
    }
    for (int i = 0; i < 3; ++i) {
        CHECK(q.dequeue() == i);
    }
    q.enqueue(5);
    CHECK(q.contains(5));
    CHECK(!q.contains(0));
}    


TEST_CASE("Graph::print_graph works without exceptions") {
    Graph g(3);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    CHECK_NOTHROW(g.print_graph());
}

TEST_CASE("Graph::addEdge creates symmetric edge") {
    Graph g(2);
    g.addEdge(0, 1, 5);

    Node* curr0 = g.getAdjList(0);
    Node* curr1 = g.getAdjList(1);

    CHECK(curr0->vertex == 1);
    CHECK(curr1->vertex == 0);
}

TEST_CASE("Graph deep copy does not affect the copied graph") {
    Graph g1(3);
    g1.addEdge(0, 1, 1);
    g1.addEdge(1, 2, 2);

    Graph g2 = g1; // Copy constructor

    g1.addEdge(0, 2, 3); // Modify original graph

    Node* curr = g2.getAdjList(0);
    bool found = false;
    while (curr != nullptr) {
        if (curr->vertex == 2) {
            found = true;
            break;
        }
        curr = curr->next;
    }

    CHECK(!found);
}

TEST_CASE("Algorithms handle empty graph correctly") {
    Graph g(3); // No edges

    CHECK_NOTHROW(Algorithms::prim(g));
    CHECK_NOTHROW(Algorithms::bfs(g, 0));
    CHECK_NOTHROW(Algorithms::dfs(g, 0));
    CHECK_NOTHROW(Algorithms::kruskal(g)); 
}

TEST_CASE("Stress test for all algorithms") {
    Graph g(7);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 3, 7);
    g.addEdge(1, 4, 1);
    g.addEdge(2, 5, 3);
    g.addEdge(3, 5, 1);
    g.addEdge(4, 6, 5);
    g.addEdge(5, 6, 2);

    CHECK_NOTHROW(Graph t = Algorithms::dijkstra(g, 1));
    CHECK_NOTHROW(Graph a = Algorithms::prim(g));
    CHECK_NOTHROW(Graph b = Algorithms::kruskal(g));
    CHECK_NOTHROW(Graph y = Algorithms::bfs(g, 1));
    CHECK_NOTHROW(Graph z = Algorithms::dfs(g, 1));
}


