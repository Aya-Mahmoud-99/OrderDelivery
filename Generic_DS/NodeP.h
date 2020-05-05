#pragma once
#include<iostream>
using namespace std;

template<class T>
class NodeP
{
	T data;
	int pir;
	NodeP<T>* next;
public:
	NodeP<T>()
	{
		next = NULL;
	}
	void setData(T it)
	{
		data = it;
	}
	void setNext(NodeP<T>* n)
	{
		next = n;
	}
	T getData()
	{
		return data;
	}
	NodeP<T>* getNext()
	{
		return next;
	}
	void setPir(int pr)
	{
		pir = pr;
	}
	int getPir()
	{
		return pir;
	}

};