#pragma once
#include <iostream>
#include <initializer_list>
using namespace std;

template <typename T>
class DLList
{
private:
	struct Node
	{
		T data;
		Node *next;
		Node *prev;
		Node(const T &);
	};

	Node *head;
	Node *tail;
	int count;

public:
	DLList();
	DLList(initializer_list<T>);
	DLList(const DLList<T> &);
	~DLList();
	const DLList<T> &operator=(const DLList<T> &);
	//Capacity
	int size();
	bool empty();
	//Element access
	T &at(int);
	T &front();
	T &back();
	//Modifiers
	void push_front(const T &);
	bool pop_front();
	void push_back(const T &);
	bool pop_back();
	bool insert(int, const T &);
	bool erase(int);
	void clear();
	//Operation
	bool remove(const T &);
	bool is_sorted();
	void sort();
	void reverse();
	void merge(DLList<T> &);
	void display();
	void rdisplay();
};