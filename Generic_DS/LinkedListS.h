#pragma once
#include<iostream>
using namespace std;
#include "NodeS.h"

template<class T>
class LinkedListS
{
private:
	NodeS<T> *Head;
	int count;
public:
	LinkedListS();
	void PrintList();
	bool Insert(T &data);
	bool remove(T *&data);
	void tooArray(T**& bagContents,int & counter);
	int getcount();
	bool getfirst(T*& data);
};


template<class T>
LinkedListS<T>::LinkedListS()
{
	count = 0;
	Head = NULL;
}

template<class T>
void LinkedListS<T>::PrintList()
{
	cout << "\nList has " << count << " nodes";
	cout << "\nprinting list contents:\n\n";
	NodeS<T> *p = Head;

	while (p != NULL)
	{
		cout << "[ " << *(p->getItem()) << " ]";
		cout << "--->";
		p = p->getNext();
	}
	cout << "*\n";
}

template<class T>
bool LinkedListS<T>::Insert(T &data)
{
	if (Head == NULL)
	{
		Head = new NodeS<T>;
		Head->setItem(&data);
		Head->setNext(NULL);
		count++;
		return true;
	}
	else if (Head->getNext() == NULL)
	{
		NodeS<T>*temp = new NodeS<T>;
		temp->setItem(&data);
		if (data < *(Head->getItem()))
		{
			temp->setNext(Head);
			Head = temp;
			count++;
			return true;
		}
		else
		{
			temp->setNext(NULL);
			Head->setNext(temp);
			count++;
			return true;
		}
	}
	else
	{
		NodeS<T>*current = Head;
		while (current->getNext() != NULL)
		{
			if (*(Head->getItem()) > data)
			{
				NodeS<T>*temp = new NodeS<T>;
				temp->setItem(&data);
				temp->setNext(Head);
				Head = temp;
				count++;
				return true;
			}
			else if (*(current->getNext()->getItem()) > data)
			{
				NodeS<T>*temp = new NodeS<T>;
				temp->setItem(&data);
				temp->setNext(current->getNext());
				current->setNext(temp);
				count++;
				return true;
			}
			else
			{
				current = current->getNext();
			}
		}
		NodeS<T>*temp = new NodeS<T>;
		temp->setItem(&data);
		temp->setNext(NULL);
		current->setNext(temp);
		count++;
		return true;
	}
}

template<class T>
bool LinkedListS<T>::remove(T *&data)
{  
	//if(count==0) return false;
//	cout<<"a"<<endl;
	if (Head == NULL)
	{
	//	cout<<"b"<<endl;
		return false;
	}
	else
	{
	//	cout<<"d"<<endl;
		data = Head->getItem();
	//	cout<<"e"<<endl;
		//NodeS<T> *temp = Head;
		//cout<<"f"<<endl;
		Head=Head->getNext();
		//cout<<"g"<<endl;
	//	delete temp;
	//	cout<<"h"<<endl;
		count--;
		
		return true;
	//	cout<<"j"<<endl;
	}
}

template<class T>
void LinkedListS<T>::tooArray(T**& bagContents,int & counter){
	bagContents=new T*[count];
	//cout<<"aaaaaa"<<endl;
	NodeS<T> * temp=Head;
	//cout<<"omar"<<endl;
	counter=0;
	//cout<<"bbbbbb"<<endl;
	while(temp){
		//cout<<"nnnn"<<endl;
		bagContents[counter++]=temp->getItem();
		//cout<<"mmm"<<endl;
		temp=temp->getNext();
		//cout<<"zzzzzz"<<endl;
	}
	//cout<<"ooooo"<<endl;
}
template<class T>
int LinkedListS<T>::getcount(){
	return count;
}
template<class T>
bool  LinkedListS<T>::getfirst(T*& first){
	if(Head==NULL) return false;
	first = Head->getItem();
	return true;
}