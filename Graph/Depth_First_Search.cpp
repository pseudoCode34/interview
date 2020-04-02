#include <iostream>
#include <list>
#include <stack>
#include <vector>

void depth_first_search(std::vector<std::list<int>> graph, int parentVertex) {
	std::vector<bool> visited(graph.size(), false);
	std::vector<int> path;
	path.push_back(parentVertex);
	visited[parentVertex] = true;

	for (auto &childVertex : graph[parentVertex]) {
		if (!visited[childVertex]) {
			path.push_back(childVertex);
			std::cout << childVertex << std::endl;
		}
		visited[childVertex] = true;
	}
}
}

int main() {
	std::vector<std::list<int>> graph;
	int v, e, src, des;
	std::cin >> v >> e;
	graph.resize(v);
	while (e--) {
		std::cin >> src >> des;
		graph[src].push_back(des);
		graph[des].push_back(src);
	}
	std::cin >> src;
	depth_first_search(graph, src);
	return 0;
}
