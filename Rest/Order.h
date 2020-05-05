#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"

class Order
{

protected:
	int ID;         //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		//order type: Normal, Frozen, VIP
	REGION Region;  //Region of this order
	int Distance;	//The distance (in meters) between the order location and the resturant 
	                
	double totalMoney;	//Total order money

	int ArrTime, ServTime, FinishTime;	//arrival, service start, and finish times
	int waitingtime;

	
	//
	// TODO: Add More Data Members As Needed
	//

public:
	Order(int ID, ORD_TYPE r_Type, REGION r_region);
	Order();
	virtual ~Order();

	int GetID();

	int GetType() const;
	REGION GetRegion() const;
	void setarrivaltime(int);
	void SetDistance(int d);
	int GetDistance() const;
	double GetTotalMoney()const;
	int GetArrivalTime()const;
	void calculatefinishtime(int);
	int getfinishingtime();
	void calculatewaitingtime(int);
	void setOrderType(int n);
	void setTotalMoney(double n);
	int getWaitingTime();
	int getServedTime();
	bool operator<(Order);
	bool operator>(Order);
	//
	// TODO: Add More Member Functions As Needed
	//

};

#endif