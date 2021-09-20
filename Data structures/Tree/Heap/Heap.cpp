#include "Heap.h"

//Static function
template <typename T, Type type>
bool Heap<T, type>::greater(const T &e1, const T &e2)
{
	if (type == MIN)
		return e1 < e2;
	else
		return e1 > e2;
}

template <typename T, Type type>
int Heap<T, type>::left(int parent)
{
	return 2 * parent + 1;
}

template <typename T, Type type>
int Heap<T, type>::right(int parent)
{
	return 2 * parent + 2;
}

template <typename T, Type type>
int Heap<T, type>::parent(int child)
{
	return (child - 1) / 2;
}

template <typename T, Type type>
void Heap<T, type>::shift_up(int i)
{
	T item = arr[i];
	while (i > 0)
	{
		int par = parent(i);
		if (greater(item, arr[par]))
		{
			arr[i] = arr[par];
			i = par;
		}
		else
			break;
	}
	arr[i] = item;
}

template <typename T, Type type>
void Heap<T, type>::shift_down(int i)
{
	int child = left(i);
	T item = arr[i];
	while (child < count)
	{
		if (child < count - 1)
		{
			child = (greater(arr[child], arr[child + 1])) ? child : child + 1;
		}
		if (greater(arr[child], item))
		{
			arr[i] = arr[child];
			i = child;
			child = left(i);
		}
		else
			break;
	}
	arr[i] = item;
}

template <typename T, Type type>
void Heap<T, type>::copy(initializer_list<T> l)
{
	cap = l.size();
	count = l.size();
	auto it = l.begin();
	arr = new T[cap];
	for (int i = 0; i < count; i++)
	{
		arr[i] = *it;
		it++;
	}
}

template <typename T, Type type>
void Heap<T, type>::copy(T *other, int size)
{
	arr = new T[size];
	cap = size;
	count = size;
	for (int i = 0; i < count; i++)
	{
		arr[i] = other[i];
	}
}

//Constructor
template <typename T, Type type>
Heap<T, type>::Heap(int cap)
{
	this->cap = cap;
	count = 0;
	arr = new T[cap];
}

template <typename T, Type type>
Heap<T, type>::Heap(initializer_list<T> l)
{
	copy(l);
	for (int i = 1; i < count; i++)
	{
		shift_up(i);
	}
}

template <typename T, Type type>
Heap<T, type>::Heap(T *other, int size)
{
	copy(other, size);
	for (int i = size / 2 - 1; i >= 0; i--)
	{
		shift_down(i);
	}
}

template <typename T, Type type>
Heap<T, type>::Heap(const Heap<T, type> &other)
{
	cap = other.cap;
	count = other.count;
	arr = new T[cap];
	for (int i = 0; i < count; i++)
	{
		arr[i] = other.arr[i];
	}
}

template <typename T, Type type>
Heap<T, type>::~Heap()
{
	delete[] arr;
	arr = NULL;
	cap = 0;
	count = 0;
}

template <typename T, Type type>
const Heap<T, type> &Heap<T, type>::operator=(const Heap<T, type> &other)
{
	~Heap();
	cap = other.cap;
	count = other.count;
	arr = new T[cap];
	for (int i = 0; i < count; i++)
	{
		arr[i] = other.arr[i];
	}
	return other;
}

template <typename T, Type type>
bool Heap<T, type>::empty()
{
	return count == 0;
}

template <typename T, Type type>
bool Heap<T, type>::full()
{
	return count == cap;
}

template <typename T, Type type>
bool Heap<T, type>::insert(const T &item)
{
	if (count == cap)
		return false;
	arr[count] = item;
	shift_up(count);
	count++;
	return true;
}

template <typename T, Type type>
bool Heap<T, type>::removeRoot()
{
	if (count == 0)
		return false;
	arr[0] = arr[count - 1];
	count--;
	shift_down(0);
	return true;
}

template <typename T, Type type>
T Heap<T, type>::k_greatest(int k)
{
	if (count == 0 || k <= 0 || k > count)
		return T();
	T *temp = new T[k];
	for (int i = 0; i < k; i++)
	{
		temp[i] = arr[0];
		removeRoot();
	}

	for (int i = 0; i < k; i++)
	{
		insert(temp[i]);
	}
	T res = temp[k - 1];
	delete[] temp;
	return res;
}

template <typename T, Type type>
void Heap<T, type>::clear()
{
	count = 0;
}

template <typename T, Type type>
void Heap<T, type>::display()
{
	for (int i = 0; i < count; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}