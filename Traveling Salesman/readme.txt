Problem: Travelling salesman problem implemented with branch and bound
	 giving the best lowest cost path traversal.
Required: C++11 build capability.

Notes:
	Directory: TSP Branch and Bound 
		* The directory where the program I am formally submitting
		is stored. In it is also a series of randomly generated 
		test cases that can be used.
	Directory: TSP (output validation)
		* This contains a single .cpp file that is meant to 
		verify output of the branch and bound method. The
		solutions here are guaranteed to be correct, as an
		exhaustive search is used to calculate the lowest 
		cost path. Inside here are also test files that match
		those in the "TSP Branch and Bound Directory."
	Directory: Generate New Node Tests
		* Generates new test files. If this option is used, after
		running the program, new files will be created. These
		new files can be copied into both TSP directories
		replacing their contents with newly randomized test data.

General:
	* If you are compiling in Linux, you will need to build the files 
	using the "-std=c++0x" flag. Also, if compiling in Linux, use the
	 "-O3" optimization flag to allow for faster run times.
