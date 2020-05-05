#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Generic_DS\bag.h"
#include "..\Generic_DS\PriorityQueue.h"
#include"..\Generic_DS\LinkedListS.h"
#include "..\Events\Event.h"
#include "..\Rest\Motorcycle.h"
#include<fstream>
#include <string>
#include "Order.h"
#include <iostream>
using namespace std;
// it is the maestro of the project
struct region
{
	int noofservedorders;
	int noofservednormal;
	int noofservedvip;
	int noofservedfrozen;
	int noofnormalmotor;
	int nooffastmotor;
	int nooffrozenmotor;
	REGION id;
	int CountOfOrders;
	int noofnormalorders;
	int noofviporders;
	int nooffrozenorders;
	int noofmotorcycles;
	int avwaitingtime;
	int avservingtime;
	int noofavmoto;

	LinkedListS<Motorcycle> normalmotor;
	LinkedListS<Motorcycle> fastmotor;
	LinkedListS<Motorcycle> frozenmotor;
	PriorityQueue<Order*> viporders;
	Queue<Order*> frozenorders;
	Queue<Order*> normalorders;
	LinkedListS<Order>  beingserved;
	LinkedListS<Order> served;
	LinkedListS<Order> AfterS;
	int countoffrozen;
	int countofnoraml;
	int countofvip;
		region(REGION R,int normal,int frozen,int vip,fstream& myfile)
		{ noofservedorders=0;
		noofservednormal=0;
		noofservedfrozen=0;
		noofservedvip=0;
			noofnormalorders = 0;
			noofviporders = 0;
			nooffrozenorders = 0;
			R=id;
			CountOfOrders=0;
			countoffrozen=frozen;
			countofnoraml=normal;
			countofvip=vip;
			noofnormalmotor=normal;
			for(int i=0;i<normal;i++)
			{
			int Id,normspeed;
			myfile>>normspeed;
			myfile>>Id;
		Motorcycle* p;
		p=new Motorcycle;
		p->setid(Id);
		p->settype(TYPE_NRM);
		p->setregion(id);
		p->setspeed(normspeed);
		p->setstatus(IDLE);
		normalmotor.Insert(*p);
			}
			nooffrozenmotor=frozen;
				for(int i=0;i<frozen;i++)
				{
					int Id, frozspeed;
					myfile>>Id;
					myfile>>frozspeed;
		Motorcycle* p;
		p=new Motorcycle;
		p->setid(Id);
		p->settype(TYPE_FROZ);
		p->setspeed(frozspeed);
		p->setregion(id);
		p->setstatus(IDLE);
	    frozenmotor.Insert(*p);
			}
				nooffastmotor=vip;
for(int i=0;i<vip;i++){
	int Id, vipspeed;
	myfile>>Id;
	myfile>>vipspeed;
		Motorcycle* p;
		p=new Motorcycle;
		p->settype(TYPE_VIP);
		p->setspeed(vipspeed);
		p->setid(Id);
		p->setregion(id);
	    p->setstatus(IDLE);
		fastmotor.Insert(*p);
			}
		}
		void increment()
		{
			CountOfOrders++;
		}
		void decrement()
		{
			CountOfOrders--;
		}
		bool assignmotorcycle(Order*o, Motorcycle* m,int currenttimestep,GUI* PGUI)
		{
			cout<<"statusb4"<<m->Getstatus()<<endl;
			if (m->Getstatus() == IDLE)
			{
				m->setorder(o);
				m->setstatus(SERV);
				cout<<"statusafter"<<m->Getstatus()<<endl;
				o->calculatewaitingtime(currenttimestep);
				o->calculatefinishtime(m->getspeed());
				if(m->gettype()==TYPE_NRM) countofnoraml--;
					if(m->gettype()==TYPE_VIP) countofvip--;
					if(m->gettype()==TYPE_FROZ) countoffrozen--;
					beingserved.Insert(*o);
					string typeofmotorcycle;
				string	motorcycleid=to_string(m->getid());
					string ordertype;
					string orderid=to_string(o->GetID());

	switch (m->gettype())	//Add a function for each mode in next phases
	{
	case TYPE_NRM:
		typeofmotorcycle="N";
		break;
	case TYPE_FROZ:
		typeofmotorcycle="F";
		break;
	case TYPE_VIP:
      typeofmotorcycle="V";
		break;
};
	switch (o->GetType())	//Add a function for each mode in next phases
	{
	case TYPE_NRM:
		ordertype="N";
		break;
	case TYPE_FROZ:
		ordertype="F";
		break;
	case TYPE_VIP:
      ordertype="V";
		break;
};
	PGUI->PrintMessage(typeofmotorcycle+motorcycleid+"("+ordertype+orderid+")");
		Sleep(600);
				return true;
			}
  return false;
		}
		 void deassignmotorcycle(int currenttimestep,Motorcycle* m){
			if(m->Getstatus()==SERV){
				Order* o=m->getorder();
				if(o->getfinishingtime()+o->getServedTime()<=currenttimestep){
					served.Insert(*o);
					m->setstatus(IDLE);
					m->setorder(NULL);
					if(m->gettype()==TYPE_NRM) countofnoraml++;
					if(m->gettype()==TYPE_VIP) countofvip++;
					if(m->gettype()==TYPE_FROZ) countoffrozen++;
				}
			}
		}
		void assignnormal(int currenttimestep,GUI* PGUI){
			Order*p;
			while (normalorders.peekFront(p))
			{
				bool assignedonce = false;
				Motorcycle** arr1;
				int count1;
				normalmotor.tooArray(arr1, count1);
				int i = 0;
				cout <<"count1"<<count1 << endl;
				while (i < count1 && !assignedonce) {
					cout << "i" << i << endl;
					bool assigned = assignmotorcycle(p, arr1[i], currenttimestep,PGUI);
					if (assigned) {
						cout << "assigned" << assigned << endl;
						normalorders.dequeue(p);
						assignedonce = true;
					}
					i++;
				}
				Motorcycle** arr2;
				int count2;
				fastmotor.tooArray(arr2, count2);
				int j = 0;
				cout << "count2"<<count2<<endl;
				while (j < count2 && !assignedonce) {

					bool assigned = assignmotorcycle(p, arr2[j], currenttimestep,PGUI);
					if (assigned) {
						cout << "assigned" << assigned << endl;
						normalorders.dequeue(p);
						assignedonce = true;
					}
					j++;
				}
				if (!assignedonce) break;
			}

		}

		void assignvip(int currenttimestep,GUI* PGUI){
			Order*p;
			while (viporders.peek(p))
			{
				bool assignedonce = false;
				Motorcycle** arr1;
				int count1;
				fastmotor.tooArray(arr1, count1);
				int i = 0;
				while (i < count1 && !assignedonce) {
					cout << "i" << i << endl;
					bool assigned = assignmotorcycle(p, arr1[i], currenttimestep,PGUI);
					if (assigned) {
						cout << "assigned" << assigned << endl;
						viporders.dequeue(p);
						assignedonce = true;
					}
					i++;
				}
				Motorcycle** arr2;
				int count2;
				normalmotor.tooArray(arr2, count2);
				int j = 0;
				while (j < count2 && !assignedonce) {

					bool assigned = assignmotorcycle(p, arr2[j], currenttimestep,PGUI);
					if (assigned) {
						cout << "assigned" << assigned << endl;
						viporders.dequeue(p);
						assignedonce = true;
					}
					j++;
				}
				Motorcycle** arr;
				int count;
				frozenmotor.tooArray(arr, count);
				int k = 0;
				while (k < count && !assignedonce) {

					bool assigned = assignmotorcycle(p, arr[k], currenttimestep,PGUI);
					if (assigned) {
						cout << "assigned" << assigned << endl;
						viporders.dequeue(p);
						assignedonce = true;
					}
					k++;
				}
				if (!assignedonce) break;
			}
		}
		void assginmotorcyces(int currenttimestep,GUI* PGUI){
			assignvip(currenttimestep,PGUI);
			assignfrozen(currenttimestep,PGUI);
			assignnormal(currenttimestep,PGUI);
		}
		void assignfrozen(int currenttimestep,GUI* PGUI )
		{
			Order*p;
			while (frozenorders.peekFront(p))
			{
							bool assignedonce=false;
				 //loop on frozen motorcycle only
				Motorcycle** arr;
				int count;
				//cout<<"xxxxx"<<endl;
					frozenmotor.tooArray(arr,count);
					//cout<<"yyyy"<<endl;
					//cout<<id<<endl;
					cout<<"count"<<count<<endl;
				int i=0;
				while(i<count&&!assignedonce){
					cout<<"i"<<i<<endl;
					bool assigned=assignmotorcycle(p,arr[i],currenttimestep,PGUI);
					if(assigned){
						cout<<"assigned"<<assigned<<endl;
						frozenorders.dequeue(p);
						assignedonce=true;
					}
					i++;
				}
				if(!assignedonce) break;
				//then check if the motorcycle status and the order to the motorcycle
			}
		}
	void DeassignallMotorcycle(int currenttime)
	{
		Motorcycle**M;
		int count;
		fastmotor.tooArray(M, count);
		for (int i = 0; i < count; i++)
		{
			deassignmotorcycle(currenttime, M[i]);
		}
		Motorcycle**M2;
		int count2;
		normalmotor.tooArray(M2, count2);
		for (int i = 0; i < count2; i++)
		{
			deassignmotorcycle(currenttime, M2[i]);
		}
		Motorcycle**M3;
		int count3;
		frozenmotor.tooArray(M3, count3);
		for (int i = 0; i < count3; i++)
		{
			deassignmotorcycle(currenttime, M3[i]);
		}
 }
	void checkforservedorders(int currenttimestep){
		/*Order** orders;
		int count;
		beingserved.tooArray(orders,count);
		for(int i=0;i<count;i++){
			if(orders[i]->getfinishingtime()<currenttimestep){

			}
		}*/
		Order* o;
		while(beingserved.getfirst(o)){
			if(o->getfinishingtime()<currenttimestep){
				beingserved.remove(o);
					switch (o->GetType())	//Add a function for each mode in next phases
	{
	case TYPE_NRM:
		noofservednormal++;
		break;
	case TYPE_FROZ:
		noofservedfrozen++;
		break;
	case TYPE_VIP:
     noofservedvip++;
		break;
};
			}
			else{
				break;
			}
		}

	}	 
};

class Restaurant  
{	
private:
	GUI *pGUI;
	Queue<Event*> EventsQueue;	
	int noofcancellationevents;
	int noofpromotionevents;
	int noofarrivalevents;
	int noofordersshouldbeserved;
	//Queue of all events that will be loaded from file
	//Aya list for motorcycles
	//Aya list for orders
	//Queue<Motorcycle*> motorcycles;
	//Queue<Order*> activeorders;#include "..\Rest\region.h"
	/// ==> 
	//	DEMO-related members. Should be removed in phases 1&2
	Queue<Order*> DEMO_Queue;	//Important: This is just for demo
	/// ==>
	
	//
	// TODO: Add More Data Members As Needed
	//

	int autopromotion;
	region* regions[4];
public:
	Restaurant();
	~Restaurant();
	void AddEvent(Event* pE);	//adds a new event to the queue of events
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();

	/// ==> 
	///  DEMO-related functions. Should be removed in phases 1&2
	//void Just_A_Demo();	//just to show a demo and should be removed in phase1 1 & 2
	void AddtoDemoQueue(Order* po);	//adds an order to the demo queue
	Order* getDemoOrder();			//return the front order from demo queue
	/// ==> 
	void simplesimulator();
	void  StepSim();
	void silent();
    void loadfunction();
	void AddOrder(Order*O);
	void Cancel(int id);
	void Promote(int id, double money);
	void autopromote(int currenttimestep);
	int AddQueueForDrawing(Queue<Order*>);
	int AddPriorityQueue(PriorityQueue<Order*>);
	GUI* getgui();
	//void allServed(Order*);
	//
	// TODO: Add More Member Functions As Needed
	//

};

#endif