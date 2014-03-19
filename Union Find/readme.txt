The following is a high-level overview of Aaron Battershell's Union-Find implementation.

General:
        • This program was written using c++ and has compiles successfully using g++ version 4.8.1 and 
	in Visual Studios 2012.

        • Input is expected via command line arguments. Once input has been entered, the
	program will produce the appropriate output and then terminate. There are two forms of input 
        that can be handle.
		1) Input: double p, int n, int s where: 
			probability of open cell: 0 < p <= 1
			number of runs: 1 < n < 100000
			size of lattice: 1 < n < 3000
		    Output: The (0 < percentage < 100) of times that the lattice can successfully be 
			traversed given user specifications. A successful traversal is defined as a
                        contiguous grouping of open cells from the top most to the lowest most cells in 
        		a lattice.  
		2) Input: string file_location.txt
			contains an s x s matrix of '1's and '0's. Every character is followed by a 	
                        space, every s characters is followed by a space and '\n'.
		   Output: The number of isolated contiguous open cells contained in the specified 
			lattice. 

        • For both input cases, a file named “results.ppm” will be generated and stored in the
        working directory that will contain an image of the either 1) the lattice specified by file
        location, or a lattice that has been randomly generated with respect to the user input 	  
        specifications.

Low level class explanation:
        • The Lattice class creates and stores its lattice data in a dynamically allocated 2D int 
        array. This graph is traversed, and connections are found by looking to each open cells right 
        and downward cells. If those neighboring cells are open, a connection is made by editing the
        std::map<set,set>'path' map. This path map takes as a key any given open cell. Its value is 	
        returns the 'root' of a contiguous area of cells. A cell is considered a root cell if, when 
        entered into the path map, produces itself: ie (path[set(x, y)] == set(x, y)). If a contiguous 
        group of cells need to be joined, the root of one group is set to equal the root of the other. 
        Therefore, all nodes point to nodes that will eventually lead to an ultimate root node for that 
        given contiguous group of nodes.
	
