#include "AQueue.h"

template <class T>
AQueue<T>::AQueue(int cap)
{
	arr = new T[cap];
	this->cap = cap;
	this->count = 0;
	Front = Rear = -1;
}

template <class T>
AQueue<T>::AQueue(const AQueue<T> &other)
{
	cap = other.cap;
	count = other.count;
	Front = other.Front;
	Rear = other.Rear;
	arr = new T[cap];
	for (int i = 0; i < count; i++)
	{
		arr[i] = other.arr[i];
	}
}

template <class T>
AQueue<T>::~AQueue()
{
	delete[] arr;
	count = 0;
	cap = 0;
	Front = Rear = -1;
}

template <class T>
const AQueue<T> &AQueue<T>::operator=(const AQueue<T> &other)
{
	this->~AQueue();
	cap = other.cap;
	count = other.count;
	Front = other.Front;
	Rear = other.Rear;
	arr = new T[cap];
	for (int i = 0; i < count; i++)
	{
		arr[i] = other.arr[i];
	}
	return other;
}

template <class T>
int AQueue<T>::size()
{
	return count;
}

template <class T>
int AQueue<T>::capacity()
{
	return cap;
}

template <class T>
bool AQueue<T>::empty()
{
	return count == 0;
}

template <class T>
bool AQueue<T>::full()
{
	return count == cap;
}

template <class T>
T AQueue<T>::front()
{
	if (Front == -1)
		return T();
	return arr[Front];
}

template <class T>
bool AQueue<T>::enqueue(const T &item)
{
	if (count == cap)
		return false;
	/*Translational move*/
	/*if (count == 0) {
		Front = Rear = 0;
		arr[Front] = item;
	}
	else {
		if (Rear == cap - 1) {
			for (int i = Front; i <= Rear; i++) {
				arr[i - Front] = arr[i];
			}
			Rear -= Front;
			Front = 0;
		}
		arr[++Rear] = item;
	}*/
	/*Circular move*/
	if (count == 0)
	{
		Front = Rear = 0;
		arr[Front] = item;
	}
	else
	{
		if (Rear == cap - 1)
		{
			Rear = -1;
		}
		arr[++Rear] = item;
	}
	count++;
	return true;
}

template <class T>
bool AQueue<T>::dequeue()
{
	if (count == 0)
		return false;
	/*Translational move*/
	/*if (count == 1) {
		Front = Rear = -1;
	}
	else {
		Front++;
	}*/
	/*Cicular move*/
	if (count == 1)
	{
		Front = Rear = -1;
	}
	else
	{
		if (Front == cap - 1)
		{
			Front = -1;
		}
		Front++;
	}
	count--;
	return true;
}