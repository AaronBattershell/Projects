#include "SeamCarve.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char **argl) {
	if (argc != 4) {
	 std::cout << "Invalid input!" << std::endl;
	} else {
	 SeamCarve(argl[1]).resize(atoi(argl[2]), atoi(argl[3]));
	}

	return 0;
}
