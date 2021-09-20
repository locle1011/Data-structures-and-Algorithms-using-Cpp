
#ifndef BST_H
#define BST_H

#include "..\Binary Tree\BinaryTree.h"
#include "..\Binary Tree\BinaryTree.cpp"
#include "..\Item\TreeItem.h"

template <typename T>
class BST : public BinaryTree<T>
{
protected:
	//Helper function
	static void insert(Node<T> *&, const T &);
	static void removeRightmostNode(Node<T> *&, Node<T> *&);
	static bool remove(Node<T> *&, const T &);
	static bool find(Node<T> *, const T &);
	static bool isBST(Node<T> *, Node<T> *&, bool &);

public:
	BST() : BinaryTree<T>() {}
	BST(const BST<T> &);
	virtual ~BST();
	const BST<T> &operator=(const BST<T> &);
	//Properities
	void insert(const T &);
	bool remove(const T &);
	bool find(const T &);
	static bool isBST(Node<T> *);
};

#endif // !BST_H
