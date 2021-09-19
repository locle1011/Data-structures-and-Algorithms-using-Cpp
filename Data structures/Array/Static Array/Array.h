#pragma once
#include <iostream>
#include <initializer_list>
using namespace std;

template<typename T, unsigned int s>
class Array {
private:
	T arr[s];
	void eleSwap(T&, T&);
public:
	Array(initializer_list<T>);
	Array(const Array<T, s>&);
	//Capacity
	unsigned int size();
	bool empty();
	//Access element
	T& operator[](unsigned int);
	T& at(int);
	T& front();
	T& back();
	//Modifiers
	void fill(const T&);
	void swap(Array<T, s>&);
	//Linear Search
	unsigned int find(const T&);
	//Selection Sort
	void sort();
	//Display
	void display();
};
