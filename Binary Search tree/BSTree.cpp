//Name: Shivang Trivedi
//Date: March 27, 2019
//Lab: 09 - Take Home
#include "BSTree.h"
#include <algorithm> 
template <typename DataType, class KeyType>
BSTree<DataType, KeyType>::BSTreeNode::BSTreeNode ( const DataType &nodeDataItem, BSTreeNode *leftPtr, BSTreeNode *rightPtr )
{
	dataItem = nodeDataItem;
	left = leftPtr;
	right = rightPtr;
}


template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::BSTree ()
{
	root = NULL;
}

template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::BSTree ( const BSTree<DataType,KeyType>& other )
{
	root = other.root;
	copyTree(root);
}

template < typename DataType, class KeyType >
BSTree<DataType, KeyType>& BSTree<DataType, KeyType>:: operator= ( const BSTree<DataType,KeyType>& other )
{
	if (this != other) {
		clear();
		root = other.root;
		copyTree(root);
	}
	return *this;
}

template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::~BSTree ()
{
	clear();
}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::insert ( const DataType& newDataItem )
{
	insertHelper(root, newDataItem);
}

template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::retrieve ( const KeyType& searchKey, DataType& searchDataItem ) const
{
	return retrieveHelper(root, searchKey, searchDataItem);
}

template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::remove ( const KeyType& deleteKey )
{
	return (removeHelper(root, deleteKey));
}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::writeKeys () const
{
	writeKeysHelper(root);
}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::clear ()
{
	clearHelper(root);
	root = NULL;
}

template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::isEmpty () const
{
	return (root == NULL);
}

template < typename DataType, class KeyType >
int BSTree<DataType, KeyType>::getHeight () const
{
	getHeightHelper(root);
}

template < typename DataType, class KeyType >
int BSTree<DataType, KeyType>::getCount () const
{
	return(getCountHelper(root));
}

template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::writeLessThan(const KeyType & searchKey) const
{
	
	writeLTHelper(root, searchKey);
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::showStructure() const

// Outputs the keys in a binary search tree. The tree is output
// rotated counterclockwise 90 degrees from its conventional
// orientation using a "reverse" inorder traversal. This operation is
// intended for testing and debugging purposes only.

{
	if (root == 0)
		cout << "Empty tree" << endl;
	else
	{
		cout << endl;
		showHelper(root, 1);
		cout << endl;
	}
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::insertHelper(BSTreeNode *& p, const DataType & newDataItem)
{
	if (p == 0) {
		p = new BSTreeNode(newDataItem,0,0);
	}
	else if (newDataItem.getKey() < p->dataItem.getKey()) {
		insertHelper(p->left, newDataItem);
	}
	else if(newDataItem.getKey() > p->dataItem.getKey()){
		insertHelper(p->right, newDataItem);
	}
	else {
		p->dataItem = newDataItem;
	}

}

template<typename DataType, class KeyType>
bool BSTree<DataType, KeyType>::retrieveHelper(BSTreeNode * p, const KeyType & searchKey, DataType & searchDataItem) const
{
	if (p == 0) {
		return false;
	}
	else if ((p->dataItem.getKey()) > searchKey) {
		retrieveHelper(p->left, searchKey, searchDataItem);
	}
	else if ((p->dataItem.getKey()) < searchKey) {
		retrieveHelper(p->right, searchKey, searchDataItem);
	}
	else {
		searchDataItem = p->dataItem;
		return true;
	}
}

template<typename DataType, class KeyType>
bool BSTree<DataType, KeyType>::removeHelper(BSTreeNode *& p, const KeyType & deleteKey)
{
	BSTreeNode *delPtr;
	if (p == 0) {
		return false;
	}
	else if ((p->dataItem.getKey()) > deleteKey) {
		removeHelper(p->left, deleteKey);
	}
	else if ((p->dataItem.getKey()) < deleteKey) {
		removeHelper(p->right, deleteKey);
	}
	else {
		delPtr = p;
		if (delPtr->left == NULL && delPtr->right == NULL) {
			delete delPtr;
			p = NULL;
		}
		else if (delPtr->left == NULL) {
			p = p->right;
			delete delPtr;
		}
		else if (delPtr->right == NULL) {
			p = p->left;
			delete delPtr;
		}
		else {
			cutRightmost(p->left, delPtr);
			return (removeHelper(p->left, (p->dataItem.getKey())));
		}
		return true;
	}

}

template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::cutRightmost(BSTreeNode *& r, BSTreeNode *& delPtr)
{
	 while (r->right != NULL) {
		r = r->right;
	 }
	 delPtr->dataItem = r->dataItem;

}

template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::writeKeysHelper(BSTreeNode * p) const
{
	if (p != NULL) {
		writeKeysHelper(p->left);
		cout << p->dataItem.getKey() << " ";
		writeKeysHelper(p->right);
	}


}

template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::clearHelper(BSTreeNode * p)
{
	if (p != 0) {
		clearHelper(p->left);
		clearHelper(p->right);
		delete p;
	}
}

template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::showHelper(BSTreeNode *p,
	int level) const

	// Recursive helper for showStructure. 
	// Outputs the subtree whose root node is pointed to by p. 
	// Parameter level is the level of this node within the tree.

{
	int j;   // Loop counter

	if (p != 0)
	{
		showHelper(p->right, level + 1);         // Output right subtree
		for (j = 0; j < level; j++)    // Tab over to level
			cout << "\t";
		cout << " " << p->dataItem.getKey();   // Output key
		if ((p->left != 0) &&           // Output "connector"
			(p->right != 0))
			cout << "<";
		else if (p->right != 0)
			cout << "/";
		else if (p->left != 0)
			cout << "\\";
		cout << endl;
		showHelper(p->left, level + 1);          // Output left subtree
	}
}

template<typename DataType, class KeyType>
int BSTree<DataType, KeyType>::getHeightHelper(BSTreeNode * p) const
{
if (p == NULL) {
		return 0;
	}
	else {
			return (max(getHeightHelper(p->left), getHeightHelper(p->right) + 1));
	}
}

template<typename DataType, class KeyType>
int BSTree<DataType, KeyType>::getCountHelper(BSTreeNode * p) const
{
	
	if (p == NULL) {
		return 0;
	}
	else {
		return (getCountHelper(p->left) + getCountHelper(p->right) + 1);
	}
}

template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::writeLTHelper(BSTreeNode * p, const KeyType & searchKey) const
{
	if (p != NULL) {
		writeLTHelper(p->left, searchKey);
		if ((p->dataItem.getKey()) < searchKey) {
			cout << p->dataItem.getKey() << " ";
			writeLTHelper(p->right, searchKey);
		}
	}
}

template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::copyTree(const BSTree<DataType, KeyType>& otherTree)
{
	copyTreeHelper(root, otherTree);
}

template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::copyTreeHelper(BSTreeNode *& p, const BSTreeNode * otherPtr)
{
	if (p != 0) {
		p = new BSTreeNode(otherPtr->dataItem, otherPtr->left, otherPtr->right);
		copyTreeHelper(NULL, p->left);
		copyTreeHelper(NULL, p->right);
	}
}


