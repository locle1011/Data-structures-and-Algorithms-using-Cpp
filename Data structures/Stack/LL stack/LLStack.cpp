#include "LLStack.h"

template <class T>
LLStack<T>::Node::Node(const T &data)
{
	this->data = data;
	this->next = nullptr;
}

template <class T>
LLStack<T>::LLStack()
{
	head = nullptr;
	count = 0;
}

template <class T>
LLStack<T>::LLStack(const LLStack<T> &other)
{
	if (other.count == 0)
	{
		head = nullptr;
		count = 0;
	}
	else
	{
		count = other.count;
		Node *cur = other.head;
		head = new Node(cur->data);
		Node *tail = head;
		cur = cur->next;
		while (cur != nullptr)
		{
			Node *newNode = new Node(cur->data);
			tail->next = newNode;
			tail = tail->next;
			cur = cur->next;
		}
	}
}

template <class T>
LLStack<T>::~LLStack()
{
	while (head != nullptr)
	{
		Node *temp = head;
		head = head->next;
		delete temp;
	}
	count = 0;
}

template <class T>
const LLStack<T> &LLStack<T>::operator=(const LLStack<T> &other)
{
	this->~LLStack();
	if (other.count != 0)
	{
		count = other.count;
		Node *cur = other.head;
		head = new Node(cur->data);
		Node *tail = head;
		cur = cur->next;
		while (cur != nullptr)
		{
			Node *newNode = new Node(cur->data);
			tail->next = newNode;
			tail = tail->next;
			cur = cur->next;
		}
	}
	return other;
}

//Capacity
template <class T>
int LLStack<T>::size()
{
	return count;
}

template <class T>
bool LLStack<T>::empty()
{
	return count == 0;
}
//Modifiers
template <class T>
T LLStack<T>::top()
{
	if (count == 0)
		return T();
	return head->data;
}

template <class T>
bool LLStack<T>::pop()
{
	if (count == 0)
		return false;
	Node *temp = head;
	head = head->next;
	delete temp;
	count--;
	return true;
}

template <class T>
void LLStack<T>::push(const T &item)
{
	if (head == nullptr)
	{
		head = new Node(item);
	}
	else
	{
		Node *newNode = new Node(item);
		newNode->next = head;
		head = newNode;
	}
	count++;
}