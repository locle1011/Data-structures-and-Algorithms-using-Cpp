#pragma once

template <class T>
class LLQueue
{
private:
	struct Node
	{
		T data;
		Node *next;
		Node(const T &data) : data(data), next(nullptr) {}
	};

	Node *Front;
	Node *Rear;
	int count;

public:
	LLQueue();
	LLQueue(const LLQueue<T> &);
	~LLQueue();
	const LLQueue<T> &operator=(const LLQueue<T> &);
	//Capacity
	int size();
	bool empty();
	//Modifiers
	T front();
	void enqueue(const T &);
	bool dequeue();
};
