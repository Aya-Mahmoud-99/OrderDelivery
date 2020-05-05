#include "Event.h"


Event::Event(int eTime, int ordID)
{
	EventTime = eTime;
	OrderID	= ordID;
}


int Event::getEventTime()
{
	return EventTime;
}
/*int Event::setEventTime(int t)
{
	EventTime=t;
}*/
int Event::getOrderID()
{
	return OrderID;
}


Event::~Event()
{

}
Event* Event::getthis(){
	return this;
}
