#include "Vector.h"

template<typename T>
void Vector<T>::Swap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}

//Auto ensure capacity
template<typename T>
void Vector<T>::ensureCapacity() {
	T* temp = arr;
	arr = new T[_capacity * 2];
	_capacity *= 2;
	fill();
	for (int i = 0; i < _size; i++) {
		arr[i] = temp[i];
	}
	delete[] temp;
}

//Auto fill default value
template<typename T>
void Vector<T>::fill() {
	for (int i = 0; i < _capacity; i++) {
		arr[i] = T();
	}
}

//Constructor
template<typename T>
Vector<T>::Vector() {
	arr = new T[5];
	_capacity = 5;
	_size = 0;
	fill();
}

template<typename T>
Vector<T>::Vector(int size, const T& val) {
	if (size == 0) throw invalid_argument("Size should not be zero");
	arr = new T[size];
	_capacity = size;
	_size = size;
	for (int i = 0; i < size; i++) {
		arr[i] = val;
	}
}

template<typename T>
Vector<T>::Vector(initializer_list<T> l) {
	arr = new T[l.size()];
	_capacity = l.size();
	_size = l.size();
	auto it = l.begin();
	for (int i = 0; i < _size; i++, it++) {
		arr[i] = *it;
	}
}

template<typename T>
Vector<T>::Vector(const Vector<T>& v) {
	_capacity = v._capacity;
	_size = v._size;
	arr = new T[_capacity];
	for (int i = 0; i < _size; i++) {
		arr[i] = v.arr[i];
	}
}

//Destructor
template<typename T>
Vector<T>::~Vector() {
	_capacity = 0;
	_size = 0;
	delete[] arr;
	arr = NULL;
}

//Capacity
template<typename T>
int Vector<T>::size() {
	return _size;
}

template<typename T>
int Vector<T>::capacity() {
	return _capacity;
}

template<typename T>
bool Vector<T>::empty() {
	return _size == 0;
}

//Element access
template<typename T>
T& Vector<T>::operator[](int i) {
	return arr[i];
}

template<typename T>
T& Vector<T>::at(int i) {
	if (i < 0 || i >= _size) throw out_of_range("Index out of range");
	return arr[i];
}

template<typename T>
T& Vector<T>::front() {
	return arr[0];
}

template<typename T>
T& Vector<T>::back() {
	return arr[_size - 1];
}

//Modifiers
template<typename T>
void Vector<T>::push_back(const T& val) {
	if (_size >= _capacity) {
		ensureCapacity();
	}
	arr[_size] = val;
	_size++;
}

template<typename T>
void Vector<T>::pop_back() {
	arr[_size - 1] = T();
	_size--;
}

template<typename T>
bool Vector<T>::insert(int pos, const T& val) {
	if (pos < 0 || pos > _size) return false;
	if (_size >= _capacity) {
		ensureCapacity();
	}
	for (int i = _size; i > pos; i--) {
		arr[i] = arr[i - 1];
	}
	arr[pos] = val;
	_size++;
	return true;
}

template<typename T>
bool Vector<T>::erase(int pos) {
	if (pos < 0 || pos >= _size) return false;
	for (int i = pos; i < _size - 1; i++) {
		arr[i] = arr[i + 1];
	}
	arr[_size - 1] = T();
	_size--;
	return true;
}

template<typename T>
bool Vector<T>::remove(const T& val) {
	for (int i=0; i < _size; i++) {
		if (arr[i] == val) {
			erase(i);
			return true;
		}
	}
	return false;
}

template<typename T>
void Vector<T>::swap(Vector& v) {
	int temp = _capacity;
	_capacity = v._capacity;
	v._capacity = temp;

	temp = _size;
	_size = v._size;
	v._size = temp;

	T* tempArr = arr;
	arr = v.arr;
	v.arr = tempArr;
}

template<typename T>
void Vector<T>::clear() {
	fill();
	_size = 0;
}

template<typename T>
void Vector<T>::reverse() {
	if (_size <= 1) return;
	for (int i = 0; i < _size / 2; i++) {
		Swap(arr[i], arr[_size - i - 1]);
	}
}

//Operator
template<typename T>
const Vector<T>& Vector<T>::operator=(const Vector<T>& v) {
	if (arr != NULL) delete[] arr;
	_capacity = v._capacity;
	_size = v._size;
	arr = new T[_capacity];
	for (int i = 0; i < _size; i++) {
		arr[i] = v.arr[i];
	}
	return v;
}

template<typename T>
bool Vector<T>::operator==(const Vector<T>& v) {
	if (_size != v._size) return false;
	for (int i = 0; i < _size; i++) {
		if (arr[i] != v.arr[i]) return false;
	}
	return true;
}

//Linear search
template<typename T>
int Vector<T>::find(const T& val) {
	for (int i = 0; i < _size; i++) {
		if (arr[i] == val) return i;
	}
	return -1;
}
