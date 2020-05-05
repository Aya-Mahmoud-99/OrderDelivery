#ifndef __ARRIVAL_EVENT_H_
#define __ARRIVAL_EVENT_H_
#include "Event.h"
//class for the arrival event
class ArrivalEvent: public Event
{
	//info about the order ralted to arrival event
	int OrdDistance;	//order distance
	ORD_TYPE OrdType;		//order type: Normal, Frozen, VIP
	REGION OrdRegion;  //Region of this order	                
	double OrdMoney;	//Total order money
public:
	ArrivalEvent(int eTime, int oID, ORD_TYPE oType, REGION reg);
	ArrivalEvent(){};
	//Add more constructors if needed
	void setdistance(int);
	virtual void Execute(Restaurant *pRest);	//override execute function
	void setmoney(double mon);
	virtual void Load(Restaurant* pRest,fstream& myfile);
};

#endif