/*
 * A segment tree is a tree data structure for storing intervals, or segments.
 * It allows for faster querying, i.e sum or min, in these intervals. Lazy
 * propagation is useful when there are high number of updates in the input
 * array. Write a program to support mininmum range query
 *
 * Time complexity to create segment tree is O(n) since new array will be at max
 * 4n size.
 * Space complexity to create segment tree is O(n) since new array will
 * be at max 4n size.
 * Time complexity to search in segment tree is O(logn) since
 * you would at max travel 4 depths.
 * Time complexity to update in segment tree is
 * O(logn).
 * Time complexity to update range in segment tree is O(range)
 *
 * References:
 * http://www.geeksforgeeks.org/segment-tree-set-1-sum-of-given-range/
 * http://www.geeksforgeeks.org/segment-tree-set-1-range-minimum-query/
 * https://www.topcoder.com/community/data-science/data-science-tutorials/range-minimum-query-and-lowest-common-ancestor/
 * https://github.com/mission-peace/interview/blob/master/src/com/interview/tree/SegmentTreeMinimumRangeQuery.java
 */

#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

/**
 * http://www.geeksforgeeks.org/next-power-of-2/
 */
size_t NextPowerOf2(size_t num) {
	if (num == 0) return 1;
	if (num > 0 && (num & (num - 1)) == 0) return num;
	while ((num & (num - 1)) > 0) num = num & (num - 1);
	return num << 1;
}

void constructMinSegmentTree(std::vector<int> &segmentTree,
							 std::vector<int> &input, size_t low, size_t high,
							 size_t pos) {
	if (low == high) {
		segmentTree[pos] = input[low];
		return;
	}

	size_t mid = (low + high) / 2;
	constructMinSegmentTree(segmentTree, input, low, mid, 2 * pos + 1);
	constructMinSegmentTree(segmentTree, input, mid + 1, high, 2 * pos + 2);
	segmentTree[pos] =
		std::min(segmentTree[2 * pos + 1], segmentTree[2 * pos + 2]);
}

/**
 * Creates a new segment tree based off input array.
 */

std::vector<int> createSegmentTree(std::vector<int> &input) {
	size_t nextPowerOfTwo = NextPowerOf2(input.size());
	// if input len is pow of 2 then size of
	// segment tree is 2*len - 1, otherwise
	// size of segment tree is next (pow of 2 for len)*2 - 1.
	std::vector<int> segmentTree(nextPowerOfTwo * 2 - 1, INT_MAX);
	constructMinSegmentTree(segmentTree, input, 0, input.size() - 1, 0);
	return segmentTree;
}

void updateSegmentTree(std::vector<int> &segmentTree, size_t index,
					   size_t delta, size_t low, size_t high, size_t pos) {
	// if index to be updated is less than low or higher than high just return.
	if (index < low || index > high) return;

	// if low and high become equal, then index will be also equal to them and
	// update that value in segment tree at pos
	if (low == high) {
		segmentTree[pos] += delta;
		return;
	}

	// otherwise keep going left and right to find index to be updated
	// and then update current tree position if min of left or right has
	// changed.
	size_t mid = (low + high) / 2;
	updateSegmentTree(segmentTree, index, delta, low, mid, 2 * pos + 1);
	updateSegmentTree(segmentTree, index, delta, mid + 1, high, 2 * pos + 2);
	segmentTree[pos] =
		std::min(segmentTree[2 * pos + 1], segmentTree[2 * pos + 2]);
}

/**
 * Updates segment tree for certain index by given delta
 */

void updateSegmentTree(std::vector<int> &input, std::vector<int> &segmentTree,
					   size_t index, size_t delta) {
	input[index] += delta;
	updateSegmentTree(segmentTree, index, delta, 0, input.size() - 1, 0);
}

void updateSegmentTreeRange(std::vector<int> &segmentTree, size_t startRange,
							size_t endRange, size_t delta, size_t low,
							size_t high, size_t pos) {
	if (low > high || startRange > high || endRange < low) return;

	if (low == high) {
		segmentTree[pos] += delta;
		return;
	}

	size_t middle = (low + high) / 2;
	updateSegmentTreeRange(segmentTree, startRange, endRange, delta, low,
						   middle, 2 * pos + 1);
	updateSegmentTreeRange(segmentTree, startRange, endRange, delta, middle + 1,
						   high, 2 * pos + 2);
	segmentTree[pos] =
		std::min(segmentTree[2 * pos + 1], segmentTree[2 * pos + 2]);
}
/**
 * Updates segment tree for given range by given delta
 */
void updateSegmentTreeRange(std::vector<int> &input,
							std::vector<int> &segmentTree, size_t startRange,
							size_t endRange, size_t delta) {
	for (size_t i = startRange; i < endRange; ++i) input[i] += delta;
	updateSegmentTreeRange(segmentTree, startRange, endRange, delta, 0,
						   input.size() - 1, 0);
}

int rangeMinimumQuery(std::vector<int> &segmentTree, size_t low, size_t high,
					  size_t qlow, size_t qhigh, size_t pos) {
	if (qlow <= low && qhigh >= high) return segmentTree[pos];

	if (qlow > high || qhigh < low) return INT_MAX;

	size_t mid = (low + high) / 2;
	return std::min(
		rangeMinimumQuery(segmentTree, low, mid, qlow, qhigh, 2 * pos + 1),
		rangeMinimumQuery(segmentTree, mid + 1, high, qlow, qhigh,
						  2 * pos + 2));
}

/**
 * Queries given range for minimum value.
 */
int rangeMinimumQuery(std::vector<int> &segmentTree, size_t qlow, size_t qhigh,
					  size_t len) {
	return rangeMinimumQuery(segmentTree, 0, len - 1, qlow, qhigh, 0);
}

void updateSegmentTreeRangeLazy(std::vector<int> &segmentTree,
								std::vector<int> &lazy, size_t startRange,
								size_t endRange, size_t delta, size_t low,
								size_t high, size_t pos) {
	if (low > high) return;

	// make sure all propagation is done at pos. If not update tree
	// at pos and mark its children for lazy propagation.
	if (lazy[pos] != 0) {
		segmentTree[pos] += lazy[pos];
		if (low != high) { // not a leaf node
			lazy[2 * pos + 1] += lazy[pos];
			lazy[2 * pos + 2] += lazy[pos];
		}
		lazy[pos] = 0;
	}

	// no overlap condition
	if (startRange > high || endRange < low) return;

	// total overlap condition
	if (startRange <= low && endRange >= high) {
		segmentTree[pos] += delta;
		if (low != high) {
			lazy[2 * pos + 1] += delta;
			lazy[2 * pos + 2] += delta;
		}
		return;
	}

	// otherwise partial overlap so look both left and right.
	size_t mid = (low + high) / 2;
	updateSegmentTreeRangeLazy(segmentTree, lazy, startRange, endRange, delta,
							   low, mid, 2 * pos + 1);
	updateSegmentTreeRangeLazy(segmentTree, lazy, startRange, endRange, delta,
							   mid + 1, high, 2 * pos + 2);
	segmentTree[pos] =
		std::min(segmentTree[2 * pos + 1], segmentTree[2 * pos + 2]);
}

/**
 * Updates given range by given delta lazily
 */

void updateSegmentTreeRangeLazy(std::vector<int> &input,
								std::vector<int> &segmentTree,
								std::vector<int> &lazy, size_t startRange,
								size_t endRange, size_t delta) {
	updateSegmentTreeRangeLazy(segmentTree, lazy, startRange, endRange, delta,
							   0, input.size() - 1, 0);
}

int rangeMinimumQueryLazy(std::vector<int> &segmentTree, std::vector<int> &lazy,
						  size_t qlow, size_t qhigh, size_t low, size_t high,
						  size_t pos) {
	if (low > high) return INT_MAX;

	// make sure all propagation is done at pos. If not update tree
	// at pos and mark its children for lazy propagation.
	if (lazy[pos] != 0) {
		segmentTree[pos] += lazy[pos];
		if (low != high) { // not a leaf node
			lazy[2 * pos + 1] += lazy[pos];
			lazy[2 * pos + 2] += lazy[pos];
		}
		lazy[pos] = 0;
	}

	// no overlap
	if (qlow > high || qhigh < low) return INT_MAX;

	// total overlap
	if (qlow <= low && qhigh >= high) return segmentTree[pos];

	// partial overlap
	size_t mid = (low + high) / 2;
	return std::min(rangeMinimumQueryLazy(segmentTree, lazy, qlow, qhigh, low,
										  mid, 2 * pos + 1),
					rangeMinimumQueryLazy(segmentTree, lazy, qlow, qhigh,
										  mid + 1, high, 2 * pos + 2));
}

int rangeMinimumQueryLazy(std::vector<int> &segmentTree, std::vector<int> &lazy,
						  size_t qlow, size_t qhigh, size_t len) {
	return rangeMinimumQueryLazy(segmentTree, lazy, qlow, qhigh, 0, len - 1, 0);
}

int main() {
	std::vector<int> input{0, 3, 4, 2, 1, 6, -1};
	std::vector<int> segTree = createSegmentTree(input);
	std::cout << rangeMinimumQuery(segTree, 2, 3, input.size()) << std::endl;
	return EXIT_SUCCESS;
}

