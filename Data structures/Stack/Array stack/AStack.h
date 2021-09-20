#pragma once
template <class T>
class AStack
{
private:
	T *arr;
	int cap;
	int count;

public:
	AStack(int);
	AStack(const AStack<T> &);
	~AStack();
	const AStack<T> &operator=(const AStack<T> &);
	//Capacity
	int size();
	int capacity();
	bool empty();
	bool full();
	//Modifiers
	T top();
	bool pop();
	bool push(const T &);
};
