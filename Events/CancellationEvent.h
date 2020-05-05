#include "Event.h"
#include "..\Rest\Restaurant.h"
#include<iostream>
using namespace std;
class CancellationEvent:public Event{

public:
	CancellationEvent(int eTime, int oID);	
	void Execute(Restaurant*Ptr);
	virtual void Load(Restaurant* pRest,fstream& myfile);
	CancellationEvent(){};
};
