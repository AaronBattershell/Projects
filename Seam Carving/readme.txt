The following is a high-level overview of Aaron Battershell's Seam
 Carving implementation.

General:
        • This program was written using c++ and has compiles 
	successfully using g++ version 4.8.1 and in Visual Studios
	2012.

        • Input is expected through command line arguments. Valid
	form of input:
		1) string int int

		   More specifically:   [Name_of_file.pgm] 
			       		[vertical seams to remove]
			       		[horizontal seams to remove]

	• Output: A file named [FileName]_processed.pgm will be 
	created	with the specified number of vertical and 
	horizontal seams removed and placed in the working directory.
	  If an invalid number of arguments are entered the program
	will output "Invalid format!" If the file name entered
	cannot be found in the working directory, the program will
	output "File not found."

High level code explanation:
	• The SeamCarve class uses three nxm grids. One holds the
	gray-scale rbg values. The second holds the weight of each
	gray-scale cell based on its surroundings. The third holds
	the weighted path values generated through a dynamic
	seam carving algorithm. Here, more memory is used to allow
	for a faster algorithm as the second and third grids could
	be combined, but at the cost of recalculating all the
	weighted cell values held in the second grid. 
