#include "Circular_SLList.h"

template <typename T>
Circular_SLList<T>::Node::Node(T data)
{
	this->data = data;
	this->next = NULL;
}

//Constructor
template <typename T>
Circular_SLList<T>::Circular_SLList()
{
	last = NULL;
	count = 0;
}

template <typename T>
Circular_SLList<T>::Circular_SLList(initializer_list<T> l)
{
	count = l.size();
	auto it = l.begin();
	last = new Node(*it);
	last->next = last;
	it++;
	while (it != l.end())
	{
		Node *newNode = new Node(*it);
		newNode->next = last->next;
		last->next = newNode;
		last = last->next;
		it++;
	}
}

template <typename T>
Circular_SLList<T>::Circular_SLList(const Circular_SLList<T> &csl)
{
	if (csl.count != 0)
	{
		count = csl.count;
		Node *cur = csl.last->next;
		last = new Node(cur->data);
		last->next = last;
		cur = cur->next;
		while (cur != csl.last->next)
		{
			Node *newNode = new Node(cur->data);
			newNode->next = last->next;
			last->next = newNode;
			last = last->next;
			cur = cur->next;
		}
	}
	else
	{
		count = 0;
		last = NULL;
	}
}

//Destructor
template <typename T>
Circular_SLList<T>::~Circular_SLList()
{
	if (last == NULL)
		return;
	while (last != last->next)
	{
		Node *temp = last->next;
		last->next = temp->next;
		delete temp;
	}
	delete last;
	last = NULL;
	count = 0;
}

//Assign operator
template <typename T>
const Circular_SLList<T> &Circular_SLList<T>::operator=(const Circular_SLList<T> &csl)
{
	count = csl.count;
	Node *cur = csl.last->next;
	last = new Node(cur->data);
	last->next = last;
	cur = cur->next;
	while (cur != csl.last->next)
	{
		Node *newNode = new Node(cur->data);
		newNode->next = last->next;
		last->next = newNode;
		last = last->next;
		cur = cur->next;
	}
	return csl;
}

//Capacity
template <typename T>
int Circular_SLList<T>::size()
{
	return count;
}

template <typename T>
bool Circular_SLList<T>::empty()
{
	return count == 0;
}

//Element access
template <typename T>
T &Circular_SLList<T>::at(int pos)
{
	if (pos < 0 || pos >= count)
		throw out_of_range("Index is out of bound");
	else
	{
		if (pos == count - 1)
			return last->data;
		Node *cur = last->next;
		for (int i = 0; i < pos; i++)
		{
			cur = cur->next;
		}
		return cur->data;
	}
}

template <typename T>
T &Circular_SLList<T>::front()
{
	if (last == NULL)
		throw out_of_range("List is empty");
	return last->next->data;
}

template <typename T>
T &Circular_SLList<T>::back()
{
	if (last == NULL)
		throw out_of_range("List is empty");
	return last->data;
}

//Modifiers

template <typename T>
bool Circular_SLList<T>::insert(int pos, const T &data)
{
	if (pos < 0 || pos > count)
		return false;
	Node *newNode = new Node(data);
	if (last == NULL)
	{
		last = newNode;
		last->next = last;
	}
	else if (pos == count)
	{
		newNode->next = last->next;
		last->next = newNode;
		last = last->next;
	}
	else
	{
		Node *cur = last;
		for (int i = 0; i < pos; i++)
		{
			cur = cur->next;
		}
		newNode->next = cur->next;
		cur->next = newNode;
	}
	count++;
	return true;
}

template <typename T>
bool Circular_SLList<T>::erase(int pos)
{
	if (pos < 0 || pos >= count)
		return false;
	if (count == 1)
	{
		delete last;
		last = NULL;
	}
	else if (pos == count - 1)
	{
		Node *cur = last->next;
		while (cur->next != last)
		{
			cur = cur->next;
		}
		cur->next = last->next;
		delete last;
		last = cur;
	}
	else
	{
		Node *cur = last;
		for (int i = 0; i < pos; i++)
		{
			cur = cur->next;
		}
		Node *temp = cur->next;
		cur->next = temp->next;
		delete temp;
	}
	count--;
	return true;
}

template <typename T>
void Circular_SLList<T>::clear()
{
	if (last == NULL)
		return;
	while (last != last->next)
	{
		Node *temp = last->next;
		last->next = temp->next;
		delete temp;
	}
	delete last;
	last = NULL;
	count = 0;
}

//Operations
template <typename T>
bool Circular_SLList<T>::remove(const T &item)
{
	if (last == NULL)
		return false;
	if (last->data == item)
	{
		if (count == 1)
		{
			delete last;
			last == NULL;
		}
		else
		{
			Node *cur = last->next;
			while (cur->next != last)
			{
				cur = cur->next;
			}
			cur->next = last->next;
			delete last;
			last = cur;
		}
		count--;
		return true;
	}
	else
	{
		Node *cur = last;
		while (cur->next != last)
		{
			if (cur->next->data == item)
			{
				Node *temp = cur->next;
				cur->next = temp->next;
				delete temp;
				count--;
				return true;
			}
			else
				cur = cur->next;
		}
	}
	return false;
}

template <typename T>
void Circular_SLList<T>::reverse()
{
	if (count > 1)
	{
		Node *prev = last;
		Node *cur = last->next;
		while (cur != last)
		{
			Node *temp = cur;
			cur = cur->next;
			temp->next = prev;
			prev = temp;
		}
		last = last->next;
		cur->next = prev;
	}
}

template <typename T>
void Circular_SLList<T>::display()
{
	if (last == NULL)
		cout << "List is empty" << endl;
	else
	{
		Node *cur = last->next;
		do
		{
			cout << cur->data << "->";
			cur = cur->next;
		} while (cur != last->next);
		cout << "HEAD" << endl;
	}
}