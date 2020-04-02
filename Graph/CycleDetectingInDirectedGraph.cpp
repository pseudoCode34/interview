// A C++ Program to detect cycle in a graph
#include <iostream>
#include <list>
#include <vector>

class Graph {
	size_t totalVertexes;
	std::vector<std::list<size_t>> adj;
	bool isCyclicUtil(size_t parentVertex, std::vector<bool> &visited,
					  std::vector<bool> &recStack);

public:
	Graph(size_t totalVertexes) : totalVertexes(totalVertexes) {
		adj.resize(totalVertexes);
	}

	void addEdge(const size_t parentVertex, const size_t childVertex) {
		adj[parentVertex].push_back(childVertex);
	}

	bool isCyclic();
};

// This function is a variation of DFSUtil() in
// https://www.geeksforgeeks.org/archives/18212
bool Graph::isCyclicUtil(size_t parentVertex, std::vector<bool> &visited,
						 std::vector<bool> &recStack) {
	if (!visited[parentVertex]) {
		// Mark the current node as visited and part of recursion stack
		visited[parentVertex] = true;
		recStack[parentVertex] = true;

		for (auto &childVertex : adj[parentVertex]) {
			if (!visited[childVertex] &&
				isCyclicUtil(childVertex, visited, recStack))
				return true;
			if (recStack[childVertex]) return true;
		}
	}
	recStack[parentVertex] = false; // remove the vertex from recursion stack
	return false;
}

// This function is a variation of DFS() in
// https://www.geeksforgeeks.org/archives/18212
bool Graph::isCyclic() {
	// Mark all the vertices as not visited and not part of recursion stack
	std::vector<bool> visited(totalVertexes, false);
	std::vector<bool> recStack(totalVertexes, false);

	for (size_t vertex = 0; vertex < totalVertexes; vertex++)
		if (isCyclicUtil(vertex, visited, recStack)) return true;

	return false;
}

int main() {
	// Create a graph given in the above diagram
	Graph g(4);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(2, 3);
	g.addEdge(3, 3);
	g.addEdge(2, 0);

	if (g.isCyclic()) std::cout << "Graph contains cycle" << std::endl;
	else
		std::cout << "Graph has no cycle" << std::endl;
	return 0;
}

