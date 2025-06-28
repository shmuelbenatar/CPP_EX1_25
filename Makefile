# email:shmuel.benatar@msmail.ariel.ac.il

CXX=g++
CXXFLAGS= -g -Wall -Wextra 

OBJECTS = Graph.cpp DataStructures.cpp Algorithms.cpp main.cpp
TESTOBJECTS = Graph.cpp DataStructures.cpp Algorithms.cpp TestGraph.cpp 

all: Main test

Main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o Main


test: $(TESTOBJECTS)
	$(CXX) $(CXXFLAGS) $(TESTOBJECTS) -o test

valgrind: Main
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes ./Main

clean:
	rm -f Main test *.o