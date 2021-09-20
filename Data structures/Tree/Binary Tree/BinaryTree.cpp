#pragma once

#include "BinaryTree.h"
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

//Private

template <class T>
Node<T> *BinaryTree<T>::createNLR(T *arr, int &i)
{
	if (arr[i] == 0)
		return NULL;
	Node<T> *p = new Node<T>(arr[i]);
	i++;
	p->left = createNLR(arr, i);
	i++;
	p->right = createNLR(arr, i);
	computeHeight(p);
	return p;
}

template <typename T>
void BinaryTree<T>::_clear(Node<T> *&root)
{
	if (root == NULL)
		return;
	_clear(root->left);
	_clear(root->right);
	delete root;
	root = NULL;
}

template <class T>
void BinaryTree<T>::travLNR(Node<T> *root)
{
	/*Recursive Traversal*/
	/*if (root == NULL) return;
	travLNR(root->left);
	cout << root->data << " ";
	travLNR(root->right);*/

	/*Iterative Traversal*/
	stack<Node<T> *> st;
	while (!st.empty() || root != NULL)
	{
		if (root != NULL)
		{
			st.push(root);
			root = root->left;
		}
		else
		{
			root = st.top();
			st.pop();
			cout << root->data << " ";
			root = root->right;
		}
	}
}

template <class T>
void BinaryTree<T>::travLRN(Node<T> *root)
{
	/*Recursive Traversal*/
	/*if (root == NULL) return;
	travLRN(root->left);
	travLRN(root->right);
	cout << root->data << " ";*/

	/*Iterative Traversal*/
	stack<Node<T> *> st;
	Node<T> *lastNode = NULL;
	while (!st.empty() || root != NULL)
	{
		if (root != NULL)
		{
			st.push(root);
			root = root->left;
		}
		else
		{
			Node<T> *q = st.top();
			if (q->right != NULL && q->right != lastNode)
			{
				root = q->right;
			}
			else
			{
				cout << q->data << " ";
				lastNode = q;
				st.pop();
			}
		}
	}
}

template <class T>
void BinaryTree<T>::travNLR(Node<T> *root)
{
	/*Recursive Traversal*/
	/*if (root == NULL) return;
	cout << root->data << " ";
	travNLR(root->left);
	travNLR(root->right);*/

	/*Iterative Traversal*/
	stack<Node<T> *> st;
	if (root != NULL)
		st.push(root);
	while (!st.empty())
	{
		root = st.top();
		st.pop();
		cout << root->data << " ";
		if (root->right != NULL)
			st.push(root->right);
		if (root->left != NULL)
			st.push(root->left);
	}
}

template <class T>
void BinaryTree<T>::travLevels(Node<T> *root)
{
	if (root == NULL)
		return;
	queue<Node<T> *> q;
	q.push(root);
	while (!q.empty())
	{
		Node<T> *cur = q.front();
		q.pop();
		cout << cur->data << " ";
		if (cur->left != NULL)
			q.push(cur->left);
		if (cur->right != NULL)
			q.push(cur->right);
	}
}

template <class T>
Node<T> *BinaryTree<T>::copy(Node<T> *root)
{
	if (root == NULL)
		return NULL;
	Node<T> *copyRoot = new Node<T>(root->data, root->count, root->height);
	copyRoot->left = copy(root->left);
	copyRoot->right = copy(root->right);
	return copyRoot;
}

template <class T>
inline int BinaryTree<T>::getHeight(Node<T> *root)
{
	if (root == NULL)
		return 0;
	return root->height;
}

template <class T>
void BinaryTree<T>::computeHeight(Node<T> *&root)
{
	int hl = getHeight(root->left);
	int hr = getHeight(root->right);
	root->height = Max(hl, hr) + 1;
}

template <class T>
int BinaryTree<T>::computeLeaves(Node<T> *root)
{
	if (root == NULL)
		return 0;
	if (root->left == NULL && root->right == NULL)
		return 1;
	return computeLeaves(root->left) + computeLeaves(root->right);
}

template <class T>
int BinaryTree<T>::computeInteriors(Node<T> *root)
{
	if (root == NULL || (root->left == NULL && root->right == NULL))
		return 0;
	return computeInteriors(root->left) + computeInteriors(root->right) + 1;
}

template <class T>
int BinaryTree<T>::computeNodes(Node<T> *root)
{
	if (root == NULL)
		return 0;
	return computeNodes(root->left) + computeNodes(root->right) + 1;
}

//Public
template <class T>
BinaryTree<T>::BinaryTree(T *arr)
{
	int i = 0;
	root = createNLR(arr, i);
}

template <class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T> &other)
{
	root = copy(other.root);
}

template <class T>
BinaryTree<T>::~BinaryTree()
{
	_clear(root);
}

template <class T>
void BinaryTree<T>::clear()
{
	_clear(root);
}

template <class T>
const BinaryTree<T> &BinaryTree<T>::operator=(const BinaryTree<T> &other)
{
	root = copy(other.root);
	return other;
}

//Proerities

template <class T>
Node<T> *&BinaryTree<T>::getRoot()
{
	return root;
}

template <class T>
bool BinaryTree<T>::empty()
{
	return root == NULL;
}

template <class T>
int BinaryTree<T>::height()
{
	return getHeight(root);
}

template <class T>
int BinaryTree<T>::countLeaves()
{
	return computeLeaves(root);
}

template <class T>
int BinaryTree<T>::countInteriors()
{
	int n = computeInteriors(root);
	if (n > 0)
		n--;
	return n;
}

template <class T>
int BinaryTree<T>::countNodes()
{
	return computeNodes(root);
}

template <class T>
void BinaryTree<T>::traverse(TraversalType type)
{
	if (root == NULL)
		cout << "Tree is empty" << endl;
	else
	{
		switch (type)
		{
		case IN:
			travLNR(root);
			break;
		case PRE:
			travNLR(root);
			break;
		case POST:
			travLRN(root);
			break;
		case LEVELS:
			travLevels(root);
			break;
		}
		cout << endl;
	}
}
