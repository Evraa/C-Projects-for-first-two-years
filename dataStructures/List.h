#pragma once
#include "Node.h"
#include<iostream>
using namespace std;

template <class T>
class List
{
	int count;
	Node <T> *head;
	Node <T> *tail;
	Node <T>* ref;
	void recSort(Node<T>**);                              //sorts a list given a pointer to its head
	void splitList(Node<T>*, Node<T>**,Node<T>**);        //splits the list into two
	Node<T>* CombineList(Node<T>*, Node<T>*);
public:
	List(void); // default constructor
	List(const List &L);  //copy constructor

	void add(T *item);
	T* remove(T *item); 
	void addKilled (T* item);
	
	bool isEmpty() const;
	bool contains(const T *item) const;
	void clear();
	int getCount()const;
	void sort();    //sort descendingly using >
	
	~List(); //destructor 

	//// refrence ////
	void setRef();
	void advanceRef();
	T* getRef();
	void deleteRef();

};


