#include "Btree.h"
#include <iostream>
using namespace std;

//***************************************
// node(int)
//***************************************
Btree::node::node(int x) {
	value = x;
	left = right = NULL;
};

//*************************************** 
// Btree()
//***************************************
Btree::Btree() {
	root = NULL;
}

//***************************************
// ~Btree()
//***************************************
Btree::~Btree() {
	deleteTree(root);
}

//*************************************** 
// getRoot
//***************************************
Btree::node* Btree::getRoot() {
	return root;
}

//***************************************
// Deletes all decendents of a given node
//***************************************
void Btree::deleteTree(node* nodePtr) {
	if(nodePtr && nodePtr->left)
		deleteTree(nodePtr->left);
	if(nodePtr && nodePtr->right)
		deleteTree(nodePtr->right);
	
	delete nodePtr;
}

//***************************************
// Return true if an element exists in the data set
//***************************************
bool Btree::search(int key, node* nodePtr) {
	if(nodePtr && nodePtr->value == key)
		return true;
	else if(nodePtr && nodePtr->left && nodePtr->value > key)
		return search(key, nodePtr->left);
	else if(nodePtr && nodePtr->right && nodePtr->value < key)
		return search(key, nodePtr->right);
    else
        return false;
}

//***************************************
// Insert an element in sorted order
//***************************************
void Btree::insert(int key, node* nodePtr) {
	if(!root)
		root = new node(key);

	else if(nodePtr->value >= key) {
		if(!nodePtr->left) 
			nodePtr->left = new node(key);
		else
			insert(key, nodePtr->left);
	}
	else if(nodePtr->value < key) {
		if(!nodePtr->right)
			nodePtr->right = new node(key);
		else
			insert(key, nodePtr->right);
	}
}

//***************************************
// Remove a node based on a key of type int
// Returns false if element not in data set
//***************************************
bool Btree::remove(int key, node* nodePtr, node* tailPtr) {
	/*Case: No nodes*/
	if(!root)
		return false;

	/*Case: key [less || greater] than current node value*/
    else if(nodePtr->value > key) 
		return (nodePtr->left ? remove(key, nodePtr->left, nodePtr) : false);
	else if(nodePtr->value < key)
		return (nodePtr->right ? remove(key, nodePtr->right, nodePtr) : false);
    
	/*Case: Node located*/
	else if(nodePtr->value == key) {

        /*Case: 2 Children*/
		if(nodePtr->left && nodePtr->right) {
			node* minNode = detachMinNode(nodePtr->right, nodePtr);
			minNode->left = nodePtr->left;
			minNode->right = nodePtr->right;
			if(nodePtr == root)
				root = minNode;
			else
				(tailPtr->left->value == key ? tailPtr->left : tailPtr->right) = minNode;
		}

        /*Case: 1 Child*/
		else if(nodePtr->left || nodePtr->right) { 
			if(nodePtr == root)
				root = (nodePtr->left ? nodePtr->left : nodePtr->right);
			else {
				if(tailPtr->left && tailPtr->left->value == key)
					tailPtr->left = (tailPtr->left->left ? nodePtr->left : nodePtr->right);
				else
					tailPtr->right = (tailPtr->right->left ? nodePtr->left : nodePtr->right);
			}
		}

        /*Case: 0 Children*/
		else { 
			if(nodePtr == root)
				root = NULL;
			else
				(tailPtr->left == nodePtr ? tailPtr->left : tailPtr->right) = NULL;
        }

		delete nodePtr;
		nodePtr = NULL;
		return true;
	}
}

//*************************************** 
// Removes and returns the minimum node of a right subtree passed to it
//***************************************
Btree::node* Btree::detachMinNode(node* nodePtr, node* tailPtr) {
	/*Case: No left node of nodePtr on first itteration*/
	if(tailPtr->right == nodePtr && !nodePtr->left) {
		tailPtr->right = NULL;
		return nodePtr;
	}	
	/*Case: Smallest node*/
	else if(!nodePtr->left) {
		tailPtr->left = nodePtr->right;
		return  nodePtr;
	}
	/*Case: Smaller values exist*/
	else
		return detachMinNode(nodePtr->left, nodePtr);
}

//***************************************
// Print existing data by in-order traveral
//***************************************
void Btree::print(node* nodePtr) {    
	if(!nodePtr) 
		return;

	if(nodePtr->right) 
		print(nodePtr->right);
	cout << nodePtr->value << ' ';
	if(nodePtr->left)  
		print(nodePtr->left);
}

//***************************************
// Returns depth of first occurence of a value
//***************************************
int Btree::depthOfNode(int key, node* nodePtr) {    
	if(!nodePtr || ((key < nodePtr->value && !nodePtr->left) || (key > nodePtr->value && !nodePtr->right)))
		return -1;
	else
		return(nodePtr->value == key ? 0 : (nodePtr->value > key ? depthOfNode(key, nodePtr->left):depthOfNode(key, nodePtr->right)) +1);
}

//***************************************
// Returns longest path to a null value reference
//***************************************
int Btree::maxDepth(node* nodePtr) {    
	return(!nodePtr ? -1 : max(maxDepth(nodePtr->left), maxDepth(nodePtr->right)) +1); 
}

//*************************************** 
// Returns shortest path to a null value reference
//***************************************
int Btree::minDepth(node* nodePtr) {
	return (!nodePtr ? -1 : min(minDepth(nodePtr->left), minDepth(nodePtr->right)) +1);
}

//***************************************
// Returns the highest cost path traveral
//***************************************
int Btree::highestCostPath(node* nodePtr) {
	if (!nodePtr)
		return 0;

	return (!nodePtr->left && !nodePtr->right ? nodePtr->value : max(highestCostPath(nodePtr->left), highestCostPath(nodePtr->right)) + nodePtr->value);
}

//***************************************
// Return false if the tree is not ballanced
//***************************************
bool Btree::isBalanced(node* nodePtr) {
	return (maxDepth(nodePtr) - minDepth(nodePtr) < 2 && nodePtr ? true : false);
}

//***************************************
// User command line interface
//***************************************
void Btree::userCLI() {
	bool end = false;
	char userChoice;
	int userInput;

	cout << "*************************************\n"
             << "Operation Options:\n"
             << "1. Insert a value\n" 
             << "2. Remove a value\n"
             << "3. Search for a value\n"
 		     << "4. Print existing values\n"
             << "5. Print the depth of a given value\n"  
             << "6. Determine if the tree is balanced\n"
             << "7. Find the highest cost path\n"
             << "8. Exit\n\n";

        cout << "Enter your operation option: ";
        cin >> userChoice;

	switch(userChoice) {
		case '1':
			cout << "Number to add: ";
			cin >> userInput;
			insert(userInput, root);
			cout << "\nElement inserted successfully\n\n";
			break;

		case '2':	
			cout << "Number to remove: ";
			cin >> userInput;
			cout << (remove(userInput, root) ? "\nElement removed successfully" : "\nThis element does not exist in the data set") << "\n\n";
			break;

		case '3':
			cout << "Number to search for: ";
			cin >> userInput;
			cout << "\nThis element " << (search(userInput, root) ? "does" : "does not") << " exist in the data set\n\n";
			break;

		case '4':
			cout << "\nExisting values: "; print(root); cout << "\n\n";
			break;

		case '5':
			cout << "Number to search for: ";
			cin >> userInput;
			if(depthOfNode(userInput, root) != -1)
				cout << "\nDepth of value " << userInput << ": " << depthOfNode(userInput, root) << "\n\n";	
			else
				cout << "\nNo such value exists in the data set\n\n";
			break;

		case '6':	
			cout << "\nThis tree " << (isBalanced(root) ? "is" : "is not") << " balanced\n\n";
			break;

		case '7':
			cout << "\nHighest cost path: " << highestCostPath(root) << "\n\n";
			break;

		case '8':
			end = true;
			break;

		default :
			cout << "\nInvalid Selection\n\n";
	}

	if(!end)
		userCLI();
}