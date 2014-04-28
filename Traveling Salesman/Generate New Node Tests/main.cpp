// Aaron Battershell

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <cstdlib>
using namespace std;

/*
/  The purpose of this file is to generate new nxn grids
/  to test my travelling salesman implementation against.
/  
/  Use of this is completely optional, and is there only
/  if you want a new dataset to work from.
/
/  By default this program will create files named map_##.txt
/  and store them in the working directory. From there 
/  those files can be taken and copied into the working
/  directories of both travelling salesmen implementations.
*/

int main() {
	srand(time(0));

	for (int i = 2; i <= 35; ++i) {
		fstream out ("map_"+to_string(i)+".txt", fstream::out);

		out << i << endl;
		for (int n = 0; n < i;  ++n) {
			for (int j = 0; j < i; ++j) {
				out << setw(4) << (n == j ? -1 : rand() % 100) << ' ';
			}
			out << endl;
		}
		out.close();
	}

	cout << "New files have been created and stored in the working directory." << endl;
	return 0;
}
