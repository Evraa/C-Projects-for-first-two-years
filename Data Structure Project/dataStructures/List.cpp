#include "List.h"

template <class T>
List<T>::List(void) // the default constructor 
{
	head =NULL;
	ref = NULL;
	tail = NULL;
	count = 0;
}

template <class T>
List<T>::List(const List &L) // copy constructor 
{
	Node <T> *oPtr = L->head;
	if(oPtr == NULL)
		head = NULL;
	else
	{
		head = new Node<T>;
		head->setOb(oPtr->getOb());
		Node <T> *nPtr = head;
		oPtr = oPtr->getNext();
		while(oPtr)
		{
			Node <T> *tuna = new Node<T>;
			tuna->setOb(oPtr->getOb());
			nPtr->setNext(tuna);
			nPtr = nPtr->getNext();
			oPtr = oPtr->getNext();
		}
		nPtr->setNext(NULL);
	}
}

template <class T>
void List<T>::add(T *item)       
{
	if(head == NULL)                  //empty list 
	{
		head = new Node<T>;
		head->setOb(item);			
		tail = head;
	}
	else
	{
		Node<T> *tuna = new Node<T>;     //create the new node
		tuna->setOb(item);

		tail->setNext(tuna);
		tuna->setPrev(tail);
		tail = tail->getNext();
	}
	count++;
}

template <class T>
T* List<T>::remove(T *item)
{
	if(head == NULL)               //empty list
		return NULL;

	Node <T> *tuna = head;
	if(head->getOb() == item)         // head = deleted item
	{                             //overload == 
		T* var = item;
		head = head->getNext();
	//	if (head->getPrev())
	//		head->setPrev(NULL);        
		delete tuna;
		count--;
		return var;
	}
	else
	{
		while(tuna->getNext())
		{
			if(tuna->getNext()->getOb() == item)
			{
				T* var = item;
				Node <T>* ptr = tuna->getNext();
				tuna->setNext(tuna->getNext()->getNext());
				delete ptr;
				ptr = tuna->getNext();
				ptr ->setPrev(tuna);
			
				count--;
				return var;
			}
			else tuna = tuna->getNext();
		}
	}

}

template <class T>
bool List<T>::isEmpty() const
{
	return (head == NULL);
}

template <class T>
bool List<T>::contains(const T *item) const
{
	if(!head)
		return false;
	
	Node <T> *tuna = head;
	while(tuna)
	{
		if(tuna->getOb() == item) //overload ==
			return true;
		else
			tuna = tuna->getNext();
	}

	return false;
}

template <class T>
void List<T>::clear()
{
	while(head)
	{
		Node<T> *tuna = head;
		head = head->getNext();
		delete tuna;
	}
	count = 0;
	head = ref = tail = NULL;
}


template <class T>
List<T>::~List()
{
	clear();
}

template <class T>
int List<T>::getCount()const
{
	return count;
}

/// sort functions

template <class T>
void List<T>::sort() //calls recursive sort using the head
{
	if (count < 2)	return;  
	recSort(&head);
	Node<T>* cur = head;
	while (cur->getNext() != NULL)	cur = cur->getNext();
	tail = cur;
}

template <class T>
void List<T>::recSort(Node<T>** hr) 
{
	Node<T>*h = *hr;
	if (h == NULL || h->getNext() == NULL) //base cases
		return;
	Node<T>* a = NULL;
	Node<T>* b = NULL;
	splitList(h,& a,& b);                 //splits the list into two
	recSort(&a);                         //calls recursive sort for part a
	recSort(&b);                         //calls recursive sort for part b
	*hr = CombineList(a, b);          
}
template <class T>
void List<T>::splitList(Node<T>*h,Node<T>** a, Node<T>** b) //splits the list into two lists
{
	Node<T>* fast;
	Node<T>* slow;
	slow = h;
	fast = h->getNext();

	/* Advance 'fast' two nodes, and advance 'slow' one node */
	while (fast != NULL)
	{
		fast = fast->getNext();
		if (fast != NULL)
		{
			slow = slow->getNext();
			fast = fast->getNext();
		}
	}
	*a = h;
	*b = slow->getNext();
	slow->getNext()->setPrev(NULL);
	slow->setNext(NULL);
}

template <class T>
Node<T>* List<T>::CombineList(Node<T>* FL, Node<T>* SL)
{
	if (FL == NULL)  return SL;
	else if (SL == NULL)  return FL;
	Node<T>* nh;
	if (*(SL->getOb()) > (FL->getOb()))
	{
		Node<T>* n = CombineList(FL, SL->getNext());
		nh = SL;
		n->setPrev(nh);
		nh->setNext(n);
	}
	else
	{
		Node<T>* m = CombineList(FL->getNext(), SL);
		nh = FL;
		m->setPrev(nh);
		nh->setNext(m);
	}
	return nh;
}
/////// reference funcs to traverse the list

template <class T>
void List<T>::setRef()          //sets the reference equals the head to traverse the list from its beginning
{
	ref = head;
}
template <class T>
void List<T>::advanceRef()
{
	if (!ref)
		return;
	ref = ref->getNext();
}
template <class T>
T* List<T>::getRef()
{
	if (!ref)
		return NULL;
	return ref->getOb();
}
template <class T>
void List<T>::deleteRef()
{
	if (!ref)                     //empty list
		return;
	if (ref==head && ref->getNext()==NULL && ref->getPrev()==NULL)          //one node only
	{
		delete head;
		count--;
		head = ref = tail = NULL;
		return;
	}

	if (ref == head)             //first node
	{
		advanceRef();
		delete head;
		count--;
		head = ref;
		head->setPrev(NULL);
		return;
	}

	if (!ref->getNext())           //last node
	{
		ref->getPrev()->setNext(NULL);
		tail = ref->getPrev();
		delete ref;
		count--;
		ref = NULL;
		return;
	}
	ref->getPrev()->setNext(ref->getNext());   //intermediate nodes
	ref->getNext()->setPrev(ref->getPrev());
	Node<T>* ptr = ref;
	advanceRef();
	delete ptr;
	count--;
}

///evram////
template <class T>
void List<T>::addKilled(T* item)
{
	if (head == NULL)
	{
		head = new Node<T>;
		head->setOb(item);			
		tail = head;
	}
	else
	{
		Node<T> *tuna = new Node<T>;     //create the new node
		tuna->setOb(item);
		//we have head, tail and ref
		setRef();
		while (ref->getNext() && ((ref->getNext())->getOb())->getFD() < item->getFD() )
		{
			advanceRef();
		}

		if (ref == NULL) //if it was the last element
		{
			tail->setNext(tuna);
		//	tuna->setPrev(tail);
			tail = tail->getNext();
		}
		else
		{
			if (ref == head) //there is only one element
			{
				if (head->getOb()->getFD() < item->getFD())
				{
					head->setNext(tuna);
					tail = tuna;
					tuna->setNext(NULL);
				}
				else
				{
				head = tuna;
				tuna->setNext(ref);
				}
			}
			else //many elements
			{
				tuna->setNext(ref->getNext());
				ref->setNext(tuna);
			}

		}


	
	}

	count++;


}
	
