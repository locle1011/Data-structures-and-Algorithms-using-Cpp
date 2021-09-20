#pragma once

#include "BTree.h"

/*Page*/

template <typename T>
Page<T>::Page(const Page<T> &other)
{
	this->countItem = other.countItem;
	this->P0 = NULL;
	for (int i = 0; i < other.countItem; i++)
	{
		this->items[i].key = other.items[i].key;
	}
}

template <typename T>
void Page<T>::display()
{
	for (int i = 0; i < countItem; i++)
	{
		cout << items[i].key << " ";
	}
	cout << endl;
}

/*Helper function*/

template <typename T>
void BTree<T>::findPage(Page<T> *p, const T &key, bool &found, int &pos)
{
	found = false;
	int i = 0;
	int j = p->countItem - 1;
	int k;
	while (i <= j)
	{
		k = (i + j) / 2;
		if (p->items[k].key < key)
		{
			i = k + 1;
		}
		else if (p->items[k].key > key)
		{
			j = k - 1;
		}
		else
		{ // found item
			found = true;
			break;
		}
	}
	if (found)
		pos = k;
	else		 // Not found
		pos = j; // j will be -1 or the index of lowerbound of key
}

template <typename T>
void BTree<T>::findBTree(Page<T> *p, const T &key, bool &found, int &pos)
{
	if (p == NULL)
	{
		found = false;
		pos = -1;
	}
	else
	{
		findPage(p, key, found, pos);
		if (!found)
		{
			if (pos == -1)
			{
				findBTree(p->P0, key, found, pos);
			}
			else
				findBTree(p->items[pos].next, key, found, pos);
		}
	}
}

template <typename T>
void BTree<T>::insertPage(Page<T> *&p, int pos, const T &key, Page<T> *r, bool &overflow, T &overflowKey, Page<T> *&overflowPage)
{
	// Not overflow yet
	overflow = false;
	overflowKey = key;
	overflowPage = NULL;
	/*--------------*/
	for (int i = p->countItem - 1; i > pos; i--)
	{
		p->items[i + 1] = p->items[i];
	}
	p->items[pos + 1].key = key;
	p->items[pos + 1].next = r;
	p->countItem++;
	if (p->countItem == M)
	{ // overflow
		overflow = true;
		overflowKey = p->items[MID].key;
		overflowPage = new Page<T>;
		for (int i = MID + 1, k = 0; i < p->countItem; i++, k++)
		{
			overflowPage->items[k] = p->items[i];
		}
		overflowPage->P0 = p->items[MID].next;
		p->countItem = MID;
		overflowPage->countItem = MID;
	}
}

template <typename T>
void BTree<T>::insertBTree(Page<T> *&parent, const T &key, bool &overflow, T &overflowKey, Page<T> *&overflowPage)
{
	overflowKey = key;
	overflowPage = NULL;
	if (parent == NULL)
	{
		overflow = true;
	}
	else
	{
		int pos = -1;
		bool found = false;
		findPage(parent, key, found, pos);
		if (!found)
		{
			Page<T> *child;
			if (pos == -1)
			{
				child = parent->P0;
			}
			else
			{
				child = parent->items[pos].next;
			}
			insertBTree(child, key, overflow, overflowKey, overflowPage);

			if (overflow)
			{
				T child_overflowKey = overflowKey;
				Page<T> *r = overflowPage;
				insertPage(parent, pos, child_overflowKey, r, overflow, overflowKey, overflowPage);
				//Parent got overflow
				if (overflow)
				{
					if (parent == root)
					{
						Page<T> *newRoot = new Page<T>(overflowKey);
						newRoot->P0 = parent;
						newRoot->items[0].next = overflowPage;
						root = newRoot;
						overflow = false;
					}
				}
			}
		}
	}
}

template <typename T>
void BTree<T>::mergePage(Page<T> *p, Page<T> *parent, int pos, Page<T> *left_sibl)
{
	p->items[p->countItem].key = parent->items[pos].key;
	p->items[p->countItem].next = left_sibl->P0;
	p->countItem++;
	for (int i = 0, last = p->countItem; i < left_sibl->countItem; i++, last++)
	{
		p->items[last] = left_sibl->items[i];
	}
	p->countItem = M - 1;
	delete left_sibl;
	for (int i = pos; i < parent->countItem; i++)
	{
		parent->items[i] = parent->items[i + 1];
	}
	parent->countItem--;
	if (parent == root && parent->countItem == 0)
	{
		root = p;
		delete parent;
	}
}

template <typename T>
void BTree<T>::retrieveRightPage(Page<T> *p, Page<T> *parent, int pos, Page<T> *right_sibl)
{
	int last = p->countItem;
	p->items[last].key = parent->items[pos].key;
	p->items[last].next = right_sibl->P0;
	p->countItem++;
	parent->items[pos].key = right_sibl->items[0].key;
	right_sibl->P0 = right_sibl->items[0].next;
	for (int i = 0; i < right_sibl->countItem - 1; i++)
	{
		right_sibl->items[i] = right_sibl->items[i + 1];
	}
	right_sibl->countItem--;
}

template <typename T>
void BTree<T>::retrieveLeftPage(Page<T> *p, Page<T> *parent, int pos, Page<T> *left_sibl)
{
	for (int i = p->countItem - 1; i >= 0; i--)
	{
		p->items[i + 1] = p->items[i];
	}
	p->items[0].key = parent->items[pos].key;
	p->items[0].next = p->P0;
	int last = left_sibl->countItem - 1;
	p->P0 = left_sibl->items[last].next;
	p->countItem++;
	parent->items[pos].key = left_sibl->items[last].key;
	left_sibl->countItem--;
}

template <typename T>
void BTree<T>::underflowRightPage(Page<T> *p, Page<T> *parent, int pos)
{
	Page<T> *right_sibl = parent->items[pos].next;
	if (right_sibl->countItem > MID)
	{
		retrieveRightPage(p, parent, pos, right_sibl);
	}
	else
	{
		mergePage(p, parent, pos, right_sibl);
	}
}

template <typename T>
void BTree<T>::underflowLeftPage(Page<T> *&p, Page<T> *parent, int pos)
{
	Page<T> *left_sibl = parent->items[pos - 1].next;
	if (left_sibl->countItem > MID)
	{
		retrieveLeftPage(p, parent, pos, left_sibl);
	}
	else
	{
		mergePage(left_sibl, parent, pos, p);
		p = left_sibl;
	}
}

template <typename T>
void BTree<T>::underflow(Page<T> *&p, Page<T> *parent, int pos)
{
	/*p is parent->items[pos] child*/
	Page<T> *left_sibl, *right_sibl;
	int last = parent->countItem - 1;
	if (p == parent->P0)
	{
		left_sibl = NULL; // first child have no left sibling page
	}
	else if (pos == 0)
	{
		left_sibl = parent->P0;
	}
	else
	{
		left_sibl = parent->items[pos - 1].next;
	}

	if (p == parent->items[last].next)
	{
		right_sibl = NULL; // last child page have no right sibling page
	}
	else
	{
		right_sibl = parent->items[pos + 1].next;
	}

	if (left_sibl == NULL)
	{
		underflowRightPage(p, parent, pos + 1);
	}
	else if (right_sibl == NULL)
	{
		underflowLeftPage(p, parent, pos);
	}
	else
	{
		if (right_sibl->countItem > MID)
		{
			retrieveRightPage(p, parent, pos + 1, right_sibl);
		}
		else if (left_sibl->countItem > MID)
		{
			retrieveLeftPage(p, parent, pos, left_sibl);
		}
		else
		{
			mergePage(p, parent, pos + 1, right_sibl);
		}
	}
}

template <typename T>
void BTree<T>::removePage(Page<T> *p, int pos)
{
	for (int i = pos; i < p->countItem; i++)
	{
		p->items[i] = p->items[i + 1];
	}
	p->countItem--;
}

template <typename T>
void BTree<T>::removeRightmostKey(Page<T> *&p, Page<T> *parent, int pos, Item<T> &del)
{
	int last = p->countItem - 1;
	if (p->items[last].next != NULL)
	{
		removeRightmostKey(p->items[last].next, p, last, del);
		if (p->countItem < MID)
		{
			underflow(p, parent, pos);
		}
	}
	else
	{
		del.key = p->items[last].key;
		p->countItem--;
		if (p->countItem < MID)
		{
			underflow(p, parent, pos);
		}
	}
}

template <typename T>
bool BTree<T>::removeBTree(Page<T> *&p, const T &key, Page<T> *parent, int pos)
{
	bool res = false;
	if (p != NULL)
	{
		bool found = false;
		int posKey = -1;
		findPage(p, key, found, posKey);
		if (found)
		{
			res = true;
			if (p->items[0].next == NULL)
			{ // p is leaf page
				removePage(p, posKey);
				if (p->countItem < MID)
				{
					if (p == root)
					{
						if (root->countItem == 0)
						{
							delete root;
							root = NULL;
						}
					}
					else
					{
						underflow(p, parent, pos);
					}
				}
			}
			else
			{ // p is not leaf page
				Page<T> *leftChild = NULL;
				if (posKey == 0)
				{
					leftChild = p->P0;
				}
				else
				{
					leftChild = p->items[posKey - 1].next;
				}

				removeRightmostKey(leftChild, p, posKey - 1, p->items[posKey]);
				if (p != root)
				{
					if (p->countItem < MID)
					{
						underflow(p, parent, pos);
					}
				}
			}
		}
		else
		{ // Not found
			if (p->items[0].next != NULL)
			{
				Page<T> *rightChild = NULL;
				if (posKey == -1)
				{
					rightChild = p->P0;
				}
				else
				{
					rightChild = p->items[posKey].next;
				}

				res = removeBTree(rightChild, key, p, posKey);
				if (p != root)
				{
					if (p->countItem < MID)
					{
						underflow(p, parent, pos);
					}
				}
			}
		}
	}
	return res;
}

template <typename T>
void BTree<T>::_clear(Page<T> *&root)
{
	if (root == NULL)
		return;
	if (root->P0 != NULL)
		_clear(root->P0);
	for (int i = 0; i < root->countItem; i++)
	{
		if (root->items[i].next != NULL)
			_clear(root->items[i].next);
	}
	delete root;
	root = NULL;
}

template <typename T>
void BTree<T>::displayTree(Page<T> *root, int k)
{
	for (int i = 1; i <= k; i++)
	{
		cout << " ";
	}
	cout << "Page: ";
	root->display();
	if (root->P0 != NULL)
	{
		displayTree(root->P0, k + 2);
	}
	for (int i = 0; i < root->countItem; i++)
	{
		if (root->items[i].next != NULL)
		{
			displayTree(root->items[i].next, k + 2);
		}
	}
}

template <typename T>
Page<T> *BTree<T>::copy(Page<T> *root)
{
	if (root == NULL)
		return NULL;
	Page<T> *newRoot = new Page<T>(*root);
	newRoot->P0 = copy(root->P0);
	for (int i = 0; i < newRoot->countItem; i++)
	{
		newRoot->items[i].next = copy(root->items[i].next);
	}
	return newRoot;
}

template <typename T>
BTree<T>::BTree(const BTree<T> &other)
{
	root = copy(other.root);
}

template <typename T>
BTree<T>::~BTree()
{
	_clear(root);
}

template <typename T>
const BTree<T> &BTree<T>::operator=(const BTree<T> &other)
{
	_clear(root);
	root = copy(other.root);
	return other;
}

//Propertites
template <typename T>
bool BTree<T>::empty()
{
	return root == NULL;
}

template <typename T>
bool BTree<T>::find(const T &key)
{
	if (root == NULL)
		return false;
	bool found = false;
	int pos = -1;
	findBTree(root, key, found, pos);
	return found;
}

template <typename T>
void BTree<T>::insert(const T &key)
{
	if (root == NULL)
	{
		root = new Page<T>(key);
	}
	else
	{
		bool overflow;
		T overflowKey;
		Page<T> *overflowPage;
		insertBTree(root, key, overflow, overflowKey, overflowPage);
	}
}

template <typename T>
bool BTree<T>::remove(const T &key)
{
	Page<T> *parent = NULL;
	int pos = -2; // pos=-1 is P0 -- first child of Page
	return removeBTree(root, key, parent, pos);
}

template <typename T>
void BTree<T>::clear()
{
	_clear(root);
}

template <typename T>
void BTree<T>::display()
{
	if (root == NULL)
		cout << "Tree is empty" << endl;
	else
		displayTree(root);
}
