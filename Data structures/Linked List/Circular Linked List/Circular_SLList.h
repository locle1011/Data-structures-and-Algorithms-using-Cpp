#pragma once
#include <iostream>
#include <initializer_list>
using namespace std;

template <typename T>
class Circular_SLList
{
private:
	struct Node
	{
		T data;
		Node *next;
		Node(T);
	};

	Node *last;
	int count;

public:
	//Constructor
	Circular_SLList();
	Circular_SLList(initializer_list<T>);
	Circular_SLList(const Circular_SLList<T> &);
	~Circular_SLList();
	const Circular_SLList<T> &operator=(const Circular_SLList<T> &);
	//Capacity
	int size();
	bool empty();
	//Element access
	T &at(int);
	T &front();
	T &back();
	//Modifiers
	bool insert(int, const T &);
	bool erase(int);
	void clear();
	//Operations
	bool remove(const T &);
	void reverse();
	void display();
};
