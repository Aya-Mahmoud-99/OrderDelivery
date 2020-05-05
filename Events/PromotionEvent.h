#include "Event.h"
class PromotionEvent :public Event {
private:
	double money;
public:
	PromotionEvent(int eTime, int oID, int mon);
	virtual void Execute(Restaurant* pRest);
	virtual void Load(Restaurant* pRest, fstream& myfile);
	PromotionEvent();
};