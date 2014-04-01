#ifndef SEAMCARVE_H
#define SEAMCARVE_H

#include <string>
#include <vector>

class SeamCarve {
	private:
		std::string filePath;
		std::vector<std::vector<int> > grid,
			weightedGrid,
			pathGrid;
		
		void weightGrid();
		void weightVertPath(std::vector<int> &);
		void weightHoriPath(std::vector<int> &);
		void moveUp(std::vector<std::vector<int> > &, int, int);


	public:
		SeamCarve(std::string);
		void resize(int, int);
		void removeVert();
		void removeHori();
		void printFile();
};

#endif
