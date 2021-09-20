#ifndef BTREE_H
#define BTREE_H
#include <iostream>
using std::cout;
using std::endl;

const int M = 5;
const int MID = M / 2;

template <typename T>
struct Page;

template <typename T>
struct Item
{
	T key;
	Page<T> *next;

	Item() : key(T()), next(NULL) {}
	Item(const T &key) : key(key), next(NULL) {}
};

template <typename T>
struct Page
{
	Item<T> items[M];
	Page<T> *P0;
	int countItem;

	Page() : P0(NULL), countItem(0) {}
	Page(const T &key) : P0(NULL), countItem(1)
	{
		items[0].key = key;
	}
	Page(const Page<T> &);

	void display();
};

template <typename T>
class BTree
{
private:
	Page<T> *root;

	/*Helper function*/
	// Find key in page
	void findPage(Page<T> *, const T &, bool &, int &);
	// Find key in B-tree
	void findBTree(Page<T> *, const T &, bool &, int &);
	// Insert item in page after pos index
	void insertPage(Page<T> *&, int, const T &, Page<T> *, bool &, T &, Page<T> *&);
	// Insert item in B-tree
	void insertBTree(Page<T> *&, const T &, bool &, T &, Page<T> *&);
	// Merge page p with key had index pos of page parent and page q
	void mergePage(Page<T> *, Page<T> *, int, Page<T> *);
	// Take a key of right sibling page
	void retrieveRightPage(Page<T> *, Page<T> *, int, Page<T> *);
	// Take a key of left sibling page
	void retrieveLeftPage(Page<T> *, Page<T> *, int, Page<T> *);
	// Handle underflow with right sibling page
	void underflowRightPage(Page<T> *, Page<T> *, int);
	// Handle underflow with left sibling page
	void underflowLeftPage(Page<T> *&, Page<T> *, int);
	// Handle underflow
	void underflow(Page<T> *&, Page<T> *, int);
	// Remove key with index pos in page
	void removePage(Page<T> *, int);
	// Remove right-most-key
	void removeRightmostKey(Page<T> *&, Page<T> *, int, Item<T> &);
	// Remove key in B-tree
	bool removeBTree(Page<T> *&, const T &, Page<T> *, int);
	// Clear B-tree in LRN-order
	static void _clear(Page<T> *&);
	// Display B-tree
	static void displayTree(Page<T> *, int k = 0);
	// Copy B-Tree in NLR-order
	static Page<T> *copy(Page<T> *);

public:
	BTree() : root(NULL) {}
	BTree(const BTree<T> &);
	~BTree();
	const BTree<T> &operator=(const BTree<T> &);
	//Properities

	bool empty();
	bool find(const T &);
	void insert(const T &);
	bool remove(const T &);
	void clear();
	void display();
};

#endif // !BTREE_H
