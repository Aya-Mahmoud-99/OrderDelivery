#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"
#include<iostream>
using namespace std;

ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType, REGION reg):Event(eTime, oID)
{
	OrdType = oType;
	OrdRegion = reg;
}

void ArrivalEvent::setdistance(int d){
	OrdDistance=d;
};

void ArrivalEvent::Execute(Restaurant* pRest)
{
	//This function should create and order and and fills its data 
	// Then adds it to normal, frozen, or VIP order lists that you will create in phase1

	
	
	///For the sake of demo, this function will just create an order and add it to DemoQueue
	///Remove the next code lines in phase 1&2
	Order* pOrd = new Order(OrderID,OrdType,OrdRegion);
	pOrd->setarrivaltime(Event::EventTime);
	pOrd->SetDistance(OrdDistance);
	//pRest->AddtoDemoQueue(pOrd);
	pRest->AddOrder(pOrd);
	//pRest->AddtoDemoQueue(pOrd);
	//pRest->getgui()->AddOrderForDrawing(pOrd);
	//delete pOrd;
	//ADD to orders list
}
void ArrivalEvent::setmoney(double mon){
	OrdMoney=mon;
}
 void ArrivalEvent::Load(Restaurant* pRest,fstream& myfile){
	 	int TS;
			myfile>>TS;
			string b;
			ORD_TYPE type;
			myfile>>b;
			if(b=="N") type=TYPE_NRM;
			if(b=="V") type=TYPE_VIP;
		    if(b=="F") type=TYPE_FROZ;
			int id;
			myfile>>id;
			int dst;
			myfile>>dst;
			int money;
			myfile>>money;
			string c;
			REGION REG;
			myfile>>c;
			if(c=="A") REG=A_REG;
			if(c=="B") REG=B_REG;
		    if(c=="C") REG=C_REG;
			if(c=="D") REG=D_REG;
			EventTime=TS;
			OrderID=id;
			OrdType=type;
			OrdRegion=REG;
			OrdDistance=dst;
			OrdMoney=money;
       pRest->AddEvent(getthis());
	   cout<<money<<endl;
}