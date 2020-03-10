#include "Queue.h"

template <class T>
Queue<T>::Queue(void)
{
	head = tail = NULL;
	count = 0;
}

template <class T>
void Queue<T>::push(T *item)
{
	if(!head && !tail)
	{

		head = new Node<T>;
		head->setOb(item);
		tail = head;
	}
	else
	{
		Node <T> *tuna = new Node<T>;
		tuna->setOb(item);
		tail->setNext(tuna);
		tail = tail->getNext();
	}
	count++;
}

template <class T>
T* Queue<T>::pop()
{
	if (!head)
		return NULL;
	Node <T> *tuna = head;
	T *var = tuna->getOb();
	head = head->getNext();
	delete tuna;
	count--;
	return var;
}

template <class T>
bool Queue<T>::isEmpty()
{
	return (head == NULL);
}

template <class T>
void Queue<T>::clear()
{
	while(head)
		pop();
	head = NULL;
	tail = NULL;

}

template <class T>
T* Queue<T>::front()
{
	T* var= NULL;
	if(head)
	var = head->getOb();
	return var;
}

template <class T>
T* Queue<T>::back()
{
	T *var = tail->getOb();
	return var;
}
template <class T>
int Queue<T>::getCount()const
{
	return count;
}


template <class T>
Queue<T>::~Queue()
{

	clear();
}

