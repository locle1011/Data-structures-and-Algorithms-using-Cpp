#include "Circular_DLList.h"

template <typename T>
Circular_DLList<T>::Node::Node(const T &data)
{
	this->data = data;
	next = NULL;
	prev = NULL;
}

//Constructor
template <typename T>
Circular_DLList<T>::Circular_DLList()
{
	head = NULL;
	count = 0;
}

template <typename T>
Circular_DLList<T>::Circular_DLList(initializer_list<T> l)
{
	count = l.size();
	auto it = l.begin();
	head = new Node(*it);
	head->next = head;
	head->prev = head;
	it++;
	while (it != l.end())
	{
		Node *newNode = new Node(*it);
		head->prev->next = newNode;
		newNode->next = head;
		newNode->prev = head->prev;
		head->prev = newNode;
		it++;
	}
}

template <typename T>
Circular_DLList<T>::Circular_DLList(const Circular_DLList<T> &cdl)
{
	if (cdl.count == 0)
	{
		count = 0;
		head = NULL;
	}
	else
	{
		count = cdl.count;
		Node *cur = cdl.head;
		head = new Node(cur->data);
		head->next = head;
		head->prev = head;
		cur = cur->next;
		while (cur != cdl.head)
		{
			Node *newNode = new Node(cur->data);
			head->prev->next = newNode;
			newNode->next = head;
			newNode->prev = head->prev;
			head->prev = newNode;
			cur = cur->next;
		}
	}
}

template <typename T>
Circular_DLList<T>::~Circular_DLList()
{
	if (head == NULL)
		return;
	while (head != head->next)
	{
		Node *temp = head;
		head->prev->next = head->next;
		head->next->prev = head->prev;
		head = head->next;
		delete temp;
	}
	delete head;
	head = NULL;
	count = 0;
}

template <typename T>
const Circular_DLList<T> &Circular_DLList<T>::operator=(const Circular_DLList<T> &cdl)
{
	clear();
	if (cdl.count != 0)
	{
		count = cdl.count;
		Node *cur = cdl.head;
		head = new Node(cur->data);
		head->next = head;
		head->prev = head;
		cur = cur->next;
		while (cur != cdl.head)
		{
			Node *newNode = new Node(cur->data);
			head->prev->next = newNode;
			newNode->next = head;
			newNode->prev = head->prev;
			head->prev = newNode;
			cur = cur->next;
		}
	}
	return cdl;
}

//Capacity
template <typename T>
int Circular_DLList<T>::size()
{
	return count;
}

template <typename T>
bool Circular_DLList<T>::empty()
{
	return count == 0;
}

//Element access
template <typename T>
T &Circular_DLList<T>::at(int pos)
{
	if (pos < 0 || pos >= count)
		throw out_of_range("Index is out of bound");
	Node *cur = head;
	for (int i = 0; i < pos; i++)
	{
		cur = cur->next;
	}
	return cur->data;
}

template <typename T>
T &Circular_DLList<T>::front()
{
	if (head == NULL)
		throw out_of_range("List is empty");
	return head->data;
}

template <typename T>
T &Circular_DLList<T>::back()
{
	if (head == NULL)
		throw out_of_range("List is empty");
	return head->prev->data;
}

//Modifiers
template <typename T>
void Circular_DLList<T>::push_front(const T &data)
{
	if (head == NULL)
	{
		head = new Node(data);
		head->next = head;
		head->prev = head;
	}
	else
	{
		Node *newNode = new Node(data);
		newNode->prev = head->prev;
		head->prev->next = newNode;
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}
	count++;
}

template <typename T>
bool Circular_DLList<T>::pop_front()
{
	if (head == NULL)
		return false;
	Node *temp = head;
	head->prev->next = head->next;
	head->next->prev = head->prev;
	head = head->next;
	delete temp;
	if (count == 1)
		head = NULL;
	count--;
	return true;
}

template <typename T>
void Circular_DLList<T>::push_back(const T &data)
{
	if (head == NULL)
	{
		head = new Node(data);
		head->next = head;
		head->prev = head;
	}
	else
	{
		Node *newNode = new Node(data);
		newNode->next = head;
		newNode->prev = head->prev;
		head->prev->next = newNode;
		head->prev = newNode;
	}
	count++;
}

template <typename T>
bool Circular_DLList<T>::pop_back()
{
	if (head == NULL)
		return false;
	Node *temp = head->prev;
	head->prev = temp->prev;
	temp->prev->next = head;
	delete temp;
	if (count == 1)
		head = NULL;
	count--;
	return true;
}

template <typename T>
bool Circular_DLList<T>::insert(int pos, const T &data)
{
	if (pos < 0 || pos > count)
		return false;
	if (pos == 0)
		push_front(data);
	else if (pos == count)
		push_back(data);
	else
	{
		Node *cur = head;
		for (int i = 0; i < pos - 1; i++)
		{
			cur = cur->next;
		}
		Node *newNode = new Node(data);
		newNode->next = cur->next;
		cur->next->prev = newNode;
		newNode->prev = cur;
		cur->next = newNode;
		count++;
	}
	return true;
}

template <typename T>
bool Circular_DLList<T>::erase(int pos)
{
	if (pos < 0 || pos >= count)
		return false;
	if (pos == 0)
		pop_front();
	else if (pos == count - 1)
		pop_back();
	else
	{
		Node *cur = head;
		for (int i = 0; i < pos - 1; i++)
		{
			cur = cur->next;
		}
		Node *temp = cur->next;
		cur->next = temp->next;
		temp->next->prev = cur;
		delete temp;
		count--;
	}
	return true;
}

template <typename T>
void Circular_DLList<T>::clear()
{
	if (head == NULL)
		return;
	while (head != head->next)
	{
		Node *temp = head;
		head->prev->next = head->next;
		head->next->prev = head->prev;
		head = head->next;
		delete temp;
	}
	delete head;
	head = NULL;
	count = 0;
}

//Operation
template <typename T>
bool Circular_DLList<T>::remove(const T &item)
{
	if (head == NULL)
		return false;
	if (head->data == item)
	{
		if (count == 1)
		{
			delete head;
			head = NULL;
			count--;
		}
		else
			pop_front();
	}
	else
	{
		Node *cur = head->next;
		while (cur->next != head->next)
		{
			if (cur->next->data == item)
			{
				Node *temp = cur->next;
				cur->next = temp->next;
				temp->next->prev = cur;
				delete temp;
				count--;
				return true;
			}
			else
				cur = cur->next;
		}
	}
}

template <typename T>
void Circular_DLList<T>::reverse()
{
	if (count <= 1)
		return;
	Node *cur = head;
	while (cur->next != head)
	{
		Node *temp = cur->next;
		cur->next = cur->prev;
		cur->prev = temp;
		cur = temp;
	}
	cur->next = cur->prev;
	cur->prev = head;
	head = cur;
}

template <typename T>
void Circular_DLList<T>::display()
{
	if (head == NULL)
		cout << "List is empty" << endl;
	else
	{
		Node *cur = head;
		do
		{
			cout << cur->data << " <=> ";
			cur = cur->next;
		} while (cur != head);
		cout << "HEAD" << endl;
	}
}