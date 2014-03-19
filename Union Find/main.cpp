//*******************************************
// Aaron Battershell 3/05/14
// Algorithms 001 : Dr Duan
// Union-Find algorithm
//*******************************************

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Lattice.hpp"

int main(int argc, char **args) {
	double p;
	int n, s, traversable = 0;

	/* Seed random which all object's srand()s are bassed off of */
	srand(time(0));
	

	if (argc == 4) {
		p = atof(args[1]);
		n = atoi(args[2]);
		s = atoi(args[3]);
		
		for (int i = 0; i < n; ++i) {
			Lattice testLattice(p, s, rand());
			if (testLattice.unionFind()) {
				++traversable;
			}
			if (!i) { /* Print to results.ppm a lattice for viewing purposes with user specified specs */
				testLattice.print();
			}
		}
		std::cout << "Traversable: " << (traversable == n ? 100 : traversable / static_cast<double>(n)) << "% of the time.\t";

	} else if (argc == 2) {
		std::string filePath = args[1];
		Lattice inputLattice(filePath);
		inputLattice.unionFind();
		inputLattice.print();
		std::cout << "There are: " << inputLattice.clusters() << " clusters." << std::endl;

	} else {
		std::cout << "Wrong input format!" << std::endl;
	}

	return 0;
}
