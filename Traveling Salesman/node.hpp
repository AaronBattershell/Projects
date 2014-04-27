#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
#include <map>

class node {
	public:
		int id,
			lowerBound;
		std::vector<int> conn;
		std::vector<std::vector<int> > grid;
		std::map<int, node*> children;
		
		node() 
			: id(0), lowerBound(0) { }

		node(int nodes, std::vector<std::vector<int> > &newGrid)
			: id(nodes), lowerBound(0), grid(newGrid) { }

		node(int id, int lowerBound, std::vector<int> &conn, std::vector<std::vector<int> > &parentGrid) 
			: id(id), lowerBound(lowerBound), conn(conn), grid(parentGrid) { 
			for (int i = 0; i < this->conn.size(); ++i) {
				if (conn[i] == id) {
					this->conn.erase(this->conn.begin() + i);
					break;
				}
			}
		} 
				

};

#endif