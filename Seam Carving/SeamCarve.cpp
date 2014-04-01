#include "SeamCarve.h"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/*
/ Constructor(string)
/	This is the only constructor that should be used in this
/	program. It initializes all the necessary vectors and 
/	gives them appropriate values.
*/
SeamCarve::SeamCarve(std::string filePath) : filePath(filePath) {
	std::string lineInput;
	std::ifstream in;
	int width, depth, temp;

	in.open(filePath.c_str());
	if (!in.is_open()) {
		std::cerr << "File not found.\n";
		exit(1);
	}

	/* Parse input file */
	getline(in, lineInput);
	do {
		getline(in, lineInput);
	} while (lineInput[0] == '#');
	depth = atoi(lineInput.substr(0, lineInput.find(' ')).c_str());
	width = atoi(lineInput.substr(lineInput.find(' ', lineInput.size() - (lineInput.find(' ')+1))).c_str());
	in >> temp;

	/* Fill grid */
	for (int i = 0; i < width; ++i) {
		grid.push_back(std::vector<int>());
		weightedGrid.push_back(std::vector<int>());
		pathGrid.push_back(std::vector<int>());
		for (int n = 0; n < depth; ++n) {
			in >> temp;
			grid[i].push_back(temp);
			weightedGrid[i].push_back(-1);
			pathGrid[i].push_back(-1);
		}
	}

	weightGrid();
	in.close();
}

/*
/ resize(int, int)
/	Accepts two arguments, the number of vertical and horizonal
/	seams that are to be removed.
*/
void SeamCarve::resize(int removeVertCount, int removeHoriCount) {
	for (int i = 0; i < removeVertCount + removeHoriCount; ++i) {
		(i < removeVertCount ? removeVert() : removeHori());
	}

	printFile();
}

/*
/ removeVert()
/	Removes the lowest weighted vertical path in an image.
*/
void SeamCarve::removeVert() {
	std::vector<int> deletedPath;
	int y, x, minVal;

	/* Create weighted paths though the grid*/
	for (int n = 0; n < grid[0].size(); ++n) {
		pathGrid[0][n] = weightedGrid[0][n]; 
	}
	for (int i = 1; i < grid.size(); ++i) {
		for (int n = 0; n < grid[0].size(); ++n) {
			if (n-1 < 0) {
				pathGrid[i][n] = std::min(pathGrid[i-1][n], pathGrid[i-1][n+1]);
			} else if (n+1 > grid[0].size()-1) {
				pathGrid[i][n] = std::min(pathGrid[i-1][n-1], pathGrid[i-1][n]);
			} else {
				pathGrid[i][n] = std::min(pathGrid[i-1][n-1],std::min(pathGrid[i-1][n],pathGrid[i-1][n+1]));
			}
			pathGrid[i][n] += weightedGrid[i][n];
		}
	}

	/* Find the index of the min value in the last row */
	x = 0;
	minVal = pathGrid[grid.size()-1][0];
	for (int i = 1; i < grid[0].size(); ++i) {
		x = (minVal > pathGrid[grid.size()-1][i] ? i : x);
		minVal = pathGrid[grid.size()-1][x];
	}

	/* Find the index of the least expensive path ending */
	for (y = grid.size()-1 ; y > 0; --y) {
		int nextX;
		if (x-1 < 0) {
			nextX = (pathGrid[y-1][x] < pathGrid[y-1][x+1] ? x : x+1);
		} else if (x+1 > grid[0].size()-1) {
			nextX = (pathGrid[y-1][x-1] < pathGrid[y-1][x] ? x-1 : x);
		} else {
			nextX = (pathGrid[y-1][x-1] < pathGrid[y-1][x] ? x-1 : (pathGrid[y-1][x] < pathGrid[y-1][x+1] ? x : x+1));
		}

		grid[y].erase(grid[y].begin() + x);
		weightedGrid[y].erase(weightedGrid[y].begin() + x);
		pathGrid[y].pop_back();
		
		deletedPath.push_back(x);
		x = nextX;
	}

	grid[y].erase(grid[y].begin() + x);
	weightedGrid[y].erase(weightedGrid[y].begin() + x);
	pathGrid[y].pop_back();
	
	deletedPath.push_back(x);
	weightVertPath(deletedPath);
}

/*
/ removeHori()
/	Removes the lowest weighted horizontal path in an image.
*/
void SeamCarve::removeHori() {
	std::vector<int> deletedPath;
	int y, x, minVal;

	/* Create weighted paths though the grid*/
	for (int n = 0; n < grid.size(); ++n) {
		pathGrid[n][0] = weightedGrid[n][0];
	}
	for (int i = 1; i < grid[0].size(); ++i) {
		for (int n = 0; n < grid.size(); ++n) {
			if (n-1 < 0) {
				pathGrid[n][i] = std::min(pathGrid[n][i-1], pathGrid[n+1][i-1]);
			} else if (n+1 > grid.size()-1) {
				pathGrid[n][i] = std::min(pathGrid[n-1][i-1], pathGrid[n][i-1]);
			} else {
				pathGrid[n][i] = std::min(pathGrid[n-1][i-1],std::min(pathGrid[n][i-1],pathGrid[n+1][i-1]));
			}
			pathGrid[n][i] += weightedGrid[n][i];
		}
	}

	/* Find the index of the least expensive path ending */
	y = 0;
	minVal = pathGrid[0].back();
	for (int i = 1; i < grid.size(); ++i) {
		y = (minVal > pathGrid[i].back() ? i : y);
		minVal = pathGrid[y].back();
	}

	/* Traverse paths, erasing the path with the least energy */
	for (x = grid[0].size()-1; x > 0; --x) {
		int nextY;
		if (y-1 < 0) {
			nextY = (pathGrid[y][x-1] < pathGrid[y+1][x-1] ? y : y+1);
		} else if (y+1 > grid.size()-1) {
			nextY = (pathGrid[y-1][x-1] < pathGrid[y][x-1] ? y-1 : y);
		} else {
			nextY = (pathGrid[y-1][x-1] < pathGrid[y][x-1] ? y-1 : (pathGrid[y][x-1] < pathGrid[y+1][x-1] ? y : y+1));
		}

		moveUp(grid, y, x);
		moveUp(weightedGrid, y, x);

		deletedPath.push_back(y);
		y = nextY;
	}

	moveUp(grid, y, x);
	moveUp(weightedGrid, y, x);

	/* Delete the last row in the grid */
	grid.pop_back();
	weightedGrid.pop_back();
	pathGrid.pop_back();

	deletedPath.push_back(y);
	weightHoriPath(deletedPath);
}

/*
/ moveUp(vector<vector<int>>, int, int)
/	Given a 2D grid plus an x y coordinate, this function shifts all
/	the elements underneath the provided x y coordinate up one. This
/	causes the x y to be overwritten and the last element to be 
/	duplicated. This is a helper function for SeamCarve::removeHori(). 
*/
void SeamCarve::moveUp(std::vector<std::vector<int> > &matrix, int y, int x) {
	for ( ; y < matrix.size()-1; ++y) {
		matrix[y][x] = matrix[y+1][x];
	}
}

/*
/ printFile()
/	Prints the contents of the 2D vector, 'grid', to the file location
/	specified at object creation. 
*/
void SeamCarve::printFile() {
	std::ofstream out;
	out.open(filePath.substr(0, filePath.size()-4).append("_processed.pgm").c_str());

	/* Print file header */
	out << "P2 \n#Image edited with seam carving \n" << grid[0].size() << ' ' 
		<< grid.size() << " \n255 \n";

	/* Print contents of grid to the file */
	for (int i = 0; i < grid.size(); ++i) {
		for (int n = 0; n < grid[i].size(); ++n) {
			out << grid[i][n] << ' ';
		}
		out << std::endl;
	}

	out.close();
}

/*
/ weightedGrid()
/	Weights all elements in a 2D array based on the contents of its
/	surroundings. Values are taken from 'grid', what holds the 
/	gray-scale image values, and results are stored in 'weighedGrid'.
*/
void SeamCarve::weightGrid() {
	for (int i = 0; i < weightedGrid.size(); ++i) {
		for (int n = 0; n < weightedGrid[0].size(); ++n) {
			weightedGrid[i][n] = std::abs((grid[i][n] - (i-1 >= 0 ? grid[i-1][n] : grid[i][n])))
					+ std::abs((grid[i][n] - (n-1 >= 0 ? grid[i][n-1] : grid[i][n])))	
					+ std::abs((grid[i][n] - (i+1 <= grid.size()-1    ? grid[i+1][n] : grid[i][n])))
					+ std::abs((grid[i][n] - (n+1 <= grid[0].size()-1 ? grid[i][n+1] : grid[i][n])));				 
		}
	}
}

/*
/ weightVertPath()
/	Similar to weightedGrid, this function calculates the weight of 
/	a cell given its surroundings. However, this only recalculates
/	the values in the vector provided. An 0(n) calculation. 
*/
void SeamCarve::weightVertPath(std::vector<int> &path) {
	for (int i = path.size()-1; i >= 0; --i) {
		for (int n = path[(path.size()-1)-i]-1; n < path[(path.size()-1)-i]+2 ; ++n) {
			if (n >= 0 && n < grid[0].size()) {
				weightedGrid[i][n] = std::abs((grid[i][n] - (i-1 >= 0 ? grid[i-1][n] : grid[i][n])))
						+ std::abs((grid[i][n] - (n-1 >= 0 ? grid[i][n-1] : grid[i][n])))	
						+ std::abs((grid[i][n] - (i+1 <= grid.size()-1    ? grid[i+1][n] : grid[i][n])))
						+ std::abs((grid[i][n] - (n+1 <= grid[0].size()-1 ? grid[i][n+1] : grid[i][n])));
			}
		}
	}
}

/*
/ weightHoriPath()
/	Similar to weightedGrid, this function calculates the weight of 
/	a cell given its surroundings. However, this only recalculates
/	the values in the vector provided. An 0(m) calculation. 
*/
void SeamCarve::weightHoriPath(std::vector<int> &path) {
	for (int i = path.size()-1; i >= 0; --i) {
		for (int n = path[(path.size()-1)-i]-1; n < path[(path.size()-1)-i]+2 ; ++n) {
			if (n >= 0 && n < grid.size()) {
				weightedGrid[n][i] = std::abs((grid[n][i] - (n-1 >= 0 ? grid[n-1][i] : grid[n][i])))
						+ std::abs((grid[n][i] - (i-1 >= 0 ? grid[n][i-1] : grid[n][i])))
						+ std::abs((grid[n][i] - (n+1 <= grid.size()-1    ? grid[n+1][i] : grid[n][i])))
						+ std::abs((grid[n][i] - (i+1 <= grid[0].size()-1 ? grid[n][i+1] : grid[n][i])));
			}
		}
	}
}
