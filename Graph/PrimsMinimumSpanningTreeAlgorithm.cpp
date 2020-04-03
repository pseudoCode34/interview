// STL implementation of Prim's algorithm for MST
#include <iostream>
#include <list>
#include <queue>
#include <vector>

// This class represents a directed graph using adjacency list representation
class Graph {
	int V; // No. of vertices

	// In a weighted graph, we need to store vertex
	// and weight pair for every edge
	std::vector<std::list<std::pair<int, int>>> adj;

public:
	Graph(int V) : V(V) { adj.resize(V); }
	// function to add an edge to graph
	void addEdge(int u, int v, int w);

	// Print MST using Prim's algorithm
	void primMST(int firstVertex = 0);
};

// Allocates memory for adjacency list

void Graph::addEdge(int u, int v, int w) {
	adj[u].push_back({v, w});
	adj[v].push_back({u, w});
}

// Prints shortest paths from src to all other vertices
void Graph::primMST(int firstVertex) {
	// Create a priority queue to store vertices that
	// are being preinMST. This is weird syntax in C++.
	// Refer below link for details of this syntax
	// http://geeksquiz.com/implement-min-heap-using-stl/
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
						std::greater<std::pair<int, int>>>
		pq;

	// Create a vector for keys and initialize all
	// keys as infinite (INF)
	std::vector<int> key(V, std::numeric_limits<int>::max());

	// To store parent array which in turn store MST
	std::vector<int> parent(V, -1);

	// To keep track of vertices included in MST
	std::vector<bool> inMST(V, false);

	// Insert source itself in priority queue and initialize
	// its key as 0.
	pq.push({0, firstVertex});
	key[firstVertex] = 0;

	/* Looping till priority queue becomes empty */
	while (!pq.empty()) {
		// The first vertex in pair is the minimum key
		// vertex, extract it from priority queue.
		// vertex label is stored in second of pair (it
		// has to be done this way to keep the vertices
		// sorted key (key must be first item
		// in pair)
		int parentVertex = pq.top().second;
		pq.pop();

		inMST[parentVertex] = true; // Include vertex in MST

		for (auto &[childVertex, weight] : adj[parentVertex])

			// If v is not in MST and weight of (u,v) is smaller
			// than current key of v
			if (!inMST[childVertex] && key[childVertex] > weight) {
				// Updating key of v
				key[childVertex] = weight;
				pq.push({key[childVertex], childVertex});
				parent[childVertex] = parentVertex;
			}
	}

	// Print edges of MST using parent array
	for (int i = 1; i < V; ++i)
		std::cout << parent[i] << " - " << i << std::endl;
}

// Driver program to test methods of graph class
int main() {
	// create the graph given in above fugure
	int V = 9;
	Graph g(V);

	// making above shown graph
	g.addEdge(0, 1, 4);
	g.addEdge(0, 7, 8);
	g.addEdge(1, 2, 8);
	g.addEdge(1, 7, 11);
	g.addEdge(2, 3, 7);
	g.addEdge(2, 8, 2);
	g.addEdge(2, 5, 4);
	g.addEdge(3, 4, 9);
	g.addEdge(3, 5, 14);
	g.addEdge(4, 5, 10);
	g.addEdge(5, 6, 2);
	g.addEdge(6, 7, 1);
	g.addEdge(6, 8, 6);
	g.addEdge(7, 8, 7);

	g.primMST();

	return 0;
}

