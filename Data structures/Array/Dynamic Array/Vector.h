#pragma once
#include <iostream>
#include <initializer_list>
using namespace std;

template<typename T>
class Vector
{
private:
	T* arr;
	int _size;
	int _capacity;
	void ensureCapacity();
	void fill();
	void Swap(T&, T&);
public:
	Vector();
	Vector(int, const T& val = T());
	Vector(initializer_list<T>);
	Vector(const Vector<T>&);
	~Vector();
	//Capacity
	int size();
	int capacity();
	bool empty();
	//Element access
	T& operator[](int);
	T& at(int);
	T& front();
	T& back();
	//Modifiers
	void push_back(const T&);
	void pop_back();
	bool insert(int, const T&);
	bool erase(int);
	bool remove(const T&);
	void swap(Vector<T>&);
	void clear();
	void reverse();
	//Linear search
	int find(const T&);
	//Display
	friend ostream& operator<<(ostream& out, const Vector<T>& v) {
		out << "{";
		for (int i = 0; i < v._size - 1; i++) {
			out << v.arr[i] << ", ";
		}
		if (v._size > 0) cout << v.arr[v._size - 1];
		out << "}";
		return out;
	}
	//operator
	const Vector<T>& operator=(const Vector<T>&);
	bool operator==(const Vector<T>&);
};
