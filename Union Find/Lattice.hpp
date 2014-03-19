#ifndef LATTICE_HPP
#define LATTICE_HPP

#include <map>
#include <string>

class Lattice {
	private:
		struct set {
			set();
			set(int, int);
			bool operator < (const set&) const;
			bool operator != (const set&) const;
			int x, y;
		};

		int dim, **lattice;
		double openProb;
		std::map<set, set> path;

		set getRoot(const set&);
		void colorGrid();


	public:
		Lattice(double, int, const int);
		Lattice(std::string);
		~Lattice();
		void print();
		bool unionFind();
		int clusters();
};

#endif
