#include <iostream>
#include <vector>

void floydWarshall(std::vector<std::vector<int>> &graph) {
	for (size_t k = 0; k < graph.size(); ++k)
		for (size_t i = 0; i < graph.size(); ++i)
			for (size_t j = 0; j < graph.size(); ++j)
				graph[i][j] = std::min(graph[i][j], graph[i][k] + graph[k][j]);
}

int main() {
	std::vector<std::vector<int>> graph;
	int v, e, src, des, weight;
	std::cin >> v >> e;
	graph.resize(v, std::vector<int>(v, 0));
	while (e--) {
		std::cin >> src >> des >> weight;
		graph[src][des] = weight;
	}
	floydWarshall(graph);
	for (int i = 0; i < v; i++) {
		for (int j = 0; j < v; j++) { std::cout << graph[i][j] << " "; }
		std::cout << std::endl;
	}
	return 0;
}
