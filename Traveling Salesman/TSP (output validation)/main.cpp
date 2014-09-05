// Aaron Battershell

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
/ The purpose of this file is to test the branch and bounds 
/ output. This complexity of this is O(n!), and therefore has
/ an upper limit of ~11 nodes to a data set that should be
/ tested against it.
/
/ Input is specified via the command line. This file expects
/ a single integer, the number of nodes wanted to run a test
/ on. 
*/

int main(int argc, char** argl) {
	if (argc != 2) {
		cout << "Invalid Input : integer argument expected" << endl;
		exit(1);
	}

	
	vector<vector<int > > grid;
	vector<int> nodes, optimalPath;
	int dim, minPathCost = 100000000;

	/* Open the file specified by the user */
	fstream in (("../maps/map_" + static_cast<string>(argl[1]) + ".txt").c_str(), fstream::in);
	if (!in.is_open()) {
		cout << "File not found!" << endl;
		exit(2);
	}

	/* Read data from file */
	in >> dim;
	for (int i = 0; i < dim; ++i) {
		nodes.push_back(i);
		optimalPath.push_back(0);
		grid.push_back(vector<int>());
		for (int n = 0; n < dim; ++n) {
			int temp;
			in >> temp;
			grid[i].push_back(temp);
		}
	}

	/* Get all permutations of input, selecting the one */
	/* that yields the greatest value */
	do { 	
		int tempSum = 0;
		int lastNode = 0;
		for (int i = 1; i < dim; ++i) {
			tempSum += grid[lastNode][nodes[i]];
			lastNode = nodes[i];
		}
		tempSum += grid[lastNode][0];

		/* A new low bound has been found */
		if (tempSum < minPathCost) { 
			minPathCost = tempSum;
			for (int i = 0; i < dim; ++i) {
				optimalPath[i] = nodes[i];
			}
		}
		minPathCost = min(minPathCost, tempSum);
	} while(next_permutation(nodes.begin()+1, nodes.end())) ;


	/* Print final results */
	cout << "Method : Exhaustive Search\nShortest traversal sum: " 
		 << minPathCost << "\n\tNode Order : ";
	for (auto &iter : optimalPath) {
		cout << iter << ' ';
	}
	cout << "0 " << endl;

	return 0;
}
