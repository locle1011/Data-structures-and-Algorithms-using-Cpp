#include "DLList.h"

template <typename T>
DLList<T>::Node::Node(const T &data)
{
	this->data = data;
	next = NULL;
	prev = NULL;
}

//Constructor
template <typename T>
DLList<T>::DLList()
{
	head = NULL;
	tail = NULL;
	count = 0;
}

template <typename T>
DLList<T>::DLList(initializer_list<T> l)
{
	count = l.size();
	auto it = l.begin();
	head = new Node(*it);
	tail = head;
	it++;
	while (it != l.end())
	{
		Node *newNode = new Node(*it);
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
		it++;
	}
}

template <typename T>
DLList<T>::DLList(const DLList<T> &dl)
{
	if (dl.count != 0)
	{
		count = dl.count;
		Node *cur = dl.head;
		head = new Node(cur->data);
		tail = head;
		cur = cur->next;
		while (cur != NULL)
		{
			Node *newNode = new Node(cur->data);
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
			cur = cur->next;
		}
	}
	else
	{
		count = 0;
		head = tail = NULL;
	}
}

template <typename T>
DLList<T>::~DLList()
{
	while (head != NULL)
	{
		Node *temp = head;
		head = head->next;
		delete temp;
	}
	tail = NULL;
	count = 0;
}

template <typename T>
const DLList<T> &DLList<T>::operator=(const DLList<T> &dl)
{
	clear();
	if (dl.count != 0)
	{
		count = dl.count;
		Node *cur = dl.head;
		head = new Node(cur->data);
		tail = head;
		cur = cur->next;
		while (cur != NULL)
		{
			Node *newNode = new Node(cur->data);
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
			cur = cur->next;
		}
	}
	return dl;
}

//Capacity
template <typename T>
int DLList<T>::size()
{
	return count;
}

template <typename T>
bool DLList<T>::empty()
{
	return count == 0;
}

//Element access
template <typename T>
T &DLList<T>::at(int pos)
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
T &DLList<T>::front()
{
	if (head == NULL)
		throw out_of_range;
	return head->data;
}

template <typename T>
T &DLList<T>::back()
{
	if (tail == NULL)
		throw out_of_range;
	return tail->data;
}

//Modifiers
template <typename T>
void DLList<T>::push_front(const T &data)
{
	if (head == NULL)
	{
		head = new Node(data);
		tail = head;
	}
	else
	{
		Node *newNode = new Node(data);
		head->prev = newNode;
		newNode->next = head;
		head = newNode;
	}
	count++;
}

template <typename T>
bool DLList<T>::pop_front()
{
	if (head == NULL)
		return false;
	Node *temp = head;
	head = head->next;
	if (head != NULL)
	{
		head->prev = NULL;
	}
	else
		tail = NULL;
	delete temp;
	count--;
	return true;
}

template <typename T>
void DLList<T>::push_back(const T &data)
{
	if (tail == NULL)
	{
		head = new Node(data);
		tail = head;
	}
	else
	{
		Node *newNode = new Node(data);
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	}
	count++;
}

template <typename T>
bool DLList<T>::pop_back()
{
	if (tail == NULL)
		return false;
	Node *temp = tail;
	tail = tail->prev;
	if (tail != NULL)
		tail->next = NULL;
	else
		head = NULL;
	delete temp;
	count--;
	return true;
}

template <typename T>
bool DLList<T>::insert(int pos, const T &data)
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
		newNode->prev = cur;
		cur->next->prev = newNode;
		cur->next = newNode;
		count++;
	}
	return true;
}

template <typename T>
bool DLList<T>::erase(int pos)
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
void DLList<T>::clear()
{
	while (head != NULL)
	{
		Node *temp = head;
		head = head->next;
		delete temp;
	}
	tail = NULL;
	count = 0;
}

//Operations
template <typename T>
bool DLList<T>::remove(const T &item)
{
	if (head == NULL)
		return false;
	if (head->data == item)
	{
		pop_front();
		return true;
	}
	else
	{
		Node *cur = head;
		while (cur->next != NULL)
		{
			if (cur->next->data == item)
			{
				break;
			}
			else
				cur = cur->next;
		}
		if (cur->next != NULL)
		{
			if (cur->next == tail)
			{
				pop_back();
				return true;
			}
			else
			{
				Node *temp = cur->next;
				cur->next = temp->next;
				temp->next->prev = cur;
				delete temp;
				count--;
				return true;
			}
		}
	}
	return false;
}

template <typename T>
bool DLList<T>::is_sorted()
{
	if (count <= 1)
		return true;
	Node *cur = head;
	while (cur->next != NULL)
	{
		if (cur->data > cur->next->data)
			return false;
		cur = cur->next;
	}
	return true;
}

template <typename T>
void DLList<T>::sort()
{
	for (int i = count - 1; i >= 1; i--)
	{
		for (Node *cur = head; cur->next != NULL; cur = cur->next)
		{
			if (cur->data > cur->next->data)
			{
				T temp = cur->data;
				cur->data = cur->next->data;
				cur->next->data = temp;
			}
		}
	}
}

template <typename T>
void DLList<T>::reverse()
{
	if (count <= 1)
		return;
	Node *cur = head->next;
	head->prev = head->next;
	head->next = NULL;
	while (cur->next != NULL)
	{
		Node *temp = cur->next;
		cur->next = cur->prev;
		cur->prev = temp;
		cur = temp;
	}
	tail->next = tail->prev;
	tail->prev = NULL;
	tail = head;
	head = cur;
}

template <typename T>
void DLList<T>::merge(DLList<T> &l)
{
	if (this->is_sorted() && l.is_sorted())
	{
		if (head == NULL)
		{
			this->head = l.head;
			this->tail = l.tail;
			l.head = NULL;
		}
		else
		{
			Node *cur = head;
			while (l.head != NULL && head->data >= l.head->data)
			{
				Node *temp = l.head;
				l.head = l.head->next;
				if (l.head != NULL)
					l.head->prev = NULL;
				temp->next = this->head;
				this->head->prev = temp;
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
					l.head->prev = cur;
					this->tail = l.tail;
					l.head = NULL;
				}
				else
				{
					Node *temp = l.head;
					l.head = l.head->next;
					if (l.head != NULL)
						l.head->prev = NULL;
					temp->next = cur->next;
					cur->next->prev = temp;
					cur->next = temp;
					temp->prev = cur;
				}
			}
		}
		this->count += l.count;
		l.tail = NULL;
		l.count = 0;
	}
}

template <typename T>
void DLList<T>::display()
{
	if (count == 0)
		cout << "List is empty" << endl;
	else
	{
		Node *cur = head;
		while (cur->next != NULL)
		{
			cout << cur->data << " <=> ";
			cur = cur->next;
		}
		cout << cur->data << endl;
	}
}

template <typename T>
void DLList<T>::rdisplay()
{
	if (count == 0)
		cout << "List is empty" << endl;
	else
	{
		Node *cur = tail;
		while (cur->prev != NULL)
		{
			cout << cur->data << " <=> ";
			cur = cur->prev;
		}
		cout << cur->data << endl;
	}
}