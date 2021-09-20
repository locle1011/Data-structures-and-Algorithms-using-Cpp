#pragma once

#include "AVLTree.h"

template <typename T>
void AVLTree<T>::LR(Node<T> *&p)
{
	Node<T> *q = p->left;
	p->left = q->right;
	q->right = p;
	BinaryTree<T>::computeHeight(p);
	BinaryTree<T>::computeHeight(q);
	p = q;
}

template <typename T>
void AVLTree<T>::DLRR(Node<T> *&p)
{
	Node<T> *q = p->left;
	Node<T> *r = q->right;
	p->left = r->right;
	q->right = r->left;
	r->right = p;
	r->left = q;
	BinaryTree<T>::computeHeight(p);
	BinaryTree<T>::computeHeight(q);
	BinaryTree<T>::computeHeight(r);
	p = r;
}

template <typename T>
void AVLTree<T>::RR(Node<T> *&p)
{
	Node<T> *q = p->right;
	p->right = q->left;
	q->left = p;
	BinaryTree<T>::computeHeight(p);
	BinaryTree<T>::computeHeight(q);
	p = q;
}

template <typename T>
void AVLTree<T>::DRLR(Node<T> *&p)
{
	Node<T> *q = p->right;
	Node<T> *r = q->left;
	p->right = r->left;
	q->left = r->right;
	r->left = p;
	r->right = q;
	BinaryTree<T>::computeHeight(p);
	BinaryTree<T>::computeHeight(q);
	BinaryTree<T>::computeHeight(r);
	p = r;
}

template <typename T>
void AVLTree<T>::rotateLeft(Node<T> *&p)
{
	Node<T> *q = p->left;
	int hl = BinaryTree<T>::getHeight(q->left);
	int hr = BinaryTree<T>::getHeight(q->right);
	if (hl >= hr)
		LR(p);
	else
		DLRR(p);
}

template <typename T>
void AVLTree<T>::rotateRight(Node<T> *&p)
{
	Node<T> *q = p->right;
	int hl = BinaryTree<T>::getHeight(q->left);
	int hr = BinaryTree<T>::getHeight(q->right);
	if (hr >= hl)
		RR(p);
	else
		DRLR(p);
}

template <typename T>
void AVLTree<T>::_insert(Node<T> *&root, const T &item)
{
	if (root == nullptr)
	{
		root = new Node<T>(item);
	}
	else if (root->data > item)
	{
		_insert(root->left, item);
		int hl = BinaryTree<T>::getHeight(root->left);
		int hr = BinaryTree<T>::getHeight(root->right);
		if (hl - hr >= 2)
			rotateLeft(root);
		BinaryTree<T>::computeHeight(root);
	}
	else if (root->data < item)
	{
		_insert(root->right, item);
		int hl = BinaryTree<T>::getHeight(root->left);
		int hr = BinaryTree<T>::getHeight(root->right);
		if (hr - hl >= 2)
			rotateRight(root);
		BinaryTree<T>::computeHeight(root);
	}
	else
	{
		root->count++;
	}
}

template <typename T>
bool AVLTree<T>::_remove(Node<T> *&root, const T &item)
{
	bool res;
	if (root == nullptr)
	{
		res = false;
	}
	else if (root->data > item)
	{
		res = _remove(root->left, item);
		int hl = BinaryTree<T>::getHeight(root->left);
		int hr = BinaryTree<T>::getHeight(root->right);
		if (hr - hl >= 2)
			rotateRight(root);
		BinaryTree<T>::computeHeight(root);
	}
	else if (root->data < item)
	{
		res = _remove(root->right, item);
		int hl = BinaryTree<T>::getHeight(root->left);
		int hr = BinaryTree<T>::getHeight(root->right);
		if (hl - hr >= 2)
			rotateLeft(root);
		BinaryTree<T>::computeHeight(root);
	}
	else
	{ // found item
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
		{ // root have two subtree
			BST<T>::removeRightmostNode(root->left, temp);
			int hl = BinaryTree<T>::getHeight(root->left);
			int hr = BinaryTree<T>::getHeight(root->right);
			if (hr - hl >= 2)
				rotateRight(root);
			BinaryTree<T>::computeHeight(root);
		}
		delete temp;
		res = true;
	}
	return res;
}

//
template <typename T>
AVLTree<T>::AVLTree(const AVLTree<T> &other)
{
	Node<T> *&root = BinaryTree<T>::getRoot();
	root = BinaryTree<T>::copy(static_cast<BinaryTree<T>>(other).getRoot());
}

template <typename T>
AVLTree<T>::~AVLTree()
{
	BinaryTree<T>::_clear(BinaryTree<T>::getRoot());
}

template <typename T>
const AVLTree<T> &AVLTree<T>::operator=(const AVLTree<T> &other)
{
	Node<T> *&root = BinaryTree<T>::getRoot();
	BinaryTree<T>::_clear(root);
	root = BinaryTree<T>::copy(static_cast<BinaryTree<T>>(other).getRoot());
	return other;
}

template <typename T>
void AVLTree<T>::insert(const T &item)
{
	Node<T> *&root = BinaryTree<T>::getRoot();
	_insert(root, item);
}

template <typename T>
bool AVLTree<T>::remove(const T &item)
{
	Node<T> *&root = BinaryTree<T>::getRoot();
	return _remove(root, item);
}

template <typename T>
bool AVLTree<T>::is_balanced(Node<T> *root)
{
	bool balanced;
	if (root == nullptr)
	{
		balanced = true;
	}
	else
	{
		balanced = is_balanced(root->left);
		if (balanced)
		{
			balanced = is_balanced(root->right);
		}
		if (balanced)
		{
			int hl = BinaryTree<T>::getHeight(root->left);
			int hr = BinaryTree<T>::getHeight(root->right);
			if (abs(hl - hr) >= 2)
			{
				balanced = false;
			}
		}
	}
	return balanced;
}

template <typename T>
bool AVLTree<T>::isAVL(Node<T> *root)
{
	return is_balanced(root) && BST<T>::isBST(root);
}
