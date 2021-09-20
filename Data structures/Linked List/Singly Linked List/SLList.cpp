#include "SLList.h"

template <typename T>
SLList<T>::Node::Node(T data)
{
	this->data = data;
	this->next = NULL;
}

//Constructor
template <typename T>
SLList<T>::SLList()
{
	head = NULL;
	count = 0;
}

template <typename T>
SLList<T>::SLList(initializer_list<T> l)
{
	count = l.size();
	auto it = l.begin();
	head = new Node(*it);
	it++;
	Node *tail = head;
	while (it != l.end())
	{
		tail->next = new Node(*it);
		tail = tail->next;
		it++;
	}
}

template <typename T>
SLList<T>::SLList(const SLList<T> &other)
{
	if (other.count != 0)
	{
		count = other.count;
		Node *temp = other.head;
		head = new Node(temp->data);
		temp = temp->next;
		Node *tail = head;
		while (temp != NULL)
		{
			tail->next = new Node(temp->data);
			tail = tail->next;
			temp = temp->next;
		}
	}
	else
	{
		count = 0;
		head = NULL;
	}
}

//Destructor
template <typename T>
SLList<T>::~SLList()
{
	while (head != NULL)
	{
		Node *temp = head;
		head = head->next;
		delete temp;
	}
}

//Assign object
template <typename T>
const SLList<T> &SLList<T>::operator=(const SLList<T> &other)
{
	clear();
	if (other.count != 0)
	{
		count = other.count;
		Node *temp = other.head;
		head = new Node(temp->data);
		temp = temp->next;
		Node *tail = head;
		while (temp != NULL)
		{
			tail->next = new Node(temp->data);
			tail = tail->next;
			temp = temp->next;
		}
	}
	return other;
}

//Capacity
template <typename T>
int SLList<T>::size()
{
	return count;
}

template <typename T>
bool SLList<T>::empty()
{
	return count == 0;
}

//Element access
template <typename T>
T &SLList<T>::at(int index)
{
	if (index < 0 || index >= count)
		throw out_of_range("Index is out of bound");
	else
	{
		Node *curNode = head;
		for (int i = 0; i < index; i++)
		{
			curNode = curNode->next;
		}
		return curNode->data;
	}
}

template <typename T>
T &SLList<T>::front()
{
	if (head == NULL)
		throw out_of_range("List is empty");
	return head->data;
}

//Modifiers
template <typename T>
bool SLList<T>::insert(int pos, const T &data)
{
	if (pos < 0 || pos > count)
		return false;
	Node *newNode = new Node(data);
	if (pos == 0)
	{
		newNode->next = head;
		head = newNode;
	}
	else
	{
		Node *curNode = head;
		for (int i = 0; i < pos - 1; i++)
		{
			curNode = curNode->next;
		}
		newNode->next = curNode->next;
		curNode->next = newNode;
	}
	count++;
	return true;
}

template <typename T>
bool SLList<T>::erase(int pos)
{
	if (pos < 0 || pos >= count)
		return false;
	if (pos == 0)
	{
		Node *temp = head;
		head = head->next;
		delete temp;
	}
	else
	{
		Node *curNode = head;
		for (int i = 0; i < pos - 1; i++)
		{
			curNode = curNode->next;
		}
		Node *temp = curNode->next;
		curNode->next = temp->next;
		delete temp;
	}
	count--;
	return true;
}

template <typename T>
void SLList<T>::clear()
{
	while (head != NULL)
	{
		Node *temp = head;
		head = head->next;
		delete temp;
	}
	count = 0;
}

//Operations
template <typename T>
bool SLList<T>::remove(const T &data)
{
	if (head == NULL)
		return false;
	if (head->data == data)
	{
		Node *temp = head;
		head = head->next;
		delete temp;
		count--;
		return true;
	}
	else
	{
		Node *curNode = head;
		while (curNode->next != NULL)
		{
			if (curNode->next->data == data)
			{
				Node *temp = curNode->next;
				curNode->next = temp->next;
				delete temp;
				count--;
				return true;
			}
			else
				curNode = curNode->next;
		}
	}
	return false;
}

template <typename T>
void SLList<T>::sort()
{
	for (int i = count - 1; i >= 1; i--)
	{
		for (Node *curNode = head; curNode->next != NULL; curNode = curNode->next)
		{
			if (curNode->data > curNode->next->data)
			{
				T temp = curNode->data;
				curNode->data = curNode->next->data;
				curNode->next->data = temp;
			}
		}
	}
}

template <typename T>
void SLList<T>::reverse()
{
	if (count <= 1)
		return;
	Node *prev = NULL;
	Node *cur = head;
	while (cur != NULL)
	{
		Node *temp = cur;
		cur = cur->next;
		temp->next = prev;
		prev = temp;
	}
	head = prev;
}

template <typename T>
bool SLList<T>::is_sorted()
{
	if (count <= 1)
		return true;
	Node *prev = head;
	Node *cur = head->next;
	while (cur != NULL)
	{
		if (prev->data > cur->data)
			return false;
		prev = prev->next;
		cur = cur->next;
	}
	return true;
}

template <typename T>
void SLList<T>::merge(SLList<T> &l)
{
	if (this->is_sorted() && l.is_sorted())
	{
		if (head == NULL)
		{
			this->head = l.head;
			l.head = NULL;
		}
		else
		{
			Node *cur = head;
			while (l.head != NULL && head->data >= l.head->data)
			{
				Node *temp = l.head;
				l.head = l.head->next;
				temp->next = this->head;
				this->head = temp;
			}
			while (l.head != NULL)
			{
				while (cur->next != NULL && cur->next->data <= l.head->data)
				{
					cur = cur->next;
				}
				if (cur->next == NULL)
				{
					cur->next = l.head;
					l.head = NULL;
				}
				else
				{
					Node *temp = l.head;
					l.head = l.head->next;
					temp->next = cur->next;
					cur->next = temp;
				}
			}
		}
		this->count += l.count;
		l.count = 0;
	}
}

template <typename T>
void SLList<T>::display()
{
	if (head == NULL)
		cout << "List is empty" << endl;
	else
	{
		Node *cur = head;
		while (cur != NULL)
		{
			cout << cur->data << "->";
			cur = cur->next;
		}
		cout << "NULL" << endl;
	}
}