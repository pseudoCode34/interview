#include <algorithm>
#include <iostream>
#include <list>
#include <numeric>
#include <vector>

/* Space complexity: O(E+V)
 * Time complexity: O(ElogE)
 */

struct edge {
	size_t srcVertex, destVertex, weight;
	bool operator<(const edge &other) const {
		return this->weight < other.weight;
	}
};

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
		// FIXME SIGSEGV, Segmentation fault
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

std::vector<edge> kruskalsAlgorithm(std::vector<edge> &graph,
									size_t totalVertexes) {
	UnionFind uf(totalVertexes);
	std::vector<edge> spanningTree;
	sort(graph.begin(), graph.end());

	for (auto &[srcVertex, destVertex, weight] : graph) {
		if (uf.isConnected(srcVertex, destVertex)) continue;

		uf.merge(srcVertex, destVertex);
		spanningTree.push_back({srcVertex, destVertex, weight});
	}

	return spanningTree;
}

int main() {
	/*
	std::vector<edge> graph;
	size_t totalEdges, totalVertexes;
	std::cin >> totalEdges >> totalVertexes;
	graph.resize(totalEdges);
	for (size_t i = 0; i < totalEdges; ++i)
		std::cin >> graph[i].srcVertex >> graph[i].destVertex >>
			graph[i].weight;
	std::cout << std::endl;
	*/

	std::vector<edge> graph{{1, 2, 3},
							{0, 1, 2},
							{2, 3, 1},
							{0, 3, 2},
							{1, 3, 4}};
	size_t totalVertexes = 4, totalEdges = 5;
	std::vector<edge> spanningTree = kruskalsAlgorithm(graph, totalVertexes);
	for (auto &[srcVertex, destVertex, weight] : spanningTree)
		std::cout << srcVertex << " -> " << destVertex << ": " << weight
				  << std::endl;

	return 0;
}
