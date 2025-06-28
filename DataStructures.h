// email:shmuel.benatar@msmail.ariel.ac.il
#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <stdexcept>

namespace graph {

// ========== Queue =========================
class Queue {
private:
    int* data;
    int capacity;
    int front;
    int rear;
    int size;

public:
    Queue(int maxSize);
    ~Queue();

    void enqueue(int value);
    int dequeue();
    bool isEmpty() const;
    bool contains(int value) const;
};


// ======== Priority Queue =====
struct PQNode {
    int index;
    int priority;
};

class PriorityQueue {
private:
    PQNode* data;
    int capacity;
    int size;

public:
    PriorityQueue(int maxSize);
    ~PriorityQueue();

    void insert(int index, int priority);
    int extractMin();
    void decreasePriority(int index, int newPriority);
    bool contains(int index) const;
    bool isEmpty() const;
};

// ===== Union Find =======
class UnionFind {
private:
    int* parent;
    int* rank;
    int size;

public:
    UnionFind(int n);
    ~UnionFind();

    int find(int x);
    void unite(int x, int y);
};

} // namespace graph

#endif

