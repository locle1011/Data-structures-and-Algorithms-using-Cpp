#pragma once
#include <iostream>
#include <initializer_list>
using namespace std;

template <typename T>
class Circular_DLList
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
	int count;

public:
	Circular_DLList();
	Circular_DLList(initializer_list<T>);
	Circular_DLList(const Circular_DLList<T> &);
	~Circular_DLList();
	const Circular_DLList<T> &operator=(const Circular_DLList<T> &);
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
	void reverse();
	void display();
};