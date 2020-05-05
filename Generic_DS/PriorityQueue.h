#pragma once
#include<iostream>
using namespace std;
#include"NodeP.h"

template<class T>
class PriorityQueue
{
	NodeP<T>* front;
	NodeP<T>* rear;
	int count;
public:
	PriorityQueue();
	bool enqueue(T it, int pr);
	bool dequeue(T& frntEntry);
	bool peek(T& it);
	void print();
	void toarr(T*&,int&);
	int getprio();
	int getcount();
};

template<class T>
PriorityQueue<T>::PriorityQueue()
{
	front = rear = NULL;
	count=0;
}

template<class T>
bool PriorityQueue<T>::enqueue(T it, int pr)
{
	NodeP<T>* nptr = front;
	NodeP<T>* n = new NodeP<T>;
	n->setData(it);
	n->setPir(pr);
	cout<<"hahahaha"<<endl;
	count++;
	if (front == NULL) {
		front = rear = n;
		n->setNext(NULL);
		return true;
	}
	if (pr > front->getPir()) {
		n->setNext(front);
		front = n;
		return true;
	}
	while (nptr->getNext() && nptr->getNext()->getPir() >= pr)
	{
		nptr = nptr->getNext();
		//	rear=n;
	}
	n->setNext(nptr->getNext());
	nptr->setNext(n);
	return true;
}



/*template<class T>
bool PriorityQueue<T>::dequeue(T& it)
{
	if (front == NULL)
	{
		return false;
	}
	else if (front == rear)
	{
		it = front->getData();
		delete front;
		front = rear = NULL;
		count--;
		return true;
	}
	else
	{
		it = front->getData();
		NodeP<T>* temp = front;
		front = front->getNext();
		delete temp;
		count--;
		return true;
	}
}*/
template<class T>
bool PriorityQueue<T>:: dequeue(T& frntEntry)  
{
	if(front==NULL)
		return false;

	NodeP<T>* nodeToDeletePtr = front;
	frntEntry = front->getData();
	front = front->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == rear)	 // Special case: one node in queue
		rear = nullptr ;	
		
	// Free memory reserved by the dequeued node
	//delete nodeToDeletePtr;
	//nodeToDeletePtr = NULL;
	count--;
	return true;

}

template<class T>
bool PriorityQueue<T>::peek(T& it)
{
	if (front == NULL)
	{
		return false;
	}
		it = front->getData();
		return true;
}

template<class T>
void PriorityQueue<T>::print()
{
	Node<T>* current = front;
	while (current != NULL)
	{
		cout << current->getData() << " ";
		current = current->getNext();
	}
	cout << endl;
}
template<class T>
void PriorityQueue<T>::toarr(T*& arr,int& i){
	arr=new T[count];
	//cout<<"x"<<endl;
	NodeP<T>* temp = front;
	//cout<<"y"<<endl;
	//int* priorities=new int[count];
	//cout<<"z"<<endl;
	 i=0;
	//cout<<"a"<<endl;
	while(temp){
		//cout<<i<<endl;
		//cout<<i<<endl;
		arr[i++]=temp->getData();
		//cout<<i<<endl;
		temp = temp->getNext();
		//cout<<i<<endl;
	}
	//cout<<"b"<<endl;
	//cout<<"c"<<endl;
}
template<class T>
int PriorityQueue<T>::getprio(){
	return front->getPir();
}
template<class T>
int PriorityQueue<T>::getcount(){
	return count;
}