#include "LLQueue.h"

template <class T>
LLQueue<T>::LLQueue()
{
	Front = Rear = nullptr;
	count = 0;
}

template <class T>
LLQueue<T>::LLQueue(const LLQueue<T> &other)
{
	if (count == 0)
	{
		this->LLQueue<T>::LLQueue();
	}
	else
	{
		count = other.count;
		Node *cur = other.Front;
		Front = new Node(cur->data);
		Rear = Front;
		cur = cur->next;
		while (cur != nullptr)
		{
			Node *newNode = new Node(cur->data);
			Rear->next = newNode;
			Rear = newNode;
			cur = cur->next;
		}
	}
}

template <class T>
LLQueue<T>::~LLQueue()
{
	while (Front != nullptr)
	{
		Node *temp = Front;
		Front = Front->next;
		delete temp;
	}
	Rear = nullptr;
	count = 0;
}

template <class T>
const LLQueue<T> &LLQueue<T>::operator=(const LLQueue<T> &other)
{
	this->~LLQueue();
	if (other.count != 0)
	{
		count = other.count;
		Node *cur = other.Front;
		Front = new Node(cur->data);
		Rear = Front;
		cur = cur->next;
		while (cur != nullptr)
		{
			Node *newNode = new Node(cur->data);
			Rear->next = newNode;
			Rear = newNode;
			cur = cur->next;
		}
	}
	return other;
}

//Capacity
template <class T>
int LLQueue<T>::size()
{
	return count;
}

template <class T>
bool LLQueue<T>::empty()
{
	return count == 0;
}

//Modifiers
template <class T>
T LLQueue<T>::front()
{
	if (Front == nullptr)
		return T();
	return Front->data;
}

template <class T>
void LLQueue<T>::enqueue(const T &item)
{
	if (count == 0)
	{
		Front = new Node(item);
		Rear = Front;
	}
	else
	{
		Rear->next = new Node(item);
		Rear = Rear->next;
	}
	count++;
}

template <class T>
bool LLQueue<T>::dequeue()
{
	if (count == 0)
		return false;
	Node *temp = Front;
	Front = Front->next;
	delete temp;
	if (count == 1)
		Rear = nullptr;
	count--;
	return true;
}