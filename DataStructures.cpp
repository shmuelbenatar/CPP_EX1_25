// email:shmuel.benatar@msmail.ariel.ac.il
#include "DataStructures.h"

namespace graph
{

    // ============ Queue =======
    // Constructor initializes the queue with a maximum size
    // and sets front, rear, and size to 0.
    // Destructor cleans up the allocated memory.
    // Enqueue adds an element to the rear of the queue.
    // Dequeue removes an element from the front of the queue.
    // isEmpty checks if the queue is empty.
    // contains checks if a specific value is present in the queue.
    Queue::Queue(int maxSize) : capacity(maxSize), front(0), rear(0), size(0){
        data = new int[capacity];
    }
    Queue::~Queue(){
        delete[] data;
    }

    void Queue::enqueue(int value){
        if (size == capacity){
            throw std::overflow_error("Queue is full");
        }
        data[rear] = value;
        rear = (rear + 1) % capacity;
        ++size;
    }

    int Queue::dequeue(){
        if (isEmpty()){
            throw std::out_of_range("Queue is empty");
        }
        int value = data[front];
        front = (front + 1) % capacity;
        --size;
        return value;
    }

    bool Queue::isEmpty() const{
        return size == 0;
    }

    // Check if the queue contains a specific value
    bool Queue::contains(int value) const{
        for (int i = 0; i < size; ++i){
            if (data[(front + i) % capacity] == value)
                return true;
        }
        return false;
    }

    // =========== Priority Queue =========================
    // Constructor initializes the priority queue with a maximum size.
    // Destructor cleans up the allocated memory.
    // insert adds an element with a specific index and priority to the queue.
    // extractMin removes and returns the index of the element with the lowest priority.
    // decreasePriority updates the priority of an existing element.
    // contains checks if a specific index is present in the queue.
    // isEmpty checks if the priority queue is empty.
    // If the queue is full, an overflow error is thrown. 
    PriorityQueue::PriorityQueue(int maxSize) : capacity(maxSize), size(0){
        data = new PQNode[capacity];
    }

    PriorityQueue::~PriorityQueue(){
        delete[] data;
    }

    void PriorityQueue::insert(int index, int priority){
        if (size == capacity){
            throw std::overflow_error("Priority Queue is full");
        }
        // Check if the index already exists in the queue
        if (contains(index)){
            throw std::invalid_argument("Index already exists in the priority queue");
        }

        data[size++] = {index, priority};
    }

    int PriorityQueue::extractMin(){
        if (isEmpty())
        throw std::out_of_range("Priority Queue is empty");
        if (size == 1){
            --size;
            return data[0].index; // Return the only element
        }
        // Find the minimum priority element
        int minPos = 0; // position in array
        for (int i = 1; i < size; ++i){
            if (data[i].priority < data[minPos].priority)
                minPos = i;
        }

        int minIndex = data[minPos].index; // the real index to return

        data[minPos] = data[size - 1];
        --size;

        return minIndex;
    }

    void PriorityQueue::decreasePriority(int index, int newPriority){
        for (int i = 0; i < size; ++i) {
            if (data[i].index == index) {
                if (newPriority > data[i].priority)
                    throw std::invalid_argument("New priority is higher than current priority");
                if (newPriority == data[i].priority)
                    return;
                data[i].priority = newPriority;
                return;
            }
        }
        throw std::invalid_argument("Index not found in priority queue");
    }
    bool PriorityQueue::contains(int index) const{
        for (int i = 0; i < size; ++i){
            if (data[i].index == index)
                return true;
        }
        return false;
    }

    bool PriorityQueue::isEmpty() const{
        return size == 0;
    }

    // ============= Union Find ========
    // Constructor initializes the Union-Find structure with a given size.
    // Destructor cleans up the allocated memory.       
    // find returns the root of the set containing x, applying path compression.
    // unite merges the sets containing x and y, using union by rank.
    // If x and y are already in the same set, no action is taken.
    // If the size is invalid, an exception is thrown.
    // If the union operation fails, an exception is thrown.
    // If the find operation fails, an exception is thrown.
    // If the union operation is successful, the function returns without any value.
    // If the find operation is successful, the function returns the root of the set containing x.
    // If the union operation is successful, the function returns without any value.    
    UnionFind::UnionFind(int n) : size(n){
        parent = new int[size];
        rank = new int[size];

        for (int i = 0; i < size; ++i){
            parent[i] = i;
            rank[i] = 0;
        }
    }

    UnionFind::~UnionFind(){
        delete[] parent;
        delete[] rank;
    }

    int UnionFind::find(int x){
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void UnionFind::unite(int x, int y){
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY)
            return;

        if (rank[rootX] < rank[rootY]){
            parent[rootX] = rootY;
        }
        else if (rank[rootX] > rank[rootY]){
            parent[rootY] = rootX;
        }
        else{
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }

} // namespace graph