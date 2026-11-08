#include "RedBlackTree.h"

using namespace std;

RedBlackTree::RedBlackTree() { 
	root = nullptr;
	numItems = 0;
}

RedBlackTree::RedBlackTree(int num) {
	root = new RBTNode;
	root->color = COLOR_BLACK;
	root->data = num;
	root->left = nullptr;
	root->right = nullptr;
	root->parent = nullptr;
	numItems = 1;
}

RedBlackTree::RedBlackTree(const RedBlackTree& tree) {
	this->root = tree.root;
	this->numItems = tree.numItems;
}


void RedBlackTree::Insert(int data) {
	
	if (Contains(data)) { //ends if node already exists
		return;
	}
	numItems++;

	RBTNode* node = new RBTNode;
	node->data = data;
	node->color = COLOR_RED;
	node->left = node->right = nullptr;

	RBTNode* cur = root;
	RBTNode* parent = nullptr;
	
	while (cur != nullptr) {
		parent = cur;
		if (node->data < cur->data) {
			cur = cur->left;
		}
        else {
			cur = cur->right;
		}
	}
	
	node->parent = parent;
	if (parent != nullptr) { //node isn't root
		if (node->data < parent->data) { //if node is less than parent
			parent->left = node;
		} 
		else { //node is greater than parent
			parent->right = node;
		}
	}
	else { //node is root
		root = node;
		root->color = COLOR_BLACK;
		return;
	}

	if (parent->parent != nullptr) {
		insertfix(node);
	}
}

//referenced for rotations https://www.geeksforgeeks.org/dsa/introduction-to-red-black-tree/
void RedBlackTree::rotateLeft(RBTNode* x) { //y node right becomes x left, x becomes y left
	RBTNode* y = x->right;
	x->right = y->left;
	y->parent = x->parent;

	if (y->left != nullptr) {
		y->left->parent = x;
	}

	if (x->parent != nullptr) {
		if (x == x->parent->left) {
		x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}
	}
	else {
		root = y;
	}
	y->left = x;
	x->parent = y;
}

void RedBlackTree::rotateRight(RBTNode* x) { //y node left becomes x right, x becomes y right
	RBTNode* y = x->left;
	x->left = y->right;
	
	y->parent = x->parent;

	if (y->right != nullptr) {
		y->right->parent = x;
	}
	if (x->parent != nullptr) {
		if (x == x->parent->right) {
		x->parent->right = y;
		}
		else {
			x->parent->left = y;
		}
	}
	else {
		root = y;
	}

	y->right = x;
	x->parent = y;
}

//referenced https://www.tutorialspoint.com/data_structures_algorithms/red_black_trees.htm
void RedBlackTree::insertfix(RBTNode* node) {
	RBTNode* cur = node;
	
	while (cur->parent != nullptr && cur->parent->parent != nullptr && cur->parent->color == COLOR_RED) {
		if (cur->parent == cur->parent->parent->left) { //parent is left child
			RBTNode* unc = cur->parent->parent->right;
			if(unc != nullptr && unc->color == COLOR_RED) {
				cur->parent->color = COLOR_BLACK;
				unc->color = COLOR_BLACK;
				cur->parent->parent->color = COLOR_RED;
				cur = cur->parent->parent;
			}
			else {
				if (cur == cur->parent->right) { //tree creates bend
					cur = cur->parent;
					rotateLeft(cur);
				}
				cur->parent->color = COLOR_BLACK;
				cur->parent->parent->color = COLOR_RED;
				rotateRight(cur->parent->parent);
				
			}
		}
		else { //parent is right child
			RBTNode* unc = cur->parent->parent->left;
			if(unc != nullptr && unc->color == COLOR_RED) {
				cur->parent->color = COLOR_BLACK;
				unc->color = COLOR_BLACK;
				cur->parent->parent->color = COLOR_RED;
				cur = cur->parent->parent;
			}
			else {
				if (cur == cur->parent->left) { //tree creates bend
					cur = cur->parent;
					rotateRight(cur);
				}
				cur->parent->color = COLOR_BLACK;
				cur->parent->parent->color = COLOR_RED;
				rotateLeft(cur->parent->parent);			
			}
		}
	}
	
	root->color = COLOR_BLACK;
}


bool RedBlackTree::Contains(int num) {
	
	RBTNode* cur = root;
	
	while (cur != nullptr && cur->data != num) {
		if (num < cur->data) {
			cur = cur->left;
		}
        else {
			cur = cur->right;
		}
	}
	
	if (cur != nullptr) {
		return true;
	}
	return false;
}

int RedBlackTree::min() {
	
	if (root != nullptr) {
		RBTNode* cur = this->root;
		RBTNode* parent = nullptr;
		
		while (cur != nullptr) {
			parent = cur;
			cur = cur->left;
		}
		
		return parent->data;
	}
	throw invalid_argument("tree is empty");

}

int RedBlackTree::max() {
	
	if (root != nullptr) {
		RBTNode* cur = this->root;
		RBTNode* parent = nullptr;
		
		while (cur != nullptr) {
			parent = cur;
			cur = cur->right;
		}
		
		return parent->data;
	}
	throw invalid_argument("tree is empty");
}



int RedBlackTree::size() {
	
	return this->numItems;
}



string RedBlackTree::ToInfixString(const RBTNode *n) const {
	string infix = "";
	if (n != nullptr) {
		infix = ToInfixString(n->left);
		
		if (n->color == COLOR_RED) {
			infix += " R" + to_string(n->data) + " ";
		}
		else {
			infix += " B" + to_string(n->data) + " ";
		}
		
		infix += ToInfixString(n->right);

		return infix;
	}
	return infix;
}



string RedBlackTree::ToPrefixString(const RBTNode *n) const {
	string prefix = "";
	if (n != nullptr) {
		if (n->color == COLOR_RED) {
			prefix += " R" + to_string(n->data) + " ";
		}
		else {
			prefix += " B" + to_string(n->data) + " ";
		}
		
		prefix += ToPrefixString(n->left);
		
		prefix += ToPrefixString(n->right);
		
		return prefix;
	}
	return prefix;
}

string RedBlackTree::ToPostfixString(const RBTNode *n) const {
	string postfix = "";
	if (n != nullptr) {
		postfix += ToPostfixString(n->left);
		
		postfix += ToPostfixString(n->right);
		
		if (n->color == COLOR_RED) {
			postfix += " R" + to_string(n->data) + " ";
		}
		else {
			postfix += " B" + to_string(n->data) + " ";
		}
			
		return postfix;
	}
	return postfix;
}

