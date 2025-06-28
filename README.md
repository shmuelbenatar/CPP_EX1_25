
# Graph Project - Adjacency List Implementation

## Author
Shmuel Ben Atar  
Email: shmuel.benatar@msmail.ariel.ac.il

---

## Project Overview
This project implements an undirected weighted graph using an adjacency list without the use of the C++ Standard Template Library (STL).  
The project demonstrates memory management, class design, and basic data structures such as queues, priority queues, and union-find.

---

## Project Structure
The project is divided into the following components:
- **Graph:** Implementation of an undirected weighted graph using an adjacency list.
- **Algorithms:** Contains implementations of BFS, DFS, Dijkstra, Prim, and Kruskal algorithms.
- **Data Structures:** Custom implementations of Queue, Priority Queue, and Union-Find for algorithm support.
- **Unit Tests:** Implemented using the `doctest` library to verify correctness.
- **Main File:** Demonstrates the usage of the graph and the algorithms.

---

## File Structure
- `Graph.h / Graph.cpp` – Graph class and its functions.
- `Algorithms.h / Algorithms.cpp` – Graph algorithms.
- `DataStructures.h / DataStructures.cpp` – Queue, Priority Queue, Union-Find.
- `TestGraph.cpp` – Unit tests with `doctest`.
- `doctest.h` – Testing framework (provided).
- `main.cpp` – Demonstration of graph construction and algorithm executions.
- `Makefile` – Compilation and execution management.

---

## Build Instructions
Use the following commands to compile and run the project:
- `make Main` – Build and run the main demo file.
- `make test` – Build and run the unit tests.
- `make valgrind` – Run memory leak checks using `valgrind`.
- `make clean` – Clean all generated files.

---

## Features
- Graph represented by an adjacency list.
- Add and remove edges with full input validation.
- Breadth-First Search (BFS) – builds a BFS tree.
- Depth-First Search (DFS) – builds a DFS tree/forest.
- Dijkstra’s algorithm – builds the shortest path tree.
- Prim’s algorithm – builds the Minimum Spanning Tree (MST).
- Kruskal’s algorithm – builds the MST using Union-Find.
- Full error handling and memory management.
- Extensive unit tests, including edge cases and exception tests.
- Valgrind verified to ensure no memory leaks.

---

## Notes
- The project strictly avoids using the STL.
- The graph and supporting data structures are fully manually managed.
