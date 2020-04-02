#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <optional>
#include <set>
#include <stack>
#include <vector>

class Graph {
public:
	Graph(const size_t totalVertexes) : totalVertexes(totalVertexes) {
		adjList.resize(totalVertexes);
	}

	void addEdge(const size_t parentVertex, const size_t secondVertex) {
		adjList[parentVertex].push_back(secondVertex);
	}

	size_t getTotalVertexes() const { return totalVertexes; }

	const std::vector<std::list<size_t>> &getAdjList() const { return adjList; }

private:
	size_t totalVertexes;
	std::vector<std::list<size_t>> adjList;
};

class TarjanStronglyConnectedComponents {
public:
	TarjanStronglyConnectedComponents(Graph &graph) {
		visited.assign(graph.getTotalVertexes(), false);
		result.resize(graph.getTotalVertexes());
	}

	std::list<std::set<size_t>> scc(Graph &graph) {
		for (size_t vertex = 0; vertex < graph.getTotalVertexes(); ++vertex)
			if (!visited[vertex]) sccUtil(graph, vertex);
		return result;
	}

	void sccUtil(Graph &graph, size_t vertex) {
		visited[vertex] = true;
		visitedTime.insert({vertex, time});
		lowTime.insert({vertex, time});
		++time;
		stack.push(vertex);
		onStack.insert(vertex);

		for (auto &childVertex : graph.getAdjList()[vertex]) {
			// if child is not visited then visit it and see if it has link back
			// to vertex's ancestor. In that case update low time to ancestor's
			// visit time
			if (!visited[childVertex]) {
				sccUtil(graph, childVertex);
				lowTime[vertex] =
					std::min(lowTime[vertex], lowTime[childVertex]);
			}
			// if child is on stack then see if it was visited before vertex's
			// low time. If yes then update vertex's low time to that.
			else if (onStack.contains(childVertex))
				lowTime[vertex] =
					std::min(lowTime[vertex], visitedTime[childVertex]);
		}

		// If vertex low time is same as visited time, this is the start vertex
		// for strongly connected component. keep popping vertices out of stack
		// still you find current vertex. They are all part of one strongly
		// connected component.
		if (visitedTime.at(vertex) == lowTime.at(vertex)) {
			std::set<size_t> stronglyConnectedComponent;
			size_t v;
			do {
				v = stack.top();
				stack.pop();
				std::erase_if(onStack, [v](size_t a) { return a == v; });
				stronglyConnectedComponent.insert(v);
			} while (vertex != v);

			result.push_back(stronglyConnectedComponent);
		}
	}

private:
	// keeps map of vertex to time it was visited
	std::map<size_t, size_t> visitedTime;
	// keeps map of vertex and time of first vertex visited in current DFS
	std::map<size_t, size_t> lowTime;
	// tells if a vertex is in stack or not
	std::set<size_t> onStack;
	// stack of visited vertices
	std::stack<size_t> stack;
	// tells if vertex has ever been visited or not. This is for DFS purpose.
	std::vector<bool> visited;
	// stores the strongly connected components result;
	std::list<std::set<size_t>> result;

	// keeps the time when every vertex is visited
	size_t time = 0;
};

int main(int argc, char *argv[]) {
	std::cout << "\nSCCs in first graph \n";
	Graph g1(5);
	g1.addEdge(1, 0);
	g1.addEdge(0, 2);
	g1.addEdge(2, 1);
	g1.addEdge(0, 3);
	g1.addEdge(3, 4);
	TarjanStronglyConnectedComponents tarjan1(g1);
	for (auto &x : tarjan1.scc(g1)) {
		if (x.empty()) continue;
		for (auto &y : x) std::cout << y << " ";
		std::cout << std::endl;
	}

	std::cout << "\nSCCs in second graph \n";
	Graph g2(4);
	g2.addEdge(0, 1);
	g2.addEdge(1, 2);
	g2.addEdge(2, 3);
	TarjanStronglyConnectedComponents tarjan2(g2);
	for (auto &x : tarjan2.scc(g2)) {
		if (x.empty()) continue;
		for (auto &y : x) std::cout << y << ' ';
		std::cout << std::endl;
	}

	std::cout << "\nSCCs in third graph \n";
	Graph g3(7);
	g3.addEdge(0, 1);
	g3.addEdge(1, 2);
	g3.addEdge(2, 0);
	g3.addEdge(1, 3);
	g3.addEdge(1, 4);
	g3.addEdge(1, 6);
	g3.addEdge(3, 5);
	g3.addEdge(4, 5);
	TarjanStronglyConnectedComponents tarjan3(g3);
	for (auto &x : tarjan3.scc(g3)) {
		if (x.empty()) continue;
		for (auto &y : x) std::cout << y << ' ';
		std::cout << std::endl;
	}
	std::cout << "\nSCCs in fourth graph \n";
	Graph g4(11);
	g4.addEdge(0, 1);
	g4.addEdge(0, 3);
	g4.addEdge(1, 2);
	g4.addEdge(1, 4);
	g4.addEdge(2, 0);
	g4.addEdge(2, 6);
	g4.addEdge(3, 2);
	g4.addEdge(4, 5);
	g4.addEdge(4, 6);
	g4.addEdge(5, 6);
	g4.addEdge(5, 7);
	g4.addEdge(5, 8);
	g4.addEdge(5, 9);
	g4.addEdge(6, 4);
	g4.addEdge(7, 9);
	g4.addEdge(8, 9);
	g4.addEdge(9, 8);
	TarjanStronglyConnectedComponents tarjan4(g4);
	for (auto &x : tarjan4.scc(g4)) {
		if (x.empty()) continue;
		for (auto &y : x) std::cout << y << ' ';
		std::cout << std::endl;
	}

	std::cout << "\nSCCs in fifth graph \n";
	Graph g5(5);
	g5.addEdge(0, 1);
	g5.addEdge(1, 2);
	g5.addEdge(2, 3);
	g5.addEdge(2, 4);
	g5.addEdge(3, 0);
	g5.addEdge(4, 2);
	TarjanStronglyConnectedComponents tarjan5(g5);
	for (auto &x : tarjan5.scc(g5)) {
		if (x.empty()) continue;
		for (auto &y : x) std::cout << y << ' ';
		std::cout << std::endl;
	}
}
