#include <iostream>
#include <list>
#include <stack>
#include <vector>

/*
 * Space complexity: O(V)
 * Time complexity: O(V + E)
 * References:
 * https://www.geeksforgeeks.org/strongly-connected-components/
 */

class Graph {
	size_t totalVertex;
	std::vector<std::list<size_t>> adjList;

	// Fills Stack with vertices (in increasing order of finishing times). The
	// top element of stack has the maximum finishing time
	void fillOrder(size_t parentVertex, std::vector<bool> &visited,
				   std::stack<size_t> &Stack);

	void DFS(size_t parentVertex, std::vector<bool> &visited);

public:
	Graph(const size_t totalVertex) : totalVertex(totalVertex) {
		adjList.resize(totalVertex);
	}

	// Directed edge
	void addEdge(const size_t parentVertex, const size_t childVertex);

	// The main function that finds and prints strongly connected components
	void printSCCs();

	// Function that returns the reverse (or transpose) of this graph
	Graph getTranspose();
};

// A recursive function to print DFS starting from parentVertex
void Graph::DFS(size_t parentVertex, std::vector<bool> &visited) {
	// Mark the current node as visited and print it
	visited[parentVertex] = true;
	std::cout << parentVertex << " ";

	for (auto &childVertex : adjList[parentVertex])
		if (!visited[childVertex]) DFS(childVertex, visited);
}

Graph Graph::getTranspose() {
	Graph reversedGraph(totalVertex);
	for (size_t parentVertex = 0; parentVertex < totalVertex; parentVertex++)
		for (auto &childVertex : adjList[parentVertex])
			reversedGraph.adjList[childVertex].push_back(parentVertex);

	return reversedGraph;
}

void Graph::addEdge(const size_t parentVertex, const size_t childVertex) {
	adjList[parentVertex].push_back(childVertex);
}

void Graph::fillOrder(size_t parentVertex, std::vector<bool> &visited,
					  std::stack<size_t> &Stack) {
	// Mark the current node as visited and print it
	visited[parentVertex] = true;

	for (auto &childVertex : adjList[parentVertex])
		if (!visited[childVertex]) fillOrder(childVertex, visited, Stack);

	// All vertices reachable from parentVertex are processed by now, push
	// parentVertex
	Stack.push(parentVertex);
}

void Graph::printSCCs() {
	std::stack<size_t> Stack;

	// Mark all the vertices as not visited (For first DFS)
	std::vector<bool> visited(totalVertex, false);

	// Fill vertices in stack according to their finishing times
	for (size_t vertex = 0; vertex < totalVertex; ++vertex)
		if (!visited[vertex]) fillOrder(vertex, visited, Stack);

	Graph reversedGraph = getTranspose();

	// Mark all the vertices as not visited (For second DFS)
	visited.assign(totalVertex, false);

	// Now process all vertices in order defined by Stack
	while (!Stack.empty()) {
		size_t parentVertex = Stack.top();
		Stack.pop();

		// Print Strongly connected component of the popped vertex
		if (!visited[parentVertex]) {
			reversedGraph.DFS(parentVertex, visited);
			std::cout << std::endl;
		}
	}
}

int main() {
	Graph g(5);
	g.addEdge(1, 0);
	g.addEdge(0, 2);
	g.addEdge(2, 1);
	g.addEdge(0, 3);
	g.addEdge(3, 4);

	std::cout << "Following are strongly connected components in "
				 "given graph"
			  << std::endl;
	g.printSCCs();
	return 0;
}
