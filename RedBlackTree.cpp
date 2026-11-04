#include "RedBlackTree.h"

RedBlackTree() {
	*root = nullptr;
	numItems = 0;
}

/*
void insert(int num) {
	
}

bool conatins(int num) {
	
	return false;
}

int min() {
	
	return 0;
}

int max() {
	
	return 0;
}

int size() {
	
	return 0;
}

*/

string ToInfixString(RBTNode *n) {
	string infix = "";
	if (*n == nullptr) {
		return "";
	}
	
	infix = ToInfixString(n->left);
	
	infix = infix + " " + toString(n->color) + toString(n->data) + " ";
	
	infix = infix + ToInfixString(n->right);

	return infix;
}



string ToPrefixString(RBTNode *n) {
	string prefix = "";
	if (n == nullptr) {
		return prefix;
	}
	
	prefix = " " toString(n-->color) + toString(n->data) + " ";
	
	prefix += ToPrefixString(n->left);
	
	prefix += ToPrefixString(n->right);
	
	return prefix;
}

string ToPostfixString(RBTNode *n) {
	string postfix = "";
	if (n == nullptr) {
		return prefix;
	}
	
	postfix = ToPostfixString(n->left);
	
	postfix = ToPostfixString(n->right);
	
	postfix += " " + toString(n->color) + toString(n->data) + " ";
	
	return postfix;
}

