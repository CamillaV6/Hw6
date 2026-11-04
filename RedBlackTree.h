#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define COLOR_RED = 0;
#define COLOR_BLACK = 1;

struct RBTNode {
	int data;
	unsigned short int color;
	RBTNode *left = nullptr;
	RBTNode *right = nullptr;
	
}

class RedBlackTree{
	public:
	
		
	
		void insert(int num);
		bool contains(int num);
		int min();
		int max();
		int size();
		
		string ToInfixString() const {return ToInfixString(root);};
		string ToPrefixString() const { return ToPrefixString(root);};
		string ToPostfixString() const { return ToPostfixString(root);};
		
	private:
		unsigned long long int numItems = 0;
		RBTNode *root = nullptr;
		
		string ToInfixString(RBTNode *n);
		string ToPrefixString(RBTNode *n);
		string ToPostfixString(RBTNode *n);
	
	
}
