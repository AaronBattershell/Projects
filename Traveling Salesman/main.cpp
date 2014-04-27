#include "result.hpp"
#include "tsp.hpp"
#include <iostream>
using namespace std;

int main(int argc, char** args) {
	//tsp tspProblem("sample1.txt");
	//tsp tspProblem("map_15_01.txt");
	//tsp tspProblem("map_6_01.txt");
	tsp tspProblem("map_7_01.txt");

	
	/*
	node *temp1 = new node(); temp1->id = 1; temp1->lowerBound = 8;
	node *temp2 = new node(); temp2->id = 2; temp2->lowerBound = 7;
	node *temp3 = new node(); temp3->id = 3; temp3->lowerBound = 7;
	node *temp4 = new node(); temp4->id = 4; temp4->lowerBound = 6;
	node *temp5 = new node(); temp5->id = 5; temp5->lowerBound = 2;
	node *temp6 = new node(); temp6->id = 6; temp6->lowerBound = 5;
	node *temp7 = new node(); temp7->id = 7; temp7->lowerBound = 14;
	node *temp8 = new node(); temp8->id = 8; temp8->lowerBound = 1;
	node *temp9 = new node(); temp9->id = 9; temp9->lowerBound = 13;
	node *temp10 = new node(); temp10->id = 10; temp10->lowerBound = 14;
	node *temp11 = new node(); temp11->id = 11; temp11->lowerBound = 12;
	node *temp12 = new node(); temp12->id = 12; temp12->lowerBound = 13;
	tspProblem.head = temp5;

	// right branch  
	temp11->children[temp12->id] = temp12; 
	temp9->children[temp10->id] = temp10; 
	temp7->children[temp8->id] = temp8;
	
	temp6->children[temp11->id] = temp11; 
	temp6->children[temp9->id] = temp9; 
	temp6->children[temp7->id] = temp7; 

	// left branch
	temp2->children[temp1->id] = temp1;
	temp4->children[temp2->id] = temp2;
	temp4->children[temp3->id] = temp3;

	// center branch
	temp5->children[temp6->id] = temp6;
	temp5->children[temp4->id] = temp4;
	*/
	// ___________________________________________________________________________________________________//
	// Print tree structure
	/*
	tspProblem.bestLowerBound = tspProblem.getLowestBoundedNode(tspProblem.head)->lowerBound;
	tspProblem.endPtr = tspProblem.getLowestBoundedNode(tspProblem.head);

	cout << "Lowest bound: " << tspProblem.getLowestBoundedNode(tspProblem.head)->id << endl;
	*/
	/*
	tspProblem.printTree(tspProblem.head);
	tspProblem.pruneBranches(tspProblem.head);
	tspProblem.printTree(tspProblem.head);
	tspProblem.pruneBranches(tspProblem.head);
	tspProblem.printTree(tspProblem.head);
	tspProblem.pruneBranches(tspProblem.head);
	tspProblem.printTree(tspProblem.head);
	tspProblem.pruneBranches(tspProblem.head);
	tspProblem.printTree(tspProblem.head); 
	*/

	/*
	cout << "Node 1 : " << tspProblem.getLowestBoundedNode(temp1)->lowerBound << ' ' << tspProblem.getLowestBoundedNode(temp1)->id << endl;
	cout << "Node 2 : " << tspProblem.getLowestBoundedNode(temp2)->lowerBound << ' ' << tspProblem.getLowestBoundedNode(temp2)->id << endl;
	cout << "Node 3 : " << tspProblem.getLowestBoundedNode(temp3)->lowerBound << ' ' << tspProblem.getLowestBoundedNode(temp3)->id << endl;
	cout << "Node 4 : " << tspProblem.getLowestBoundedNode(temp4)->lowerBound << ' ' << tspProblem.getLowestBoundedNode(temp4)->id << endl;
	cout << "Node 5 : " << tspProblem.getLowestBoundedNode(temp5)->lowerBound << ' ' << tspProblem.getLowestBoundedNode(temp5)->id << endl;
	cout << "Node 6 : " << tspProblem.getLowestBoundedNode(temp6)->lowerBound << ' ' << tspProblem.getLowestBoundedNode(temp6)->id << endl;
	cout << "Node 7 : " << tspProblem.getLowestBoundedNode(temp7)->lowerBound << ' ' << tspProblem.getLowestBoundedNode(temp7)->id << endl;
	cout << "Node 8 : " << tspProblem.getLowestBoundedNode(temp8)->lowerBound << ' ' << tspProblem.getLowestBoundedNode(temp8)->id << endl;
	cout << "Node 9 : " << tspProblem.getLowestBoundedNode(temp9)->lowerBound << ' ' << tspProblem.getLowestBoundedNode(temp9)->id << endl;
	cout << "Node 10: " << tspProblem.getLowestBoundedNode(temp10)->lowerBound << ' ' << tspProblem.getLowestBoundedNode(temp10)->id << endl;
	cout << "Node 11: " << tspProblem.getLowestBoundedNode(temp11)->lowerBound << ' ' << tspProblem.getLowestBoundedNode(temp11)->id << endl;
	cout << "Node 12: " << tspProblem.getLowestBoundedNode(temp12)->lowerBound << ' ' << tspProblem.getLowestBoundedNode(temp12)->id << endl << endl;
	cout << "Node HEAD: " << tspProblem.getLowestBoundedNode(tspProblem.head)->lowerBound << ' ' << tspProblem.getLowestBoundedNode(tspProblem.head)->id << endl;
	*/ 



	result *answer = tspProblem.shortestPath();
	// Print result of returned value
	cout << "Shortest traversal sum: " << answer->pathSum << "\n\tNode order : ";
	for (auto &i : answer->shortestPath) 
		cout << i << ' ';

	return 0;
}