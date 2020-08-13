#include "ExpressionTree.h"
#include <cstdlib> // For several general-purpose functions
#include <iostream> // For cin, cout, and system
#include <string> // For string data type
using namespace std; // So "std::cout" may be abbreviated to "cout"
//Name: Shivang Trivedi
//Date: March 20, 2019
//--------------------------------------------------------------------
template <typename DataType>
ExprTree<DataType>::ExprTreeNode:: ExprTreeNode ( char nodeDataItem,
                              ExprTreeNode *leftPtr,
                              ExprTreeNode *rightPtr )
{
	//set datamembers
	dataItem = nodeDataItem;
	left = leftPtr;
	right = rightPtr;


}


template <typename DataType>
ExprTree<DataType>:: ExprTree ()
{
	//create a empty root
	root = NULL;


}

template <typename DataType>
ExprTree<DataType>:: ExprTree ( const ExprTree &source )
{
	//copy constructor
	root = source.root;
	copyHelper(root);
}


template <typename DataType>
ExprTree<DataType>& ExprTree<DataType>::operator=(const ExprTree& source) 
{
	
	if (this != &source) {
		root = source.root;
		copyHelper(root);
	}
	return *this;
	
}

template <typename DataType>
void ExprTree<DataType>:: copyHelper ( ExprTreeNode *&p )
{
	if (p != 0) {
		p = new ExprTreeNode(p->dataItem, p->left, p->right);
		copyHelper(p->left);
		copyHelper(p->right);
	}
}

template <typename DataType>
ExprTree<DataType>:: ~ExprTree ()
{

	clear();
}


template <typename DataType>
void ExprTree<DataType>::build() 
{
	clear();
	buildHelper(root);
}

template <typename DataType>
void ExprTree<DataType>::buildHelper(ExprTreeNode*& p) 
{
	char ch;
	cin >> ch;
	p = new ExprTreeNode(ch, 0, 0);

	if (!isdigit(ch)) {
		buildHelper(p->left);
		buildHelper(p->right);
	}
}
template <typename DataType>
void ExprTree<DataType>::expression() const 
{
	exprHelper(root);
}

template <typename DataType>
void ExprTree<DataType>::exprHelper(ExprTreeNode* p) const 
{
	if (p != 0) {
		
		if (!isdigit(p->dataItem)) {
			cout << '(';
			exprHelper(p->left);
		}
		cout << p->dataItem;
		if (!isdigit(p->dataItem)) {
			exprHelper(p->right);
			cout << ')';
		}
	}
}


template <typename DataType>
DataType ExprTree<DataType>::evaluate() const throw (logic_error) 
{
	if (root == NULL) {
		throw logic_error("The tree is empty");
	}	
	return evalHelper(root);
}


template <typename DataType>
DataType ExprTree<DataType>::evalHelper(ExprTreeNode* p) const
{
	float result;	
	if (isdigit(p->dataItem)) {
		result = p->dataItem - '0';
	}
	else {
		float leftEval = evalHelper(p->left);
		float rightEval = evalHelper(p->right);

		if (p->dataItem == '+') {
			result = leftEval + rightEval;
		}
		else if (p->dataItem == '-') {
			result = leftEval - rightEval;
		}
		else if (p->dataItem == '/') {
			result = leftEval / rightEval;
		}
		else if (p->dataItem == '*') {
			result = leftEval * rightEval;
		}
		else {
			result = 0;
		}
	}
	return result;
}

template <typename DataType>
void ExprTree<DataType>:: clear ()
{
	clearHelper(root);    
	root = 0;
}


template <typename DataType>
void ExprTree<DataType>:: clearHelper ( ExprTreeNode *p )
{
	if (p != 0) {
		clearHelper(p->left);
		clearHelper(p->right);
		delete p;
	}
}


template <typename DataType>
void ExprTree<DataType>:: showStructure () const
{

		// Outputs an expression tree. The tree is output rotated counter-
		// clockwise 90 degrees from its conventional orientation using a
		// "reverse" inorder traversal. This operation is intended for testing
		// and debugging purposes only.

		if (root==NULL)
			cout << "Empty tree" << endl;
		else
		{
			cout << endl;
			showHelper(root, 1);
			cout << endl;
		}
	

}


template <typename DataType>
void ExprTree<DataType>::showHelper(ExprTreeNode *p, int level) const

// Recursive helper for the showStructure() function. Outputs the
// subtree whose root node is pointed to by p. Parameter level is the
// level of this node within the expression tree.

{
	int j;   // Loop counter

	if (p != 0)
	{
		showHelper(p->right, level + 1);        // Output right subtree
		for (j = 0; j < level; j++)   // Tab over to level
			cout << "\t";
		cout << " " << p->dataItem;        // Output dataItem
		if ((p->left != 0) &&          // Output "connector"
			(p->right != 0))
			cout << "<";
		else if (p->right != 0)
			cout << "/";
		else if (p->left != 0)
			cout << "\\";
		cout << endl;
		showHelper(p->left, level + 1);         // Output left subtree
	}
}



template <typename DataType>
void ExprTree<DataType>::commute() 
{
	commuteHelper(root);
}


template <typename DataType>
void ExprTree<DataType>::commuteHelper(ExprTreeNode* p)
{
	if (p != 0) {
		if (!isdigit(p->dataItem)) {
			ExprTreeNode *temp = p->left;
			p->left = p->right;
			p->right = temp;
		}
		commuteHelper(p->left);
		commuteHelper(p->right);
	}
	else {
		return;
	}

}

template <typename DataType>
bool ExprTree<DataType>::isEquivalent(const ExprTree<DataType>& source) const 
{
	return isEquivalentHelper(root, source.root);
}


template <typename DataType>
bool ExprTree<DataType>::isEquivalentHelper(const ExprTreeNode* x,
					   const ExprTreeNode* y) const
{

	if (x == NULL && y == NULL) {
		return true;
	}
	else if (x != NULL && y != NULL) {
		if (x->dataItem == y->dataItem) {
			if (isEquivalentHelper(x->left, y->left) && isEquivalentHelper(x->right, y->right)) {
				return true;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}

}
