#ifndef __EVENT_H_
#define __EVENT_H_

#include "..\Defs.h"
#include<iostream>
using namespace std;
class Restaurant;	//Forward declation

//The base class for all possible events in the system (abstract class)
class Event
{
protected:
	int EventTime;	//Timestep when this event takes place
	int OrderID;	//each event is related to certain order
public:
	Event(int eTime, int ordID);
	int getEventTime();
	int getOrderID();
	virtual ~Event();
	//int setEventTime(int);
	Event(){};

	virtual void Execute(Restaurant* pRest)=0;	////a pointer to "Restaurant" and events need it to execute
	virtual void Load(Restaurant* pRest,fstream& myfile)=0;
	Event* getthis();
};


#endif