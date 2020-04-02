#include <iostream>
#include <list>
#include <vector>

void depth_first_search(std::vector<std::list<int>> graph, int parentVertex,
						std::vector<bool> &visited) {
	if (visited[parentVertex]) return;

	std::cout << parentVertex << " ";
	visited[parentVertex] = true;
	for (auto &childVertex : graph[parentVertex])
		depth_first_search(graph, childVertex, visited);
}

int main() {
	std::vector<std::list<int>> graph;
	std::vector<bool> visited;
	int v, e, src, des;
	std::cin >> v >> e;
	graph.resize(v);
	visited.resize(v, false);
	while (e--) {
		std::cin >> src >> des;
		graph[src].push_back(des);
	}
	std::cin >> src;
	depth_first_search(graph, src, visited);
	return 0;
}
