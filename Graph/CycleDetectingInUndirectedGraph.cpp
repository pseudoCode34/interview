#include <iostream>
#include <list>
#include <numeric>
#include <vector>

/*
 * References:
 * https://www.youtube.com/watch?v=n_t0a_8H8VY&list=PLrmLmBdmIlpu2f2g8ltqaaCZiq6GJvl1j&index=12
 * https://www.geeksforgeeks.org/detect-cycle-undirected-graph/
 */

/**
 * Underlying Arguments:
 * 		%Ranks% : represent approximate depth of the each node in the tree
 *		%Parent% represents each vertex's parentVertex
 *
 * Offer 3 operations:
 * 		makeSet(constructor)
 * 		find
 * 		merge
 *
 * Time complexity: O(m * alpha(n)) ~ O(4m) ~ O(m)
 * Where
 * 		m : total opertions
 * 		n : total elements
 * 		alpha(n) : slowly growing function, in practice, <= 4
 *
 * Representing disjoint sets using ranks and paths compression
 *
 */

class UnionFind {
	size_t __size;
	std::vector<size_t> parent, ranks;

public:
	/**
	 * a.k.a MakeSet
	 * Create each subset with a corresponding vertex. Mark theirs %parent as
	 * themselves and their rank are 0
	 */
	UnionFind(const size_t totalVertexes) : __size(totalVertexes) {
		parent.assign(totalVertexes, 0);
		ranks.assign(totalVertexes, 0);
		std::iota(parent.begin(), parent.end(), 0);
	}

	/**
	 * @param element A vertex
	 * @return	The vertex which is representative of the subset containing
	 *@param
	 *.
	 *
	 * If the subset containing this %element% has only 1 element, which
	 *contains %element% only, return %element%. Otherwise, recursively call
	 *this function to find the representative of the subset.
	 *
	 */
	size_t find(size_t element) {
		if (parent[element] == element) return element;
		return parent[element] = find(parent[element]);
	}

	/**
	 * @param x, y Two vertex
	 * @return If both of the representative of the subsets containing 2 @param
	 * are equal.
	 */
	bool isConnected(size_t x, size_t y) { return find(x) == find(y); }

	/**
	 * @param x, y Two vertex needed to unite in the same subset.
	 *
	 * Since they are in different subsets, we take the union of them. The
	 * vertex whose rank is higher will be the representative.
	 */
	void merge(size_t x, size_t y) {
		x = find(x);
		y = find(y);

		if (ranks[x] > ranks[y]) parent[y] = x;
		else if (ranks[x] < ranks[y])
			parent[x] = y;
		else {
			parent[x] = y;
			++ranks[y];
		}
		--__size;
	}

	size_t size() const { return __size; }
};

class Graph {
	bool isCyclicUsingDFSUtil(size_t vertex, size_t parentVertex,
							  std::vector<bool> &visited) {
		visited[vertex] = true;

		for (auto &childVertex : adjList[vertex]) {
			if (parentVertex == childVertex) continue;
			if (visited[childVertex]) return true;
			if (isCyclicUsingDFSUtil(childVertex, parentVertex, visited))
				return true;
		}
		return false;
	}

public:
	Graph(const size_t totalVertexes) : totalVertexes(totalVertexes) {
		adjList.resize(totalVertexes);
	}

	// Undirected edge
	void addEdge(const size_t parentVertex, const size_t childVertex) {
		adjList[parentVertex].push_back(childVertex);
		adjList[childVertex].push_back(parentVertex);
	}

	bool isCyclicUsingDFS() {
		std::vector<bool> visited(totalVertexes, false);
		for (size_t vertex = 0; vertex < totalVertexes; ++vertex) {
			if (visited[vertex]) continue;
			if (isCyclicUsingDFSUtil(vertex, 0, visited)) return true;
		}
		return false;
	}

	/**
	 * Cycle detecting using disjoint sets. For each edge, make subsets using
	 * both the vertices of the edge. If both the vertices are in the same
	 * subset, a cycle is found.
	 *
	 * Time complexity : O(V)
	 * Space complexity : O(V)
	 */
	bool isCyclicUsingDisjointSets() const {
		UnionFind uf(totalVertexes);

		for (size_t parentVertex = 0; parentVertex < totalVertexes;
			 ++parentVertex)
			for (auto &childVertex : adjList[parentVertex]) {
				if (uf.isConnected(parentVertex, childVertex)) return true;

				uf.merge(parentVertex, childVertex);
			}
		return false;
	}

private:
	size_t totalVertexes;
	std::vector<std::list<size_t>> adjList;
};

int main() {
	Graph g(5);
	g.addEdge(0, 1);
	g.addEdge(1, 2);
	g.addEdge(2, 3);
	g.addEdge(3, 1);
	g.addEdge(4, 1);

	if (g.isCyclicUsingDFS()) std::cout << "Graph contains cycle" << std::endl;
	else
		std::cout << "Graph has no cycle" << std::endl;
	return 0;
}
