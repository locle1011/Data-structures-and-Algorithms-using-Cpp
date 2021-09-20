#ifndef AVL_TREE
#define AVL_TREE

#include "..\Item\TreeItem.h"
#include "..\Binary Tree\BinaryTree.h"
#include "..\Binary Tree\BinaryTree.cpp"
#include "..\Binary Search Tree\BST.h"
#include "..\Binary Search Tree\BST.cpp"

#define abs(a) (((a) >= 0) ? (a) : (-(a)))

template <typename T>
class AVLTree : public BST<T>
{
private:
	/*Helper function*/

	// Left rotation
	static void LR(Node<T> *&);
	// Double left-right rotation
	static void DLRR(Node<T> *&);
	// Right rotation
	static void RR(Node<T> *&);
	// Double right-left rotation
	static void DRLR(Node<T> *&);
	static void rotateLeft(Node<T> *&);
	static void rotateRight(Node<T> *&);
	static void _insert(Node<T> *&, const T &);
	static bool _remove(Node<T> *&, const T &);

public:
	AVLTree() : BST<T>::BST() {}
	AVLTree(const AVLTree<T> &);
	~AVLTree();
	const AVLTree<T> &operator=(const AVLTree<T> &);
	//Properities
	void insert(const T &);
	bool remove(const T &);
	static bool is_balanced(Node<T> *);
	static bool isAVL(Node<T> *);
};

#endif // !AVL_TREE
