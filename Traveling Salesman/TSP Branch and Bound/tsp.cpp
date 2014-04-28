#include "tsp.hpp"

/*
/ constructor
/	Reads in grid data from a file specified by the user and assigns values
/   to the head node.
*/
tsp::tsp(std::string filePath) : bestLowerBound(1000000000), head(new node) {
	std::fstream in (filePath.c_str(), std::fstream::in);

	// Check if the file was found
	if (!in.is_open()) {
		std::cerr << "File not found!" << std::endl;
		exit(1);
	}

	// Get map connection data from the file specified
	in >> nodes;
	for (int i = 0; i < nodes; ++i) {
		head->grid.push_back(std::vector<int>());
		for (int n = 0; n < nodes; ++n) {
			int tempVal;
			in >> tempVal;
			head->grid[i].push_back(tempVal);
		}
	}
	in.close();

	// Assign values to the starting graph node
	head->id = 0;
	calcLowerBound(head);
	addChildren(head);
	for (int i = 1; i < nodes; ++i) {
		head->conn.push_back(i);
	}
}

/*
/ destructor
*/
tsp::~tsp() {
	deleteTree(head);
}

/*
/ printSolution
/	The only function available to be called by the user, this function prints to
/   console the optimal path, along with the path's cost.
*/
void tsp::printSolution() {
	calcShortestPath();

	std::cout << "Method : Branch and Bound\nShortest traversal sum: " 
		<< bestLowerBound << "\n\tNode order : ";

	node *nodePtr = head;
	while (!isLeafNode(nodePtr)) {
		std::cout << nodePtr->id << ' ';
		nodePtr = nodePtr->children.begin()->second;
	}
	std::cout << nodePtr->id << " 0" << std::endl;
}

/*
/ shortestPath
/	Called by printSolution(), this function contains the body of logic that
/   drives this program to produce the optimal path.
*/
void tsp::calcShortestPath() {
	 do {
		node *nodePtr = getLowestBoundedNode(head);
		while (!noPossibleChildren(nodePtr)) {
			calcChildrenBounds(nodePtr); 
			nodePtr = getLowestBoundedNode(nodePtr);
		}

		node *bestNode = getLowestBoundedEndNode(head);
		endPtr = bestNode;
		bestLowerBound = bestNode->lowerBound;

		pruneBranches(head);
	} while (!isLinkedList(head));
}

/*
/ calcChildrenBounds
/	A high level driving function that assigns to any given node its
/   children with proper values.
*/
void tsp::calcChildrenBounds (node *nodePtr) {
	addChildren(nodePtr);

	for (auto &iter : nodePtr->children) {	
		calcLowerBound(iter.second, nodePtr->id, iter.second->id);
	}
}

/*
/ calcLowerBound
/	Assignse to all nodes passed in to it a proper lower bound and
/   edits the nodes connection grid.
*/
void tsp::calcLowerBound(node *curNode, int from, int to) { // x: from, y: to
	int lowBound = 0,
		minElement = 0;
	if (from != -1 && to != -1) {
		lowBound += curNode->grid[from][to];
		curNode->grid[to][from] = inf;
		
		// Set regions of the graph to inifity to dissalow infinite loops
		for (int i = 0; i < nodes; ++i) {
			curNode->grid[from][i] = inf;
			curNode->grid[i][to] = inf;
		}
	}

	// Remove values horizontaly
	for (int i = 0; i < nodes; ++i) {
		minElement = ndef;
		for (int n = 0; n < nodes; ++n) {
			minElement = (minElement > curNode->grid[i][n] && curNode->grid[i][n] != inf ? curNode->grid[i][n] : minElement);
		}

		lowBound += (minElement == ndef ? 0 : minElement);
		if (lowBound != ndef) {
			for (int n = 0; n < nodes; ++n) {
				curNode->grid[i][n] -= (curNode->grid[i][n] == inf ? 0 : minElement);
			}
		}
	}

	// Remove values vertiacaly 
	for (int i = 0; i < nodes; ++i) {
		minElement = ndef;
		for (int n = 0; n < nodes; ++n) {
			minElement = (minElement > curNode->grid[n][i] && curNode->grid[n][i] != inf ? curNode->grid[n][i] : minElement);
		}

		lowBound += (minElement == ndef ? 0 : minElement);
		if (lowBound != ndef) {
			for (int n = 0; n < nodes; ++n) {
				curNode->grid[n][i] -= (curNode->grid[n][i] == inf ? 0 : minElement);
			}
		}
	}

	curNode->lowerBound += lowBound; 
}

/*
/ addChildren
/	For all the integer values stored in the conn vector, a passed in node
/   will be created with the proper values.
*/
void tsp::addChildren(node *nodePtr) {
	for (auto &iter : nodePtr->conn) {
		nodePtr->children[iter] = new node(iter, nodePtr->lowerBound, nodePtr->conn, nodePtr->grid); // where the magic happens
	}
}

/*
/ isLinkedList
/	Returns true if all nodes in the tree have less than or equal to one child, else false.
*/
bool tsp::isLinkedList(node *nodePtr) {
	return (nodePtr->children.size() == 0 ? true : (nodePtr->children.size() != 1) ? false : isLinkedList(nodePtr->children.begin()->second));
}

/*
/ getLowestBoundedNode - double check
/	Scanning all the nodes in a tree, this function returns the leaf node with the lowest
/	lower bound.
*/
node* tsp::getLowestBoundedNode(node *nodePtr) {
	if (isLeafNode(nodePtr)) {
		return nodePtr;
	}

	std::map<int,node*>::iterator iter = nodePtr->children.begin();
	node *minNode = getLowestBoundedNode(iter->second);
	
	// Iterate through all children, getting the one with the lowest bound
	for (++iter; iter != nodePtr->children.end(); ++iter) {
		node *tempResult = getLowestBoundedNode(iter->second);
		if (minNode->lowerBound > tempResult->lowerBound && tempResult != nodePtr) { //DOUBEL CHECK THISSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
			minNode = tempResult;
		}
	}

	return minNode;
}

/*
/ getLowestBoundedEndNode
/	Scanning all the nodes in a tree, this function returns the leaf node of a compleate path
/   (there will only ever be two at a time givin this implementation) that has the lowest value.
*/
node* tsp::getLowestBoundedEndNode(node *nodePtr) {
	if (isLeafNode(nodePtr)) {
		return (nodePtr->conn.empty() ? nodePtr : NULL);
	}

	std::map<int,node*>::iterator iter = nodePtr->children.begin();
	node *minNode = getLowestBoundedEndNode(iter->second);
	
	// Iterate through all children, getting an end node with the lowest bound
	for (++iter; iter != nodePtr->children.end(); ++iter) {
		node *tempResult = getLowestBoundedEndNode(iter->second);
		if ((minNode == NULL ? ndef : minNode->lowerBound) > (tempResult == NULL ? ndef : tempResult->lowerBound)) {
			minNode = tempResult;
		}
	}

	return minNode;
}

/*
/ isLeafNode
/	True if a node has no child nodes, else false.
*/
bool tsp::isLeafNode(node *nodePtr) {
	return nodePtr->children.size() == 0;
}

/*
/ noPossibleChildren
/	True if a node has no possible children (all nodes have been visited), else false.
*/
bool tsp::noPossibleChildren(node *nodePtr) {
	return nodePtr->conn.size() == 0;
}

/*
/ pruneBranches
/	Scans the tree of elements removing all nodes with a greater lower bound than the
/	lowest bound found so far.
*/
void tsp::pruneBranches(node *nodePtr) {
	std::vector<int> toDelete;
	for (auto &iter : nodePtr->children) {
		if ((iter.second->lowerBound >= bestLowerBound && iter.second != endPtr && isLeafNode(iter.second)) || iter.second->bad) { // If to high and not last node
			toDelete.push_back(iter.second->id);
			deleteTree(iter.second);
			continue;
		}
		pruneBranches(iter.second);
	}

	if (!toDelete.empty()) {
		for (auto &iter : toDelete) {
			nodePtr->children.erase(iter);
		}
		if (nodePtr->children.empty()) {
			nodePtr->bad = true;
		}
	}
}

/*
/ deleteTree
/	Recursivly deletes a node and all its children.
*/
void tsp::deleteTree(node *nodePtr) { // Curently being worked on
	for (auto &iter : nodePtr->children) {
		deleteTree(iter.second);
	}

	delete nodePtr;
	nodePtr = NULL;
}

/*
/ printGrid
/	Meant for testing purposes, this function prints out the DAG of a node.
*/
void tsp::printGrid(node *nodePtr) {
	for (int i = 0; i < nodes; ++i) {
		for (int n = 0; n < nodes; ++n) {
			std::cout << std::setw(3) << nodePtr->grid[i][n] << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

/*
/ printTree
/	Meant for testing purposes, this function prints out the tree of connections.
*/
void tsp::printTree(node *nodePtr, int depth) {
	for (int i = 0; i < depth; ++i) {
		std::cout << "  ";
	}

	std::cout << nodePtr->id << std::endl;

	for (auto &iter : nodePtr->children) {
		printTree(iter.second, depth+1);
	}
}
