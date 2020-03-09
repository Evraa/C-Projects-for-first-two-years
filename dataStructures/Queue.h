#pragma once
#include "Node.h"
#include<iostream>
using namespace std;

template <class T>
class Queue
{
	int count;
	Node <T> *head, *tail;
public:
	Queue(void);
	void push(T *item);
	T* pop();
	T* front();
	T* back();
	bool isEmpty();
	void clear();
	int getCount()const;
	~Queue();
};
