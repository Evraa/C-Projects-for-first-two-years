#define NULL 0


#pragma once


template<class T1>
class Node
{
	T1 * ob;
	Node* next;
	Node* prev;
public:
	Node()
	{
	ob = NULL;
	prev = NULL;
	next = NULL;
	}

	void setOb(T1 *ptr)
	{
		if (ob!=NULL)
		{
			delete ob;
			ob = NULL;
		}

		ob = ptr;
	}
	void setNext(Node *N)
	{
		
		next = N;
	}
	void setPrev(Node *N)
	{
	    
		prev = N;
	}
	Node<T1>* getNext() const
	{
		return next;
	}
	Node<T1>* getPrev() const
	{
		return prev;
	}
	T1* getOb() const
	{
		return ob;
	}

};



