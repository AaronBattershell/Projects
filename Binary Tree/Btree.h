#ifndef BTREE_H
#define	BTREE_H

class Btree
{
	private:
		struct node {
			node(int x = -1);
			int value;
			node* left;
			node* right;
		};

		node* root;
	
	public:
		Btree();
		~Btree();
        
		node* getRoot();
        node* detachMinNode(node*, node*);
        
		bool search(int, node*);
		bool remove(int, node*, node* = 0);
		bool isBalanced(node*);
        
		int depthOfNode(int, node*);
		int minDepth(node*);
		int maxDepth(node*);
		int highestCostPath(node*);
        
		void insert(int, node*);
		void deleteTree(node*);
		void print(node*);
        void userCLI();
};

#endif	/* BTREE_H */