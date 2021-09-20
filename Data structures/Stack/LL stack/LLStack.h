#pragma once

template <class T>
class LLStack
{
private:
	struct Node
	{
		T data;
		Node *next;
		Node(const T &);
	};

	Node *head;
	int count;

public:
	LLStack();
	LLStack(const LLStack<T> &);
	~LLStack();
	const LLStack<T> &operator=(const LLStack<T> &);
	//Capacity
	int size();
	bool empty();
	//Modifiers
	T top();
	bool pop();
	void push(const T &);
};
