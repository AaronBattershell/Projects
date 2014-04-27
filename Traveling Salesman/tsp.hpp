#ifndef TSP_HPP
#define TSP_HPP

#include "node.hpp"
#include "result.hpp"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

#define inf -1
#define ndef 100000000

class tsp {
	public:
		node *head, *endPtr;
		int nodes,
			bestLowerBound;
	public:
		tsp(std::string);
		~tsp();
		result* shortestPath();
		void calcChildrenBounds(node *); // make all children full fledged nodes, assign them new grid values and lower bounds, children ect
		void calcLowerBound(node *, int = -1, int = -1);
		void addChildren(node *);
		void printGrid(node *);
		void printTree(node *, int = 0);


		bool isLinkedList(node *);			// Done
		node* getLowestBoundedNode(node *); // Done
		node* getLowestBoundedEndNode(node *); // needs checked
		bool isLeafNode(node *);		    // Done
		bool noPossibleChildren(node *);    // Done
		void pruneBranches(node *);			// Needs checked - Does it delete only leafNodes? Does it delete high branches with artificialy low lowerBounds?
		void deleteTree(node *);			// Done
		//bool allPathsLowestBound();		// May not need if removing all paths 
};

#endif