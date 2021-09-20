#pragma once

template <class T>
class AQueue
{
private:
	T *arr;
	int Front;
	int Rear;
	int cap;
	int count;

public:
	AQueue(int);
	AQueue(const AQueue<T> &);
	~AQueue();
	const AQueue<T> &operator=(const AQueue<T> &);
	//Capacity
	int size();
	bool empty();
	int capacity();
	bool full();
	//Modifiers
	T front();
	bool enqueue(const T &);
	bool dequeue();
};
