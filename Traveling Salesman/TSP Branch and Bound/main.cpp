// Aaron Battershell

#include "tsp.hpp"
#include <iostream>

/*
/ Input is specified via the command line. This file expects
/ a single integer, the number of nodes wanted to run a test
/ on. 
*/

int main(int argc, char** args) {
	if (argc == 2) {
		tsp tspProblem(args[1]);
		tspProblem.printSolution();
	} else {
		std::cout << "Invalid input : integer argument expected" << std::endl;
	}
	
	return 0;
}
