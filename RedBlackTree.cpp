#include "RedBlackTree.h"

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
	
	RBTNode* node = new RBTNode;
	node->data = data;
	node->color = COLOR_RED;
	node->left = node->right = nullptr;

	RBTNode* cur = this->root;
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
			node->color = COLOR_RED;
			if (parent->color == COLOR_RED) {
				node->color = COLOR_BLACK;
			}
		} 
		else { //node is greater than parent
			parent->right = node;
			if (parent->color == COLOR_RED) {
				node->color = COLOR_BLACK;
			}
		}
	}
	else { //node is root
		root = node;
		node->color = COLOR_BLACK;
	}

	if (parent->parent != nullptr) {
		insertfix(node);
	}
	numItems++;
}

//referenced for rotations https://www.geeksforgeeks.org/dsa/introduction-to-red-black-tree/
void RedBlackTree::rotateLeft(RBTNode* x) { //y node right becomes x left, x becomes y left
	RBTNode* y = x->right;
	x->right = y->left;

	if (y->left != nullptr) {
		y->left->parent = x;
		y->parent = x->parent;
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

	if (y->right != nullptr) {
		y->right->parent = x;
		y->parent = x->parent;
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
	
	while (cur->parent->parent != nullptr || cur->parent->color == COLOR_RED) {
		if (node->parent == node->parent->parent->left) { //parent is left child
			RBTNode* unc = node->parent->parent->right;
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
			RBTNode* unc = node->parent->parent->right;
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
	
	RBTNode* cur = this->root;
	
	while (cur->data != num || cur != nullptr) {
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
	RBTNode* cur = this->root;
	RBTNode* parent = nullptr;
	
	while (cur != nullptr) {
		parent = cur;
		cur = cur->left;
	}
	
	return parent->data;
}

int RedBlackTree::max() {
	RBTNode* cur = this->root;
	RBTNode* parent = nullptr;
	
	while (cur != nullptr) {
		parent = cur;
		cur = cur->right;
	}
	
	return parent->data;
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

