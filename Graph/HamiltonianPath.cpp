#include <iostream>
#include <vector>

struct Edge {
	size_t src, dest;
};

struct Graph {
	std::vector<std::vector<size_t>> adjList;

	Graph(const std::vector<Edge> &edges, size_t totalVertex) {
		adjList.resize(totalVertex);

		// add edges to the undirected graph
		for (auto &[src, dest] : edges) {
			adjList[src].push_back(dest);
			adjList[dest].push_back(src);
		}
	}
};

void printAllHamiltonianPaths(const Graph &g, size_t parentVertex,
							  std::vector<bool> &visited,
							  std::vector<size_t> &path, size_t totalVertex) {
	// if all the vertices are visited, then Hamiltonian path exists, so print
	// it out
	if (path.size() == totalVertex) {
		for (auto &vertex : path) std::cout << vertex << " ";
		std::cout << std::endl;

		return;
	}

	// Check if every edge starting from parentVertex leads to a solution or not
	for (auto &childVertex : g.adjList[parentVertex])
		// process only unvisited vertices as Hamiltonian
		// path visits each vertex exactly once
		if (!visited[childVertex]) {
			visited[childVertex] = true;
			path.push_back(childVertex);

			// check if adding vertex childVertex to the path leads
			// to solution or not
			printAllHamiltonianPaths(g, childVertex, visited, path,
									 totalVertex);

			// Backtrack
			// visited[childVertex] = false;
			// path.pop_back();
		}
}

// main function
int main() {
	// consider complete graph having 4 vertices
	std::vector<Edge> edges = {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 0},
							   {0, 1}, {2, 0}, {3, 5}, {2, 5}, {3, 0}};

	// starting node
	size_t start = 1;

	// Number of vertices in the graph
	size_t totalVertex = 6;

	// create a graph from edges
	Graph g(edges, totalVertex);

	// add starting node to the path
	std::vector<size_t> path;
	path.push_back(start);

	// mark start node as visited
	std::vector<bool> visited(totalVertex, false);
	visited[start] = true;

	printAllHamiltonianPaths(g, start, visited, path, totalVertex);

	return 0;
}
