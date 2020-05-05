#pragma once
#include<iostream>
using namespace std;

template<class T>
class NodeS
{
private:
	T *item;
	NodeS<T>* next;
public:
	NodeS<T>();
	void setItem(T *it);
	void setNext(NodeS<T>* nextNodePtr);
	T *getItem();
	NodeS<T>* getNext();
};

template<class T>
NodeS<T>::NodeS()
{
	next = NULL;
}

template<class T>
void NodeS<T>::setItem(T *newItem)
{
	item = newItem;
}

template<class T>
void NodeS<T>::setNext(NodeS<T>* nextNodePtr)
{
	next = nextNodePtr;
}

template<class T>
T *NodeS<T>::getItem()
{
	return item;
} // end getItem

template<class T>
NodeS<T>* NodeS<T>::getNext()
{
	return next;
} // end getNext