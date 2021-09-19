#pragma once
#include "Array.h"

//Constructor

template<typename T, unsigned int s>
Array<T, s>::Array(initializer_list<T> l){
	int i = 0;
	for (auto it=l.begin(); i<s; it++,i++) {
		arr[i] = *it;
	}
}

template<typename T, unsigned int s>
Array<T, s>::Array(const Array<T, s> &other) {
	for (int i = 0; i < s; i++) {
		arr[i] = other.arr[i];
	}
}

//Private function
template<typename T, unsigned int s>
void Array<T, s>::eleSwap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}

//Capacity
template<typename T,unsigned int s>
unsigned int Array<T,s>::size() {
	return s;
}

template<typename T,unsigned int s>
bool Array<T, s>::empty() {
	return s == 0;
}

//Elements access
template<typename T,unsigned int s>
T& Array<T, s>::operator[](unsigned int i) {
	return arr[i];
}

template<typename T,unsigned int s>
T& Array<T, s>::at(int i) {
	if (i < 0 || i >= s) throw "Out of bound";
	return arr[i];
}

template<typename T, unsigned int s>
T& Array<T, s>::front(){
	if (s == 0) throw "Array is empty";
	return arr[0];
}

template<typename T, unsigned int s>
T& Array<T, s>::back(){
	if (s == 0) throw "Array is empty";
	return arr[s-1];
}

//Modifiers

template<typename T, unsigned int s>
void Array<T, s>::fill(const T& val) {
	for (unsigned int i = 0; i < s; i++) {
		arr[i] = val;
	}
}

template<typename T, unsigned int s>
void Array<T, s>::swap(Array<T, s>& other) {
	for (unsigned int i = 0; i < s; i++) {
		eleSwap(arr[i], other.arr[i]);
	}
}

// Linear Search

template<typename T,unsigned int s>
unsigned int Array<T, s>::find(const T& val) {
	for (unsigned int i = 0; i < s; i++) {
		if (arr[i] == val) return i;
	}
	return -1;
}

//Selection Sort

template<typename T, unsigned int s>
void Array<T, s>::sort() {
	for (unsigned int i = 0; i < s - 1; i++) {
		unsigned int minIndex = i;
		for (unsigned int j = i + 1; j < s; j++) {
			if (arr[j] < arr[minIndex]) minIndex = j;
		}
		eleSwap(arr[i], arr[minIndex]);
	}
}

//Display

template<typename T, unsigned int s>
void Array<T, s>::display(){
	if (s == 0) cout << "Array is empty" << endl;
	else {
		cout << "[";
		for (unsigned int i = 0; i < s - 1; i++) {
			cout << at(i) << ", ";
		}
		if (s > 0) cout << at(s - 1);
		cout << "]" << endl;
	}
}