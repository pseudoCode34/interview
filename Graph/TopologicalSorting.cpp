#include <iostream>
#include <list>
#include <vector>

void topologicalSortDFS(std::vector<std::list<int>> &graph, int src,
						std::vector<bool> &visited,
						std::list<int> &topologicalSortedList) {
	if (visited[src]) return;

	visited[src] = true;
	for (auto &childVertex : graph[src])
		topologicalSortDFS(graph, childVertex, visited, topologicalSortedList);
	topologicalSortedList.push_front(src);
}

std::list<int> topologicalSort(std::vector<std::list<int>> graph) {
	std::list<int> topologicalSortedList;
	std::vector<bool> visited(graph.size(), false);
	for (size_t src = 0; src < graph.size(); src++)
		topologicalSortDFS(graph, src, visited, topologicalSortedList);

	return topologicalSortedList;
}

int main() {
	std::vector<std::list<int>> graph;
	int v, e, src, des;
	std::cin >> v >> e;
	graph.resize(v);
	while (e--) {
		std::cin >> src >> des;
		graph[src].push_back(des);
	}

	std::list<int> topologicalSortedList = topologicalSort(graph);
	for (auto &vertex : topologicalSortedList) std::cout << vertex << " ";
	std::cout << std::endl;

	return 0;
}
