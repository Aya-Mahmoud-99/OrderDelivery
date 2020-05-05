#ifndef __MOTORCYCLE_H_
#define __MOTORCYCLE_H_
#include"Order.h"


#include "..\Defs.h"

#pragma once
class Motorcycle	
{
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding motorcycle type 
	int speed;		//meters it can move in one clock tick (in one timestep)
	REGION	region;	//region of the motorcycle
	STATUS	status;	//idle or in-serve
	Order*o;

public:
	Motorcycle();
	void settype(ORD_TYPE);
	void setregion(REGION);
	void setspeed(int s);
	int getspeed();
	void setstatus(STATUS s);
	bool operator >(Motorcycle m);
	bool operator<(Motorcycle m);
	bool operator==(Motorcycle m);
	virtual ~Motorcycle();
	STATUS Getstatus();
	void setorder(Order*l);
	Order* getorder();
	void setid(int);
	ORD_TYPE gettype();
	int getid();
};

#endif