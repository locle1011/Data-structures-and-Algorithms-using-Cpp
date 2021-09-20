
#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "..\Item\TreeItem.h"

#define Max(a, b) ((a > b) ? (a) : (b))
#define Min(a, b) ((a < b) ? (a) : (b))

template <class T>
class BinaryTree
{
protected:
	Node<T> *root;
	//
	static Node<T> *createNLR(T *, int &);
	static void travLNR(Node<T> *);
	static void travNLR(Node<T> *);
	static void travLRN(Node<T> *);
	static void travLevels(Node<T> *);
	static Node<T> *copy(Node<T> *);
	static inline int getHeight(Node<T> *);
	static void computeHeight(Node<T> *&);
	static int computeLeaves(Node<T> *);
	static int computeInteriors(Node<T> *);
	static int computeNodes(Node<T> *);
	static void _clear(Node<T> *&);

public:
	BinaryTree() : root(nullptr) {}
	BinaryTree(T *);
	BinaryTree(const BinaryTree<T> &);
	virtual ~BinaryTree();
	const BinaryTree<T> &operator=(const BinaryTree<T> &);
	//Properties
	Node<T> *&getRoot();
	bool empty();
	int height();
	int countLeaves();
	int countInteriors();
	int countNodes();
	void traverse(TraversalType);
	void clear();
};

#endif // !BINARY_TREE_H
