#include "Order.h"
#include<iostream>
using namespace std;
Order::Order(int id, ORD_TYPE r_Type, REGION r_region)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	Region = r_region;	
}

Order::Order()
{

}

Order::~Order()
{
     
}

int Order::GetID()
{
	cout<<"ID "<<ID<<endl;
	return ID;
}


int Order::GetType() const
{
	return type;
}

REGION Order::GetRegion() const
{
	return Region;
}

void Order::SetDistance(int d)
{
	Distance = d>0?d:0;
}

int Order::GetDistance() const
{
	return Distance;
}
double Order::GetTotalMoney()const
{
	return totalMoney;
}
int Order::GetArrivalTime()const
{
	cout<<"ARR "<<ArrTime<<endl;
	return ArrTime;
}
void Order::calculatefinishtime(int speed){
	ServTime=Distance/speed;
	cout<<"distance "<<Distance<<endl;
	cout<<"speed "<<speed<<endl;
	cout<<"Servtime "<<ServTime<<endl;
	FinishTime=ServTime+waitingtime+ArrTime;
	cout<<FinishTime<<endl;
}
int Order::getfinishingtime(){
	cout<<"finish time "<<FinishTime<<endl;
	return FinishTime;
}
void Order::calculatewaitingtime(int currenttime){
	cout<<"current timestep "<<currenttime<<endl;
	waitingtime=currenttime-ArrTime;
	cout<<"waiting time "<<waitingtime<<endl;
}

int Order::getServedTime()
{
	cout<<"serv time"<<ServTime;
	return ServTime;
}

int Order::getWaitingTime()
{
	cout<<"waiting time "<<waitingtime<<endl;
	return waitingtime;
}

void Order::setOrderType(int n)
{
	if (n == 1)
		type = TYPE_NRM;

	if (n == 2)
		type = TYPE_FROZ;

	if (n == 3)
		type = TYPE_VIP;

}

void Order::setTotalMoney(double n)
{
	totalMoney = n;
}

bool Order::operator<(Order O)
{
	if (FinishTime < O.FinishTime)
	{
		return true;
	}
	else if (FinishTime > O.FinishTime)
	{
		return false;
	}
	else if (FinishTime == O.FinishTime)
	{
		if (ServTime < O.ServTime)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool Order::operator>(Order O)
{
	if (FinishTime > O.FinishTime)
	{
		return true;
	}
	else if (FinishTime < O.FinishTime)
	{
		return false;
	}
	else if (FinishTime == O.FinishTime)
	{
		if (ServTime > O.ServTime)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
void Order::setarrivaltime(int arrtime){
	ArrTime=arrtime;
}