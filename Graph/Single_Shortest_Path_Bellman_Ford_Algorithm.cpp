#include <iostream>
#include <vector>

struct edge {
	size_t src, des, weight;
};

/*
 * Time complexity: Worst case O(V*E)
 * 			   Best case O(E)
 * Space complexity: O(V)
 *
 * Slower than Dijikstra's algorithm, O(VlogV), but able to detect negative
 * cycle in the graph, which is more versatile.
 */

std::pair<bool, std::vector<size_t>> bellmanFord(const std::vector<edge> &graph,
												 const size_t totalVertex,
												 const size_t sourceVertex) {
	std::vector<size_t> distances(totalVertex,
								  std::numeric_limits<size_t>::max());
	distances[sourceVertex] = 0;

	for (size_t i = 1; i < totalVertex; ++i)
		for (auto &[src, dest, weight] : graph)
			// relax(Edge &edge)
			if (distances[dest] > distances[src] + weight)
				distances[dest] = distances[src] + weight;

	for (auto &[src, dest, weight] : graph)
		if (distances[dest] > distances[src] + weight)
			// Negative Cyclce Exists
			return {false, std::vector<size_t>()};

	return {true, distances};
}

int main() {
	size_t totalEdge, sourceVertex, totalVertex;
	std::vector<edge> graph;
	std::cin >> totalEdge >> totalVertex;
	for (size_t i = 0; i < totalEdge; ++i) {
		std::cin >> graph[i].src >> graph[i].des >> graph[i].weight;
	}
	std::cin >> sourceVertex;

	const auto [isExistedPath, path] =
		bellmanFord(graph, totalVertex, sourceVertex);
	if (isExistedPath) {
		std::cout << "No Cycle Exist ! " << std::endl;
		for (auto &vertex : path) std::cout << vertex << " ";
	} else
		std::cout << "Graph Has Negative Weight Cycle" << std::endl;

	return 0;
}
