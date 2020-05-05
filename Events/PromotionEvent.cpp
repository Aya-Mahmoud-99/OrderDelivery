#include"PromotionEvent.h"
#include "..\Rest\Restaurant.h"
PromotionEvent::PromotionEvent(int eTime, int oID, int mon) :Event(eTime, oID) {
	money = mon;
}
PromotionEvent::PromotionEvent() {
}
void PromotionEvent::Load(Restaurant* pRest, fstream& myfile) {
	int time;
	myfile >> time;
	int id;
	myfile >> id;
	int mon;
	myfile >> mon;
	EventTime = time;
	OrderID = id;
	money = mon;
	pRest->AddEvent(getthis());
	cout<<money<<endl;
}

void PromotionEvent::Execute(Restaurant *Ptr)
{
	int ID = Event::OrderID;
	Ptr->Promote(ID, money);
	cout << "event is promoted" << endl;

}


