#pragma once
#include <iostream>
#include <initializer_list>
using namespace std;

#define max(a, b) ((a > b) ? (a) : (b))
#define min(a, b) ((a < b) ? (a) : (b))

enum Type
{
	MIN = 0,
	MAX = 1
};

template <typename T, Type type = MIN>
class Heap
{
private:
	T *arr;
	int cap;
	int count;

	static inline bool greater(const T &, const T &);
	static inline int left(int);
	static inline int right(int);
	static inline int parent(int);
	void shift_up(int);
	void shift_down(int);
	void copy(initializer_list<T>);
	void copy(T *, int);

public:
	Heap(int);
	Heap(initializer_list<T>);
	Heap(T *, int);
	Heap(const Heap<T, type> &);
	~Heap();
	const Heap<T, type> &operator=(const Heap<T, type> &);
	//Properity
	bool empty();
	bool full();
	bool insert(const T &);
	bool removeRoot();
	T k_greatest(int);
	void clear();
	void display();
};
