#include <iostream>
#include <list>
#include <vector>

void connectedComponentsDFS(std::vector<std::list<size_t>> &graph,
							size_t sourceVertex, std::vector<bool> &visited) {
	if (visited[sourceVertex]) return;

	visited[sourceVertex] = true;
	for (auto &childVertex : graph[sourceVertex])
		connectedComponentsDFS(graph, childVertex, visited);
}

size_t connectedComponents(std::vector<std::list<size_t>> &graph) {
	size_t components = 0;
	std::vector<bool> visited(graph.size(), false);

	for (size_t sourceVertex = 0; sourceVertex < graph.size(); ++sourceVertex)
		if (!visited[sourceVertex]) {
			components++;
			connectedComponentsDFS(graph, sourceVertex, visited);
		}

	return components;
}

int main() {
	std::vector<std::list<size_t>> graph;
	size_t totalVertex, totalEdge, sourceVertex, destVertex;
	std::cin >> totalVertex >> totalEdge;
	graph.resize(totalVertex);
	while (totalEdge--) {
		std::cin >> sourceVertex >> destVertex;
		graph[sourceVertex].push_back(destVertex);
	}
	std::cout << connectedComponents(graph);
	return 0;
}

