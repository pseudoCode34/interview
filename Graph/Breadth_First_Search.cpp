#include <iostream>
#include <list>
#include <queue>
#include <vector>
void breadth_first_search(std::vector<std::list<int>> graph, int firstVertex) {
	std::vector<bool> visited(graph.size(), false);
	std::queue<int> Q;
	Q.push(firstVertex);
	visited[firstVertex] = true;
	while (!Q.empty()) {
		int parentVertex = Q.front();
		Q.pop();
		std::cout << parentVertex << " ";
		for (auto &childVertex : graph[parentVertex]) {
			if (!visited[childVertex]) Q.push(childVertex);
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
	breadth_first_search(graph, src);
	return 0;
}
