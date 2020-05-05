#include"CancellationEvent.h"
#include "..\Rest\Restaurant.h"
CancellationEvent::CancellationEvent(int eTime, int oID):Event(eTime,oID){
}

void CancellationEvent::Load(Restaurant* pRest,fstream& myfile){
	 int time;
		  myfile>>time;
		  int id;
		  myfile>>id;
		 EventTime=time;
		 OrderID=id;
		   pRest->AddEvent(getthis());
		   cout<<id<<endl;
}
void CancellationEvent::Execute(Restaurant*Ptr)
{
	int id=Event::OrderID;
	Ptr->Cancel(id);	
}