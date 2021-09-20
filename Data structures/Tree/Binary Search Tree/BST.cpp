#pragma once

#include "BST.h"

//Helper function

template <typename T>
void BST<T>::insert(Node<T> *&root, const T &item)
{
	/*Using recrusive*/

	if (root == nullptr)
	{
		root = new Node<T>(item);
	}
	else if (root->data > item)
	{
		insert(root->left, item);
		BinaryTree<T>::computeHeight(root);
	}
	else if (root->data < item)
	{
		insert(root->right, item);
		BinaryTree<T>::computeHeight(root);
	}
	else
	{ //root->data==item
		root->count++;
	}

	/*Using loop*/
	//if (root == nullptr) {
	//	root = new Node<T>(item);
	//}
	//else {
	//	Node<T>* parent = nullptr;
	//	Node<T>* cur = root;
	//	while (cur != nullptr) {
	//		parent = cur;
	//		if (cur->data > item) {
	//			cur = cur->left;
	//		}
	//		else if (cur->data < item) {
	//			cur = cur->right;
	//		}
	//		else {
	//			cur->count++;
	//			return;
	//		}
	//	}
	//	Node<T>* newNode = new Node<T>(item);
	//	if (parent->data > item) {
	//		parent->left = newNode;
	//	}
	//	else if (parent->data < item) {
	//		parent->right = newNode;
	//	}
	//}
}

template <typename T>
void BST<T>::removeRightmostNode(Node<T> *&r, Node<T> *&del)
{
	/*Using recursive*/
	if (r->right != nullptr)
	{
		removeRightmostNode(r->right, del);
		BinaryTree<T>::computeHeight(r);
	}
	else
	{
		del->data = r->data;
		del->count = r->count;
		del = r;
		r = r->left;
	}

	/*Using loop*/
	//Node<T>* prev_r = nullptr;
	//Node<T>* r_most = r;
	//while (r_most->right != nullptr) {
	//	prev_r = r_most;
	//	r_most = r_most->right;
	//}
	//del->data = r_most->data;
	//del->count = r_most->count;
	//del = r_most;
	//if (prev_r != nullptr)
	//	prev_r->right = r_most->left;
	//else {
	//	r = r->left;
	//}
}

template <typename T>
bool BST<T>::remove(Node<T> *&root, const T &item)
{
	/*Using recursive*/
	bool res;
	if (root == nullptr)
		res = false;
	else if (root->data > item)
	{
		res = remove(root->left, item);
		BinaryTree<T>::computeHeight(root);
	}
	else if (root->data < item)
	{
		res = remove(root->right, item);
		BinaryTree<T>::computeHeight(root);
	}
	else
	{
		Node<T> *temp = root;
		if (root->left == nullptr && root->right == nullptr)
		{
			root = nullptr;
		}
		else if (root->left == nullptr && root->right != nullptr)
		{
			root = root->right;
		}
		else if (root->left != nullptr && root->right == nullptr)
		{
			root = root->left;
		}
		else
		{
			removeRightmostNode(root->left, temp);
			BinaryTree<T>::computeHeight(root);
		}
		delete temp;
		res = true;
	}
	return res;

	/*Using loop*/
	//bool found = false;
	//Node<T>* parent = nullptr;
	//Node<T>* cur = root;
	//while (cur != nullptr) {
	//	if (cur->data < item) {
	//		parent = cur;
	//		cur = cur->right;
	//	}
	//	else if (cur->data > item) {
	//		parent = cur;
	//		cur = cur->left;
	//	}
	//	else {
	//		found = true;
	//		break;
	//	}
	//}

	//if (found) {
	//	if (cur->left == nullptr && cur->right == nullptr) {
	//		if (cur == root) {
	//			root = nullptr;
	//		}
	//		else if (cur == parent->left) {
	//			parent->left = nullptr;
	//		}
	//		else if (cur == parent->right) {
	//			parent->right = nullptr;
	//		}
	//	}
	//	else if (cur->left != nullptr && cur->right == nullptr) {
	//		if (cur == root) {
	//			root = root->left;
	//		}
	//		else if (cur == parent->left) {
	//			parent->left = cur->left;
	//		}
	//		else if (cur == parent->right) {
	//			parent->right = cur->left;
	//		}
	//	}
	//	else if (cur->left == nullptr && cur->right != nullptr) {
	//		if (cur == root) {
	//			root = root->right;
	//		}
	//		else if (cur == parent->left) {
	//			parent->left = cur->right;
	//		}
	//		else if (cur == parent->right) {
	//			parent->right = cur->right;
	//		}
	//	}
	//	else {
	//		parent = cur;
	//		Node<T>* r_most = cur->left;
	//		while (r_most->right != nullptr) {
	//			parent = r_most;
	//			r_most = r_most->right;
	//		}
	//		cur->data = r_most->data;
	//		cur->count = r_most->count;
	//		cur = r_most;
	//		if (parent != root) {
	//			parent->right = r_most->left;
	//		}
	//		else { // parent==root
	//			root->left = r_most->left;
	//		}
	//	}
	//	delete cur;
	//}
	//return found;
}

template <typename T>
bool BST<T>::find(Node<T> *root, const T &item)
{
	/*Using recursive*/

	//if (root == nullptr) return false;
	//if (root->data == item) return true;
	//else if (root->data > item) {
	//	return find(root->left, item);
	//}
	//else { // root->data < item
	//	return find(root->right, item);
	//}

	/*Using loop*/
	while (root != nullptr)
	{
		if (root->data > item)
			root = root->left;
		else if (root->data < item)
			root = root->right;
		else
			return true;
	}
	return false;
}

//template<typename T>
//void BST<T>::travLRN(Node<T>* root)
//{
//	if (root != nullptr) {
//		travLRN(root->left);
//		travLRN(root->right);
//		cout << root->data << " ";
//	}
//}
//
//template<typename T>
//void BST<T>::travLNR(Node<T>* root) {
//	if (root != nullptr) {
//		travLNR(root->left);
//		cout << root->data << " ";
//		travLNR(root->right);
//	}
//}
//
//template<typename T>
//void BST<T>::travNLR(Node<T>* root)
//{
//	if (root != nullptr) {
//		cout << root->data << " ";
//		travNLR(root->left);
//		travNLR(root->right);
//	}
//}
//
//template<typename T>
//void BST<T>::travLevels(Node<T>* root)
//{
//	if (root == nullptr) return;
//	queue<Node<T>*> q;
//	q.push(root);
//	while (!q.empty()) {
//		Node<T>* cur = q.front();
//		q.pop();
//		cout << cur->data << " ";
//		if (cur->left != nullptr) q.push(cur->left);
//		if (cur->right != nullptr) q.push(cur->right);
//	}
//}

//template<typename T>
//void BST<T>::_clear(Node<T>*& root)
//{
//	if (root == nullptr) return;
//	_clear(root->left);
//	_clear(root->right);
//	delete root;
//	root = nullptr;
//}

//template<typename T>
//Node<T>* BST<T>::copy(Node<T>* root)
//{
//	if (root == nullptr) return nullptr;
//	Node<T>* newRoot = new Node<T>(root->data);
//	newRoot->left = copy(root->left);
//	newRoot->right - copy(root->right);
//	return newRoot;
//}

template <typename T>
bool BST<T>::isBST(Node<T> *root, Node<T> *&prev, bool &first)
{
	bool is_bst = true;
	if (root != nullptr)
	{
		//Check left sub-tree
		if (is_bst)
		{
			is_bst = isBST(root->left, prev, first);
		}

		if (first)
		{
			first = false;
		}
		else if (prev->data >= root->data)
		{
			is_bst = false;
		}
		prev = root;

		//Check right sub-tree
		if (is_bst)
		{
			is_bst = isBST(root->right, prev, first);
		}
	}
	return is_bst;
}

//Member function

template <typename T>
BST<T>::BST(const BST<T> &other)
{
	Node<T> *&root = BinaryTree<T>::getRoot();
	root = BinaryTree<T>::copy(static_cast<BinaryTree<T>>(other).getRoot());
}

template <typename T>
BST<T>::~BST()
{
	Node<T> *&root = BinaryTree<T>::getRoot();
	BinaryTree<T>::_clear(root);
}

template <typename T>
const BST<T> &BST<T>::operator=(const BST<T> &other)
{
	Node<T> *&root = BinaryTree<T>::getRoot();
	BinaryTree<T>::_clear(root);
	root = BinaryTree<T>::copy(static_cast<BinaryTree<T>>(other).getRoot());
	return other;
}

//Properities

//template<typename T>
//bool BST<T>::empty()
//{
//	Node<T>* root = BinaryTree<T>::getRoot();
//	return root == nullptr;
//}

template <typename T>
void BST<T>::insert(const T &item)
{
	Node<T> *&root = BinaryTree<T>::getRoot();
	insert(root, item);
}

template <typename T>
bool BST<T>::remove(const T &item)
{
	Node<T> *&root = BinaryTree<T>::getRoot();
	return remove(root, item);
}

template <typename T>
bool BST<T>::find(const T &item)
{
	Node<T> *root = BinaryTree<T>::getRoot();
	return find(root, item);
}

//template<typename T>
//void BST<T>::traverse(TraversalType type)
//{
//	Node<T>* root = getRoot();
//	if (root == nullptr) cout << "Tree is empty" << endl;
//	else {
//		switch (type)
//		{
//		case IN: travLNR(root);
//			break;
//		case PRE: travNLR(root);
//			break;
//		case POST: travLRN(root);
//			break;
//		case LEVELS: travLevels(root);
//			break;
//		}
//		cout << endl;
//	}
//}

//template<typename T>
//void BST<T>::clear()
//{
//	Node<T>* root = BinaryTree<T>::getRoot();
//	_clear(root);
//}

template <typename T>
bool BST<T>::isBST(Node<T> *root)
{
	Node<T> *prev = nullptr; // Check previous node
	bool first = true;		 // Check the first node
	return isBST(root, prev, first);
}
