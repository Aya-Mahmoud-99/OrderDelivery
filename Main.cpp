#include "Rest\Restaurant.h"
#include "GUI\GUI.h"

int main()
{
	Restaurant* pRest = new Restaurant;
	//pRest->loadfunction();
	pRest->RunSimulation();
	delete pRest;

	
	return 0;
}
