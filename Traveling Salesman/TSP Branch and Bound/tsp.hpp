#ifndef TSP_HPP
#define TSP_HPP

#include "node.hpp"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

#define inf -1
#define ndef 100000000

class tsp {
	private:
		node *head, *endPtr;
		int nodes, bestLowerBound;

		void addChildren(node *);
		void calcShortestPath();
		void calcChildrenBounds(node *);
		void calcLowerBound(node *, int = -1, int = -1);
		void deleteTree(node *);
		node *getLowestBoundedEndNode(node *); 
		node *getLowestBoundedNode(node *);
		bool isLinkedList(node *);
		bool isLeafNode(node *);	
		bool noPossibleChildren(node *);    
		void printGrid(node *);
		void printTree(node *, int = 0);
		void pruneBranches(node *);

	public:
		tsp(std::string);
		~tsp();

		void printSolution();
};

#endif
