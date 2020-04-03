#include <iostream>
#include <list>
#include <queue>
#include <vector>

std::vector<size_t>
dijkshtra(std::vector<std::list<std::pair<size_t, size_t>>> graph, size_t src) {
	std::priority_queue<std::pair<size_t, size_t>,
						std::vector<std::pair<size_t, size_t>>,
						std::greater<std::pair<size_t, size_t>>>
		Q;
	std::vector<size_t> distances(graph.size(),
								  std::numeric_limits<size_t>::max());
	std::vector<bool> visited(graph.size(), false);

	distances[src] = 0;
	Q.push({src, 0});

	while (!Q.empty()) {
		auto [current_vertex, distance_of_passed_vertex] = Q.top();
		Q.pop();
		std::cout << "Currently at" << current_vertex << std::endl;
		if (visited[current_vertex]) continue;

		visited[current_vertex] = true;
		for (auto &[neighbour_vertex, weight_current_neighbour] :
			 graph[current_vertex])
			if (distance_of_passed_vertex + weight_current_neighbour <
				distances[current_vertex]) {
				distances[current_vertex] =
					distance_of_passed_vertex + weight_current_neighbour;
				Q.push({current_vertex, distances[current_vertex]});
			}
	}

	return distances;
}
int main() {
	std::vector<std::list<std::pair<size_t, size_t>>> graph;
	size_t v, e, src, des, weight;
	std::cin >> v >> e;
	graph.resize(v);
	while (e--) {
		std::cin >> src >> des >> weight;
		graph[src].push_back({des, weight});
	}
	std::cin >> src;
	std::vector<size_t> distances = dijkshtra(graph, src);
	for (auto &distance_to_dest_vertex : distances)
		std::cout << distance_to_dest_vertex << " ";
	return 0;
}
