#ifndef RESULT_HPP
#define RESULT_HPP

#include <vector>

struct result {
	int pathSum;
	std::vector<int> shortestPath;
	result() : pathSum(0) { }
};

#endif