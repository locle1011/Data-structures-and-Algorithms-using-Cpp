#include "AStack.h"

template <class T>
AStack<T>::AStack(int cap)
{
	arr = new T[cap];
	this->cap = cap;
	this->count = 0;
}

template <class T>
AStack<T>::AStack(const AStack<T> &other)
{
	this->cap = other.cap;
	this->count = other.count;
	arr = new T[cap];
	for (int i = 0; i < count; i++)
	{
		arr[i] = other.arr[i];
	}
}

template <class T>
AStack<T>::~AStack()
{
	delete[] arr;
	arr = nullptr;
	cap = 0;
	count = 0;
}

template <class T>
const AStack<T> &AStack<T>::operator=(const AStack<T> &other)
{
	this->~AStack();
	this->cap = other.cap;
	this->count = other.count;
	arr = new T[cap];
	for (int i = 0; i < count; i++)
	{
		arr[i] = other.arr[i];
	}
	return other;
}

//Capacity
template <class T>
int AStack<T>::size()
{
	return count;
}

template <class T>
int AStack<T>::capacity()
{
	return cap;
}

template <class T>
bool AStack<T>::empty()
{
	return count == 0;
}

template <class T>
bool AStack<T>::full()
{
	return count == cap;
}

//Modifiers
template <class T>
T AStack<T>::top()
{
	if (count == 0)
		return T();
	return arr[count - 1];
}

template <class T>
bool AStack<T>::pop()
{
	if (count == 0)
		return false;
	count--;
	return true;
}

template <class T>
bool AStack<T>::push(const T &item)
{
	if (count == cap)
		return false;
	arr[count] = item;
	count++;
	return true;
}