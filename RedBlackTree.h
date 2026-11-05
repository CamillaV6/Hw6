#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <iostream>
#include <vector>
#include <string>



using namespace std;

#define COLOR_RED 0
#define COLOR_BLACK 1

struct RBTNode {
	int data;
	unsigned short int color;
	RBTNode *left = nullptr;
	RBTNode *right = nullptr;
	RBTNode *parent = nullptr;
	
};

class RedBlackTree{
	public:
	
		RedBlackTree();
		RedBlackTree(int num);
		RedBlackTree(const RedBlackTree& tree);
		void Insert(int num);
		bool Contains(int num);
		int min();
		int max();
		int size();
		
		string ToInfixString() const {return ToInfixString(root);};
		string ToPrefixString() const { return ToPrefixString(root);};
		string ToPostfixString() const { return ToPostfixString(root);};
		
	private:
		unsigned long long int numItems = 0;
		RBTNode *root = nullptr;
		
		string ToInfixString(const RBTNode *n) const;
		string ToPrefixString(const RBTNode *n)const;
		string ToPostfixString(const RBTNode *n)const;
		
		//insertfix and related functions in private to not be called on randomly
		void insertfix(RBTNode* node);
		void rotateRight(RBTNode* x);
		void rotateLeft(RBTNode* x);
	
	
};

#endif
