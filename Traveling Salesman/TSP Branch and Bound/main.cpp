// Aaron Battershell

#include "tsp.hpp"
#include <iostream>

int main(int argc, char** args) {
	if (argc == 2) {
		tsp tspProblem(args[1]);
		tspProblem.printSolution();
	} else {
		std::cout << "Invalid input : string argument expected" << std::endl;
	}
	
	return 0;
}
