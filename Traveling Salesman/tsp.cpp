#include "tsp.hpp"
#include <iostream>
using namespace std;

/*
/ constructor
/	
*/
tsp::tsp(std::string filePath) : bestLowerBound(0), head(new node) {
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

tsp::~tsp() {
	deleteTree(head);
}

result* tsp::shortestPath() {
	 do {
		node *nodePtr = getLowestBoundedNode(head);
		//printTree(head);
		while (!noPossibleChildren(nodePtr)) {
			calcChildrenBounds(nodePtr); // work on this function - what fully makes children nodes children nodes
			//cout << "From: " << nodePtr->id;
			nodePtr = getLowestBoundedNode(nodePtr);
			//cout << "  To: " << nodePtr->id << endl;
			//printGrid(nodePtr);
			//printTree(head);
		}
		node *bestNode = getLowestBoundedEndNode(head);
		endPtr = bestNode;
		bestLowerBound = bestNode->lowerBound;

		pruneBranches(head);
		//cout << "Pruning Branches" << endl;
		static int i = 0;
		if (i % 1000 == 0 ) {
			printTree(head);
			char temp;
			cout << "Enter a character to continue: ";
			cin >> temp;
		}
		++i;
	} while (!isLinkedList(head));

	//assign result new values
	result *finalResult = new result();

	node *tmpPtr = head;
	while (true) {
		finalResult->shortestPath.push_back(tmpPtr->id);
		if (isLeafNode(tmpPtr)) {
			break;
		}
		tmpPtr = tmpPtr->children.begin()->second;
	}
	finalResult->pathSum = bestLowerBound;

	return finalResult;
}

void tsp::calcChildrenBounds (node *nodePtr) {
	// Assign children to the current node
	//cout << "Parent's lower bound: " <<  nodePtr->lowerBound << endl;
	addChildren(nodePtr);

	// Assign
	for (auto &iter : nodePtr->children) {	
		calcLowerBound(iter.second, nodePtr->id, iter.second->id); //cNode, pId, cId 
	}
}

void tsp::calcLowerBound(node *curNode, int from, int to) { // x: from, y: to
	int lowBound = 0,
		minElement = 0;
	if (from != -1 && to != -1) {
		if (curNode->grid[from][to] == inf) {
			std::cout << "ERROR: ADDING INFINITY" << std::endl;
			exit(0);
		}

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
	//cout << "Node " << curNode->id << ": " << curNode->lowerBound << endl;
}

void tsp::addChildren(node *nodePtr) {
	for (auto &iter : nodePtr->conn) {
		nodePtr->children[iter] = new node(iter, nodePtr->lowerBound, nodePtr->conn, nodePtr->grid); // where the magic happens
	}
}

// Change to check for at least two valid children
bool tsp::isLinkedList(node *nodePtr) {
	return (nodePtr->children.size() == 0 ? true : (nodePtr->children.size() != 1) ? false : isLinkedList(nodePtr->children.begin()->second));
}

node* tsp::getLowestBoundedNode(node *nodePtr) {

	// Case: leaf node reached
	if (isLeafNode(nodePtr)) {
		return nodePtr;
	}

	// Creat your iterator for traversing through your children map
	std::map<int,node*>::iterator iter = nodePtr->children.begin();
	
	// Initilize a variable that will hold the node that holds the lowest bound
	node *minNode = getLowestBoundedNode(iter->second);
	
	// Iterate through all children, getting the one with the lowest bound
	for (++iter; iter != nodePtr->children.end(); ++iter) {
		node *tempResult = getLowestBoundedNode(iter->second);
		if (minNode->lowerBound > tempResult->lowerBound) {
			minNode = tempResult;
		}
	}

	return minNode;
}

node* tsp::getLowestBoundedEndNode(node *nodePtr) {

	// Case: leaf node reached
	if (isLeafNode(nodePtr)) {
		return (nodePtr->conn.empty() ? nodePtr : NULL);
	}

	// Creat your iterator for traversing through your children map
	std::map<int,node*>::iterator iter = nodePtr->children.begin();
	
	// Initilize a variable that will hold the node that holds the lowest bound
	node *minNode = getLowestBoundedEndNode(iter->second);
	
	// Iterate through all children, getting the one with the lowest bound
	for (++iter; iter != nodePtr->children.end(); ++iter) {
		node *tempResult = getLowestBoundedEndNode(iter->second);
		if ((minNode == NULL ? ndef : minNode->lowerBound) > (tempResult == NULL ? ndef : tempResult->lowerBound)) {
			minNode = tempResult;
		}
	}

	return minNode;
}

bool tsp::isLeafNode(node *nodePtr) {
	return nodePtr->children.size() == 0;
}

bool tsp::noPossibleChildren(node *nodePtr) {
	return nodePtr->conn.size() == 0;
}

// 
void tsp::pruneBranches(node *nodePtr) {
	vector<int> toDelete(nodePtr->children.size()/2);
	for (auto &iter : nodePtr->children) {
		if (iter.second->lowerBound >= bestLowerBound && iter.second != endPtr && isLeafNode(iter.second)) { // If to high and not last node
			toDelete.push_back(iter.second->id);
			//nodePtr->children.erase(iter.second->id);
			deleteTree(iter.second);
			continue;
		}
		pruneBranches(iter.second);
	}

	for (auto &iter : toDelete) {
		nodePtr->children.erase(iter);
	}
}

// 
void tsp::deleteTree(node *nodePtr) { // Curently being worked on
	for (auto &iter : nodePtr->children) {
		deleteTree(iter.second);
	}

	delete nodePtr;
	nodePtr = NULL;
}

void tsp::printGrid(node *nodePtr) {
	for (int i = 0; i < nodes; ++i) {
		for (int n = 0; n < nodes; ++n) {
			std::cout << std::setw(3) << nodePtr->grid[i][n] << ' ';
		}
		std::cout << std::endl;
	}
	cout << endl;
}

void tsp::printTree(node *nodePtr, int depth) {
	for (int i = 0; i < depth; ++i) {
		cout << "  ";
	}

	cout << nodePtr->id << endl;

	for (auto &iter : nodePtr->children) {
		printTree(iter.second, depth+1);
	}
}
