#pragma once
#include <iostream>
#include <initializer_list>
using namespace std;

template <typename T>
class SLList
{
private:
	struct Node
	{
		T data;
		Node *next;
		Node(T);
	};

	Node *head;
	int count;

public:
	//Constructor
	SLList();
	SLList(initializer_list<T>);
	SLList(const SLList<T> &);
	~SLList();
	const SLList<T> &operator=(const SLList<T> &);
	//Capacity
	int size();
	bool empty();
	//Element access
	T &at(int);
	T &front();
	//Modifiers
	bool insert(int, const T &);
	bool erase(int);
	void clear();
	//Operations
	bool remove(const T &);
	void sort();
	void reverse();
	void merge(SLList<T> &);
	bool is_sorted();
	void display();
};
