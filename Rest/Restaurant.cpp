#include <cstdlib>
#include <time.h>

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include"..\Events\CancellationEvent.h"
#include"..\Events\PromotionEvent.h"
#include<fstream>

Restaurant::Restaurant()
{
	pGUI = NULL;
	noofarrivalevents = 0;
	noofcancellationevents = 0;
	noofpromotionevents = 0;
	noofordersshouldbeserved = 0;
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();

	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		simplesimulator();
		break;
	case MODE_STEP:
		StepSim();
		break;
	case MODE_SLNT:
		silent();
		break;


	};

}



//////////////////////////////////  Event handling functions   /////////////////////////////
void Restaurant::AddEvent(Event* pE)	//adds a new event to the queue of events
{
	EventsQueue.enqueue(pE);
}

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while (EventsQueue.peekFront(pE))	//as long as there are more events
	{
		if (pE->getEventTime() > CurrentTimeStep)	//no more events at current time
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}


Restaurant::~Restaurant()
{
	delete pGUI;
}




////////////////////////////////////////////////////////////////////////////////
/// ==> 
///  DEMO-related functions. Should be removed in phases 1&2

//This is just a demo function for project introductory phase
//It should be removed starting phase 1

void Restaurant::simplesimulator()
{
	loadfunction();
	int EventCnt;
	Order* pOrd;
	int counts[4] = { 0,0,0,0 };
	int count[4] = { 0,0,0,0 };
	/*pGUI->PrintMessage("Enter EVENTS Count(next phases should read I/P filename):");
	EventCnt = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer*/
	pGUI->UpdateInterface();

	//pGUI->PrintMessage("Generating orders randomly... In next phases, orders should be loaded from a file");

	//int EvTime = 0;

	//Create Random events
	//All generated event will be "ArrivalEvents" for the demo


	int CurrentTimeStep = 1;
	//as long as events queue is not empty yet
	Event *x;
	int countofservedorders = 0;
	while (countofservedorders < noofordersshouldbeserved)
	{ int y=1;
		cout<<"xxx"<<endl;
		ExecuteEvents(CurrentTimeStep);

		for (int i = 0; i < 4; i++) {
			int x = AddPriorityQueue(regions[i]->viporders);
			int y = AddQueueForDrawing(regions[i]->frozenorders);
			int z = AddQueueForDrawing(regions[i]->normalorders);
			counts[i] = x + y + z;
			count[i] = regions[i]->served.getcount();
		}
		countofservedorders = count[0] + count[1] + count[2] + count[3];
		pGUI->UpdateInterface();
		Sleep(500);
		for (int i = 0; i < 4; i++)
		{
			pGUI->ClearStatusBar();
			string str1 = to_string(counts[i]);
			string str2 = to_string(regions[i]->countofvip);
			string str3 = to_string(regions[i]->countofnoraml);
			string str4 = to_string(regions[i]->countoffrozen);
			string str5=to_string(regions[i]->noofservednormal);
			string str6=to_string(regions[i]->noofservedfrozen);
			string str7=to_string(regions[i]->noofservedvip);
			pGUI->PrintMessage("number of active order in this region is:" + str1,y++);
			//Sleep(600);
			pGUI->PrintMessage("number of available VIP motorcycle is:" + str2,y++);
			//Sleep(600);
			pGUI->PrintMessage("number of available Normal motorcycle is:" + str3,y++);
			//Sleep(600);
			pGUI->PrintMessage("number of available Frozen motorcycle is:" + str4,y++);
			//Sleep(600);
			pGUI->PrintMessage("number of served normal orders:" + str5,y++);
			//Sleep(600);
			pGUI->PrintMessage("number of served frozen orders:" + str6,y++);
			//Sleep(600);
			y=1;
			Sleep(2000);
			pGUI->ClearStatusBar();
			pGUI->PrintMessage("number of served vip orders" + str7,y++);
			Sleep(600);
			cout << "region" << i << endl;
			regions[i]->checkforservedorders(CurrentTimeStep);
			regions[i]->DeassignallMotorcycle(CurrentTimeStep);
			Sleep(600);
			regions[i]->assginmotorcyces(CurrentTimeStep,pGUI);
			y=1;
		}
		pGUI->UpdateInterface();
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep, timestep, 10);
		pGUI->PrintMessage(timestep);


		//execute all events at current time step
		//The above line may add new orders to the DEMO_Queue

		//Let's draw all arrived orders by passing them to the GUI to draw

		pGUI->UpdateInterface();
		Sleep(1000);
		CurrentTimeStep++;
		pGUI->waitForClick();
		//advance timestep
		pGUI->ResetDrawingList();

	}
	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();

	cout << "a" << endl;
	ofstream out;
	out.open("output.txt");
	out << "Region A" << endl;
	Order *O;
	out << "FT ID AT WT ST" << endl;
	float sumofwaiting1 = 0;
	int countoforderss1 = 0;
	float sumofserving1 = 0;
	float AvgWait1;
	float AvgServ1;
	int FT1, ID1, AT1, WT1, ST1;

	float sumofwaiting2 = 0;
	int countoforderss2 = 0;
	float sumofserving2 = 0;
	float AvgWait2;
	float AvgServ2;
	int FT2, ID2, AT2, WT2, ST2;


	float sumofwaiting3 = 0;
	int countoforderss3 = 0;
	float sumofserving3 = 0;
	float AvgWait3;
	float AvgServ3;
	int FT3, ID3, AT3, WT3, ST3;



	float sumofwaiting4 = 0;
	int countoforderss4 = 0;
	float sumofserving4 = 0;
	float AvgWait4;
	float AvgServ4;
	int FT4, ID4, AT4, WT4, ST4;

	int FTr, IDr, ATr, WTr, STr;



	while (regions[0]->served.remove(O))
	{
		regions[0]->AfterS.Insert(*O);
		sumofwaiting1 = O->getWaitingTime() + sumofwaiting1;
		sumofserving1 = sumofserving1 + O->getServedTime();
		countoforderss1++;
		FT1 = O->getfinishingtime();
		ID1 = O->GetID();
		AT1 = O->GetArrivalTime();
		WT1 = O->getWaitingTime();
		ST1 = O->getServedTime();


		out << FT1 << " " << ID1 << " " << AT1 << " " << WT1 << " " << ST1 << endl;
		switch (O->GetType())
		{
		case 0:
		{
			regions[0]->noofnormalorders++;
			break;
		}
		case 1:
		{
			regions[0]->nooffrozenorders++;
			break;
		}
		case 2:
		{
			regions[0]->noofviporders++;
			break;
		}
		}
	}
	AvgWait1 = sumofwaiting1 / countoforderss1;
	AvgServ1 = sumofserving1 / countoforderss1;
	out << "orders: " << regions[0]->CountOfOrders << " [Norm: " << regions[0]->noofnormalorders;
	out << " Froz: " << regions[0]->nooffrozenorders << " VIP: " << regions[0]->noofviporders << "]" << endl;
	int tot1 = (regions[0]->countoffrozen) + (regions[0]->countofnoraml) + (regions[0]->countofvip);
	out << "MotorC: " << tot1 << " [Norm: " << regions[0]->countofnoraml << " Froz: " << regions[0]->countoffrozen;
	out << " VIP: " << regions[0]->countofvip << "]" << endl;
	out << "Avg wait = " << AvgWait1;
	out << ", Avg Serv = " << AvgServ1 << endl;
	out << endl;

	out << endl;
	out << "Region B" << endl;
	out << "FT ID AT WT ST" << endl;

	while (regions[1]->served.remove(O))
	{
		regions[1]->AfterS.Insert(*O);
		sumofwaiting2 = O->getWaitingTime() + sumofwaiting2;
		sumofserving2 = sumofserving2 + O->getServedTime();
		countoforderss2++;
		FT2 = O->getfinishingtime();
		ID2 = O->GetID();
		AT2 = O->GetArrivalTime();
		WT2 = O->getWaitingTime();
		ST2 = O->getServedTime();


		out << FT2 << " " << ID2 << " " << AT2 << " " << WT2 << " " << ST2 << endl;
		switch (O->GetType())
		{
		case 0:
		{
			regions[1]->noofnormalorders++;
			break;
		}
		case 1:
		{
			regions[1]->nooffrozenorders++;
			break;
		}
		case 2:
		{
			regions[1]->noofviporders++;
			break;
		}
		}
	}
	AvgWait2 = sumofwaiting2 / countoforderss2;
	AvgServ2 = sumofserving2 / countoforderss2;
	out << "orders: " << regions[1]->CountOfOrders << " [Norm: " << regions[1]->noofnormalorders;
	out << " Froz: " << regions[1]->nooffrozenorders << " VIP: " << regions[1]->noofviporders << "]" << endl;
	int tot2 = (regions[1]->countoffrozen) + (regions[1]->countofnoraml) + (regions[1]->countofvip);
	out << "MotorC: " << tot2 << " [Norm: " << regions[1]->countofnoraml << " Froz: " << regions[1]->countoffrozen;
	out << " VIP: " << regions[1]->countofvip << "]" << endl;
	out << "Avg wait = " << AvgWait2;
	out << ", Avg Serv = " << AvgServ2 << endl;

	out << endl;
	out << "Region C" << endl;
	out << "FT ID AT WT ST" << endl;


	while (regions[2]->served.remove(O))
	{
		regions[2]->AfterS.Insert(*O);
		sumofwaiting3 = O->getWaitingTime() + sumofwaiting3;
		sumofserving3 = sumofserving3 + O->getServedTime();
		countoforderss3++;
		FT3 = O->getfinishingtime();
		ID3 = O->GetID();
		AT3 = O->GetArrivalTime();
		WT3 = O->getWaitingTime();
		ST3 = O->getServedTime();


		out << FT3 << " " << ID3 << " " << AT3 << " " << WT3 << " " << ST3 << endl;
		switch (O->GetType())
		{
		case 0:
		{
			regions[2]->noofnormalorders++;
			break;
		}
		case 1:
		{
			regions[2]->nooffrozenorders++;
			break;
		}
		case 2:
		{
			regions[2]->noofviporders++;
			break;
		}
		}
	}
	AvgWait3 = sumofwaiting3 / countoforderss3;
	AvgServ3 = sumofserving3 / countoforderss3;
	out << "orders: " << regions[0]->CountOfOrders << " [Norm: " << regions[0]->noofnormalorders;
	out << " Froz: " << regions[0]->nooffrozenorders << " VIP: " << regions[0]->noofviporders << "]" << endl;
	int tot3 = (regions[2]->countoffrozen) + (regions[2]->countofnoraml) + (regions[2]->countofvip);
	out << "MotorC: " << tot3 << " [Norm: " << regions[2]->countofnoraml << " Froz: " << regions[2]->countoffrozen;
	out << " VIP: " << regions[2]->countofvip << "]" << endl;
	out << "Avg wait = " << AvgWait3;
	out << ", Avg Serv = " << AvgServ3 << endl;
	out << endl;

	out << "Region D" << endl;
	out << "FT ID AT WT ST" << endl;


	while (regions[3]->served.remove(O))
	{
		regions[3]->AfterS.Insert(*O);
		sumofwaiting4 = O->getWaitingTime() + sumofwaiting4;
		sumofserving4 = sumofserving4 + O->getServedTime();
		countoforderss4++;
		FT4 = O->getfinishingtime();
		ID4 = O->GetID();
		AT4 = O->GetArrivalTime();
		WT4 = O->getWaitingTime();
		ST4 = O->getServedTime();


		out << FT4 << " " << ID4 << " " << AT4 << " " << WT4 << " " << ST4 << endl;
		switch (O->GetType())
		{
		case 0:
		{
			regions[3]->noofnormalorders++;
			break;
		}
		case 1:
		{
			regions[3]->nooffrozenorders++;
			break;
		}
		case 2:
		{
			regions[3]->noofviporders++;
			break;
		}
		}
	}
	AvgWait4 = sumofwaiting4 / countoforderss4;
	AvgServ4 = sumofserving4 / countoforderss4;
	out << "orders: " << regions[3]->CountOfOrders << " [Norm: " << regions[3]->noofnormalorders;
	out << " Froz: " << regions[3]->nooffrozenorders << " VIP: " << regions[3]->noofviporders << "]" << endl;
	int tot4 = (regions[3]->countoffrozen) + (regions[3]->countofnoraml) + (regions[3]->countofvip);
	out << "MotorC: " << tot4 << " [Norm: " << regions[3]->countofnoraml << " Froz: " << regions[3]->countoffrozen;
	out << " VIP: " << regions[3]->countofvip << "]" << endl;
	out << "Avg wait = " << AvgWait4;
	out << ", Avg Serv = " << AvgServ4 << endl;

	out << endl;
	out << "Whole Restaurant" << endl;
	out << "FT ID AT WT ST" << endl;


	int totOrder = 0;
	int totNormal = 0;
	int totFrozen = 0;
	int totVIP = 0;


	for (int i = 0; i < 4; i++)
	{
		while (regions[i]->AfterS.remove(O))
		{
			FTr = O->getfinishingtime();
			IDr = O->GetID();
			ATr = O->GetArrivalTime();
			WTr = O->getWaitingTime();
			STr = O->getServedTime();


			out << FTr << " " << IDr << " " << ATr << " " << WTr << " " << STr << endl;
			switch (O->GetType())
			{
			case 0:
			{
				totNormal++;
				break;
			}
			case 1:
			{
				totFrozen++;
				break;
			}
			case 2:
			{
				totVIP++;
				break;
			}
			}
		}
	}
	int sumofallwaiting=sumofwaiting1+sumofwaiting2+sumofwaiting3+sumofwaiting4;
	int sumofallserving=sumofserving1+sumofserving2+sumofserving3+sumofserving4;
	int sumofallorderss=countoforderss1+countoforderss2+countoforderss3+countoforderss4;
	totOrder = totNormal + totFrozen + totVIP;
	int totMN = regions[0]->countofnoraml + regions[1]->countofnoraml + regions[2]->countofnoraml + regions[3]->countofnoraml;
	int totMF = regions[0]->countoffrozen + regions[1]->countoffrozen + regions[2]->countoffrozen + regions[3]->countoffrozen;
	int totMV = regions[0]->countofvip + regions[1]->countofvip + regions[2]->countofvip + regions[3]->countofvip;
	int totC = tot1 + tot2 + tot3 + tot4;

	out << "orders: " << totOrder << " [Norm: " << totNormal;
	out << " Froz: " << totFrozen << " VIP: " << totVIP << "]" << endl;
	out << "MotorC: " << totC << " [Norm: " << totMN << " Froz: " << totMF;
	out << " VIP: " << totMV << "]" << endl;
	double totWait = sumofallwaiting/sumofallorderss;
	double totserv = sumofallserving/sumofallorderss;
	out << "Avg wait = " << totWait << ", " << "Avg Serv = " << totserv << endl;
	out.close();








}
////////////////

void Restaurant::StepSim()

{
	loadfunction();
	int EventCnt;
	Order* pOrd;
	int counts[4] = { 0,0,0,0 };
	int count[4] = { 0,0,0,0 };
	/*pGUI->PrintMessage("Enter EVENTS Count(next phases should read I/P filename):");
	EventCnt = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer*/
	pGUI->UpdateInterface();

	//pGUI->PrintMessage("Generating orders randomly... In next phases, orders should be loaded from a file");

	//int EvTime = 0;

	//Create Random events
	//All generated event will be "ArrivalEvents" for the demo


	int CurrentTimeStep = 1;
	//as long as events queue is not empty yet
	Event *x;
	int countofservedorders = 0;
	while (countofservedorders < noofordersshouldbeserved)
	{
		 int y=1;
		ExecuteEvents(CurrentTimeStep);

		for (int i = 0; i < 4; i++) {
			int x = AddPriorityQueue(regions[i]->viporders);
			int y = AddQueueForDrawing(regions[i]->frozenorders);
			int z = AddQueueForDrawing(regions[i]->normalorders);
			counts[i] = x + y + z;
			count[i] = regions[i]->served.getcount();
		}
		countofservedorders = count[0] + count[1] + count[2] + count[3];
		pGUI->UpdateInterface();
		Sleep(500);
		for (int i = 0; i < 4; i++)
		{
					pGUI->ClearStatusBar();
			string str1 = to_string(counts[i]);
			string str2 = to_string(regions[i]->countofvip);
			string str3 = to_string(regions[i]->countofnoraml);
			string str4 = to_string(regions[i]->countoffrozen);
			string str5=to_string(regions[i]->noofservednormal);
			string str6=to_string(regions[i]->noofservedfrozen);
			string str7=to_string(regions[i]->noofservedvip);
			pGUI->PrintMessage("number of active order in this region is:" + str1,y++);
			//Sleep(600);
			pGUI->PrintMessage("number of available VIP motorcycle is:" + str2,y++);
			//Sleep(600);
			pGUI->PrintMessage("number of available Normal motorcycle is:" + str3,y++);
			//Sleep(600);
			pGUI->PrintMessage("number of available Frozen motorcycle is:" + str4,y++);
			//Sleep(600);
			pGUI->PrintMessage("number of served normal orders:" + str5,y++);
			//Sleep(600);
			pGUI->PrintMessage("number of served frozen orders:" + str6,y++);
			//Sleep(600);
			y=1;
			Sleep(2000);
			pGUI->ClearStatusBar();
			pGUI->PrintMessage("number of served vip orders" + str7,y++);
			Sleep(600);
			cout << "region" << i << endl;
			regions[i]->checkforservedorders(CurrentTimeStep);
			regions[i]->DeassignallMotorcycle(CurrentTimeStep);
			Sleep(600);
			regions[i]->assginmotorcyces(CurrentTimeStep,pGUI);
			y=1;
		}
		string noofservedorders=to_string(regions[0]->noofservedorders+regions[1]->noofservedorders+regions[2]->noofservedorders+regions[3]->noofservedorders);
		pGUI->PrintMessage("number of served orders" + noofservedorders);
		pGUI->UpdateInterface();
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep, timestep, 10);
		pGUI->PrintMessage(timestep);


		//execute all events at current time step
		//The above line may add new orders to the DEMO_Queue

		//Let's draw all arrived orders by passing them to the GUI to draw

		pGUI->UpdateInterface();
		Sleep(10);
		CurrentTimeStep++;
		//advance timestep
		pGUI->ResetDrawingList();

	}
	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();
	cout << "a" << endl;
	ofstream out;
	out.open("output.txt");
	out << "Region A" << endl;
	Order *O;
	out << "FT ID AT WT ST" << endl;
	float sumofwaiting1 = 0;
	int countoforderss1 = 0;
	float sumofserving1 = 0;
	float AvgWait1;
	float AvgServ1;
	int FT1, ID1, AT1, WT1, ST1;

	float sumofwaiting2 = 0;
	int countoforderss2 = 0;
	float sumofserving2 = 0;
	float AvgWait2;
	float AvgServ2;
	int FT2, ID2, AT2, WT2, ST2;


	float sumofwaiting3 = 0;
	int countoforderss3 = 0;
	float sumofserving3 = 0;
	float AvgWait3;
	float AvgServ3;
	int FT3, ID3, AT3, WT3, ST3;



	float sumofwaiting4 = 0;
	int countoforderss4 = 0;
	float sumofserving4 = 0;
	float AvgWait4;
	float AvgServ4;
	int FT4, ID4, AT4, WT4, ST4;

	int FTr, IDr, ATr, WTr, STr;



	while (regions[0]->served.remove(O))
	{
		regions[0]->AfterS.Insert(*O);
		sumofwaiting1 = O->getWaitingTime() + sumofwaiting1;
		sumofserving1 = sumofserving1 + O->getServedTime();
		countoforderss1++;
		FT1 = O->getfinishingtime();
		ID1 = O->GetID();
		AT1 = O->GetArrivalTime();
		WT1 = O->getWaitingTime();
		ST1 = O->getServedTime();


		out << FT1 << " " << ID1 << " " << AT1 << " " << WT1 << " " << ST1 << endl;
		switch (O->GetType())
		{
		case 0:
		{
			regions[0]->noofnormalorders++;
			break;
		}
		case 1:
		{
			regions[0]->nooffrozenorders++;
			break;
		}
		case 2:
		{
			regions[0]->noofviporders++;
			break;
		}
		}
	}
	AvgWait1 = sumofwaiting1 / countoforderss1;
	AvgServ1 = sumofserving1 / countoforderss1;
	out << "orders: " << regions[0]->CountOfOrders << " [Norm: " << regions[0]->noofnormalorders;
	out << " Froz: " << regions[0]->nooffrozenorders << " VIP: " << regions[0]->noofviporders << "]" << endl;
	int tot1 = (regions[0]->countoffrozen) + (regions[0]->countofnoraml) + (regions[0]->countofvip);
	out << "MotorC: " << tot1 << " [Norm: " << regions[0]->countofnoraml << " Froz: " << regions[0]->countoffrozen;
	out << " VIP: " << regions[0]->countofvip << "]" << endl;
	out << "Avg wait = " << AvgWait1;
	out << ", Avg Serv = " << AvgServ1 << endl;
	out << endl;

	out << endl;
	out << "Region B" << endl;
	out << "FT ID AT WT ST" << endl;

	while (regions[1]->served.remove(O))
	{
		regions[1]->AfterS.Insert(*O);
		sumofwaiting2 = O->getWaitingTime() + sumofwaiting2;
		sumofserving2 = sumofserving2 + O->getServedTime();
		countoforderss2++;
		FT2 = O->getfinishingtime();
		ID2 = O->GetID();
		AT2 = O->GetArrivalTime();
		WT2 = O->getWaitingTime();
		ST2 = O->getServedTime();


		out << FT2 << " " << ID2 << " " << AT2 << " " << WT2 << " " << ST2 << endl;
		switch (O->GetType())
		{
		case 0:
		{
			regions[1]->noofnormalorders++;
			break;
		}
		case 1:
		{
			regions[1]->nooffrozenorders++;
			break;
		}
		case 2:
		{
			regions[1]->noofviporders++;
			break;
		}
		}
	}
	AvgWait2 = sumofwaiting2 / countoforderss2;
	AvgServ2 = sumofserving2 / countoforderss2;
	out << "orders: " << regions[1]->CountOfOrders << " [Norm: " << regions[1]->noofnormalorders;
	out << " Froz: " << regions[1]->nooffrozenorders << " VIP: " << regions[1]->noofviporders << "]" << endl;
	int tot2 = (regions[1]->countoffrozen) + (regions[1]->countofnoraml) + (regions[1]->countofvip);
	out << "MotorC: " << tot2 << " [Norm: " << regions[1]->countofnoraml << " Froz: " << regions[1]->countoffrozen;
	out << " VIP: " << regions[1]->countofvip << "]" << endl;
	out << "Avg wait = " << AvgWait2;
	out << ", Avg Serv = " << AvgServ2 << endl;

	out << endl;
	out << "Region C" << endl;
	out << "FT ID AT WT ST" << endl;


	while (regions[2]->served.remove(O))
	{
		regions[2]->AfterS.Insert(*O);
		sumofwaiting3 = O->getWaitingTime() + sumofwaiting3;
		sumofserving3 = sumofserving3 + O->getServedTime();
		countoforderss3++;
		FT3 = O->getfinishingtime();
		ID3 = O->GetID();
		AT3 = O->GetArrivalTime();
		WT3 = O->getWaitingTime();
		ST3 = O->getServedTime();


		out << FT3 << " " << ID3 << " " << AT3 << " " << WT3 << " " << ST3 << endl;
		switch (O->GetType())
		{
		case 0:
		{
			regions[2]->noofnormalorders++;
			break;
		}
		case 1:
		{
			regions[2]->nooffrozenorders++;
			break;
		}
		case 2:
		{
			regions[2]->noofviporders++;
			break;
		}
		}
	}
	AvgWait3 = sumofwaiting3 / countoforderss3;
	AvgServ3 = sumofserving3 / countoforderss3;
	out << "orders: " << regions[0]->CountOfOrders << " [Norm: " << regions[0]->noofnormalorders;
	out << " Froz: " << regions[0]->nooffrozenorders << " VIP: " << regions[0]->noofviporders << "]" << endl;
	int tot3 = (regions[2]->countoffrozen) + (regions[2]->countofnoraml) + (regions[2]->countofvip);
	out << "MotorC: " << tot3 << " [Norm: " << regions[2]->countofnoraml << " Froz: " << regions[2]->countoffrozen;
	out << " VIP: " << regions[2]->countofvip << "]" << endl;
	out << "Avg wait = " << AvgWait3;
	out << ", Avg Serv = " << AvgServ3 << endl;
	out << endl;

	out << "Region D" << endl;
	out << "FT ID AT WT ST" << endl;


	while (regions[3]->served.remove(O))
	{
		regions[3]->AfterS.Insert(*O);
		sumofwaiting4 = O->getWaitingTime() + sumofwaiting4;
		sumofserving4 = sumofserving4 + O->getServedTime();
		countoforderss4++;
		FT4 = O->getfinishingtime();
		ID4 = O->GetID();
		AT4 = O->GetArrivalTime();
		WT4 = O->getWaitingTime();
		ST4 = O->getServedTime();


		out << FT4 << " " << ID4 << " " << AT4 << " " << WT4 << " " << ST4 << endl;
		switch (O->GetType())
		{
		case 0:
		{
			regions[3]->noofnormalorders++;
			break;
		}
		case 1:
		{
			regions[3]->nooffrozenorders++;
			break;
		}
		case 2:
		{
			regions[3]->noofviporders++;
			break;
		}
		}
	}
	AvgWait4 = sumofwaiting4 / countoforderss4;
	AvgServ4 = sumofserving4 / countoforderss4;
	out << "orders: " << regions[3]->CountOfOrders << " [Norm: " << regions[3]->noofnormalorders;
	out << " Froz: " << regions[3]->nooffrozenorders << " VIP: " << regions[3]->noofviporders << "]" << endl;
	int tot4 = (regions[3]->countoffrozen) + (regions[3]->countofnoraml) + (regions[3]->countofvip);
	out << "MotorC: " << tot4 << " [Norm: " << regions[3]->countofnoraml << " Froz: " << regions[3]->countoffrozen;
	out << " VIP: " << regions[3]->countofvip << "]" << endl;
	out << "Avg wait = " << AvgWait4;
	out << ", Avg Serv = " << AvgServ4 << endl;

	out << endl;
	out << "Whole Restaurant" << endl;
	out << "FT ID AT WT ST" << endl;


	int totOrder = 0;
	int totNormal = 0;
	int totFrozen = 0;
	int totVIP = 0;


	for (int i = 0; i < 4; i++)
	{
		while (regions[i]->AfterS.remove(O))
		{
			FTr = O->getfinishingtime();
			IDr = O->GetID();
			ATr = O->GetArrivalTime();
			WTr = O->getWaitingTime();
			STr = O->getServedTime();


			out << FTr << " " << IDr << " " << ATr << " " << WTr << " " << STr << endl;
			switch (O->GetType())
			{
			case 0:
			{
				totNormal++;
				break;
			}
			case 1:
			{
				totFrozen++;
				break;
			}
			case 2:
			{
				totVIP++;
				break;
			}
			}
		}
	}
	int sumofallwaiting=sumofwaiting1+sumofwaiting2+sumofwaiting3+sumofwaiting4;
	int sumofallserving=sumofserving1+sumofserving2+sumofserving3+sumofserving4;
	int sumofallorderss=countoforderss1+countoforderss2+countoforderss3+countoforderss4;
	totOrder = totNormal + totFrozen + totVIP;
	int totMN = regions[0]->countofnoraml + regions[1]->countofnoraml + regions[2]->countofnoraml + regions[3]->countofnoraml;
	int totMF = regions[0]->countoffrozen + regions[1]->countoffrozen + regions[2]->countoffrozen + regions[3]->countoffrozen;
	int totMV = regions[0]->countofvip + regions[1]->countofvip + regions[2]->countofvip + regions[3]->countofvip;
	int totC = tot1 + tot2 + tot3 + tot4;

	out << "orders: " << totOrder << " [Norm: " << totNormal;
	out << " Froz: " << totFrozen << " VIP: " << totVIP << "]" << endl;
	out << "MotorC: " << totC << " [Norm: " << totMN << " Froz: " << totMF;
	out << " VIP: " << totMV << "]" << endl;
	double totWait = sumofallwaiting/sumofallorderss;
	double totserv = sumofallserving/sumofallorderss;
	out << "Avg wait = " << totWait << ", " << "Avg Serv = " << totserv << endl;
	out.close();







}

void Restaurant::silent()

{
	loadfunction();
	int EventCnt;
	Order* pOrd;
	int counts[4] = { 0,0,0,0 };
	int count[4] = { 0,0,0,0 };
	/*pGUI->PrintMessage("Enter EVENTS Count(next phases should read I/P filename):");
	EventCnt = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer*/
	pGUI->DoNothing();

	//pGUI->PrintMessage("Generating orders randomly... In next phases, orders should be loaded from a file");

	//int EvTime = 0;

	//Create Random events
	//All generated event will be "ArrivalEvents" for the demo


	int CurrentTimeStep = 1;
	//as long as events queue is not empty yet
	Event *x;
	int countofservedorders = 0;
	while (countofservedorders < noofordersshouldbeserved)
	{

		ExecuteEvents(CurrentTimeStep);

		for (int i = 0; i < 4; i++) {
			int x = AddPriorityQueue(regions[i]->viporders);
			int y = AddQueueForDrawing(regions[i]->frozenorders);
			int z = AddQueueForDrawing(regions[i]->normalorders);
			counts[i] = x + y + z;
			count[i] = regions[i]->served.getcount();
		}
		countofservedorders = count[0] + count[1] + count[2] + count[3];
		pGUI->DoNothing();
		Sleep(1);
		for (int i = 0; i < 4; i++)
		{
			string str1 = to_string(counts[i]);
			string str2 = to_string(regions[i]->countofvip);
			string str3 = to_string(regions[i]->countofnoraml);
			string str4 = to_string(regions[i]->countoffrozen);





			/*Order* x;
			bool isfound;
			isfound = regions[i]->viporders.dequeue(x);
			if (isfound) {
			regions[i]->decrement();
			}
			isfound = regions[i]->frozenorders.dequeue(x);
			if (isfound) {
			regions[i]->decrement();
			}
			isfound = regions[i]->normalorders.dequeue(x);
			if (isfound) {
			regions[i]->decrement();
			}
			*/
			cout << "region" << i << endl;
			regions[i]->checkforservedorders(CurrentTimeStep);
			regions[i]->DeassignallMotorcycle(CurrentTimeStep);
			regions[i]->assginmotorcyces(CurrentTimeStep,pGUI);
		}
		pGUI->DoNothing();
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep, timestep, 10);
		pGUI->PrintMessage("waiting");


		//execute all events at current time step
		//The above line may add new orders to the DEMO_Queue

		//Let's draw all arrived orders by passing them to the GUI to draw

		pGUI->DoNothing();
		Sleep(1);
		CurrentTimeStep++;
		//advance timestep
		pGUI->ResetDrawingList();

	}
	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();
	cout << "a" << endl;
	
	ofstream out;
	out.open("output.txt");
	out << "Region A" << endl;
	Order *O;
	out << "FT ID AT WT ST" << endl;
	float sumofwaiting1 = 0;
	int countoforderss1 = 0;
	float sumofserving1 = 0;
	float AvgWait1;
	float AvgServ1;
	int FT1, ID1, AT1, WT1, ST1;

	float sumofwaiting2 = 0;
	int countoforderss2 = 0;
	float sumofserving2 = 0;
	float AvgWait2;
	float AvgServ2;
	int FT2, ID2, AT2, WT2, ST2;


	float sumofwaiting3 = 0;
	int countoforderss3 = 0;
	float sumofserving3 = 0;
	float AvgWait3;
	float AvgServ3;
	int FT3, ID3, AT3, WT3, ST3;



	float sumofwaiting4 = 0;
	int countoforderss4 = 0;
	float sumofserving4 = 0;
	float AvgWait4;
	float AvgServ4;
	int FT4, ID4, AT4, WT4, ST4;

	int FTr, IDr, ATr, WTr, STr;



	while (regions[0]->served.remove(O))
	{
		regions[0]->AfterS.Insert(*O);
		sumofwaiting1 = O->getWaitingTime() + sumofwaiting1;
		sumofserving1 = sumofserving1 + O->getServedTime();
		countoforderss1++;
		FT1 = O->getfinishingtime();
		ID1 = O->GetID();
		AT1 = O->GetArrivalTime();
		WT1 = O->getWaitingTime();
		ST1 = O->getServedTime();


		out << FT1 << " " << ID1 << " " << AT1 << " " << WT1 << " " << ST1 << endl;
		switch (O->GetType())
		{
		case 0:
		{
			regions[0]->noofnormalorders++;
			break;
		}
		case 1:
		{
			regions[0]->nooffrozenorders++;
			break;
		}
		case 2:
		{
			regions[0]->noofviporders++;
			break;
		}
		}
	}
	AvgWait1 = sumofwaiting1 / countoforderss1;
	AvgServ1 = sumofserving1 / countoforderss1;
	out << "orders: " << regions[0]->CountOfOrders << " [Norm: " << regions[0]->noofnormalorders;
	out << " Froz: " << regions[0]->nooffrozenorders << " VIP: " << regions[0]->noofviporders << "]" << endl;
	int tot1 = (regions[0]->countoffrozen) + (regions[0]->countofnoraml) + (regions[0]->countofvip);
	out << "MotorC: " << tot1 << " [Norm: " << regions[0]->countofnoraml << " Froz: " << regions[0]->countoffrozen;
	out << " VIP: " << regions[0]->countofvip << "]" << endl;
	out << "Avg wait = " << AvgWait1;
	out << ", Avg Serv = " << AvgServ1 << endl;
	out << endl;

	out << endl;
	out << "Region B" << endl;
	out << "FT ID AT WT ST" << endl;

	while (regions[1]->served.remove(O))
	{
		regions[1]->AfterS.Insert(*O);
		sumofwaiting2 = O->getWaitingTime() + sumofwaiting2;
		sumofserving2 = sumofserving2 + O->getServedTime();
		countoforderss2++;
		FT2 = O->getfinishingtime();
		ID2 = O->GetID();
		AT2 = O->GetArrivalTime();
		WT2 = O->getWaitingTime();
		ST2 = O->getServedTime();


		out << FT2 << " " << ID2 << " " << AT2 << " " << WT2 << " " << ST2 << endl;
		switch (O->GetType())
		{
		case 0:
		{
			regions[1]->noofnormalorders++;
			break;
		}
		case 1:
		{
			regions[1]->nooffrozenorders++;
			break;
		}
		case 2:
		{
			regions[1]->noofviporders++;
			break;
		}
		}
	}
	AvgWait2 = sumofwaiting2 / countoforderss2;
	AvgServ2 = sumofserving2 / countoforderss2;
	out << "orders: " << regions[1]->CountOfOrders << " [Norm: " << regions[1]->noofnormalorders;
	out << " Froz: " << regions[1]->nooffrozenorders << " VIP: " << regions[1]->noofviporders << "]" << endl;
	int tot2 = (regions[1]->countoffrozen) + (regions[1]->countofnoraml) + (regions[1]->countofvip);
	out << "MotorC: " << tot2 << " [Norm: " << regions[1]->countofnoraml << " Froz: " << regions[1]->countoffrozen;
	out << " VIP: " << regions[1]->countofvip <<"]" <<endl;
	out << "Avg wait = " << AvgWait2;
	out << ", Avg Serv = " << AvgServ2 << endl;

	out << endl;
	out << "Region C" << endl;
	out << "FT ID AT WT ST" << endl;


	while (regions[2]->served.remove(O))
	{
		regions[2]->AfterS.Insert(*O);
		sumofwaiting3 = O->getWaitingTime() + sumofwaiting3;
		sumofserving3 = sumofserving3 + O->getServedTime();
		countoforderss3++;
		FT3 = O->getfinishingtime();
		ID3 = O->GetID();
		AT3 = O->GetArrivalTime();
		WT3 = O->getWaitingTime();
		ST3 = O->getServedTime();


		out << FT3 << " " << ID3 << " " << AT3 << " " << WT3 << " " << ST3 << endl;
		switch (O->GetType())
		{
		case 0:
		{
			regions[2]->noofnormalorders++;
			break;
		}
		case 1:
		{
			regions[2]->nooffrozenorders++;
			break;
		}
		case 2:
		{
			regions[2]->noofviporders++;
			break;
		}
		}
	}
	AvgWait3 = sumofwaiting3 / countoforderss3;
	AvgServ3 = sumofserving3 / countoforderss3;
	out << "orders: " << regions[0]->CountOfOrders << " [Norm: " << regions[0]->noofnormalorders;
	out << " Froz: " << regions[0]->nooffrozenorders << " VIP: " << regions[0]->noofviporders << "]" << endl;
	int tot3 = (regions[2]->countoffrozen) + (regions[2]->countofnoraml) + (regions[2]->countofvip);
	out << "MotorC: " << tot3 << " [Norm: " << regions[2]->countofnoraml << " Froz: " << regions[2]->countoffrozen;
	out << " VIP: " << regions[2]->countofvip <<"]" <<endl;
	out << "Avg wait = " << AvgWait3;
	out << ", Avg Serv = " << AvgServ3 << endl;
	out << endl;

	out << "Region D" << endl;
	out << "FT ID AT WT ST" << endl;


	while (regions[3]->served.remove(O))
	{
		regions[3]->AfterS.Insert(*O);
		sumofwaiting4 = O->getWaitingTime() + sumofwaiting4;
		sumofserving4 = sumofserving4 + O->getServedTime();
		countoforderss4++;
		FT4 = O->getfinishingtime();
		ID4 = O->GetID();
		AT4 = O->GetArrivalTime();
		WT4 = O->getWaitingTime();
		ST4 = O->getServedTime();


		out << FT4 << " " << ID4 << " " << AT4 << " " << WT4 << " " << ST4 << endl;
		switch (O->GetType())
		{
		case 0:
		{
			regions[3]->noofnormalorders++;
			break;
		}
		case 1:
		{
			regions[3]->nooffrozenorders++;
			break;
		}
		case 2:
		{
			regions[3]->noofviporders++;
			break;
		}
		}
	}
	AvgWait4 = sumofwaiting4 / countoforderss4;
	AvgServ4 = sumofserving4 / countoforderss4;
	out << "orders: " << regions[3]->CountOfOrders << " [Norm: " << regions[3]->noofnormalorders;
	out << " Froz: " << regions[3]->nooffrozenorders << " VIP: " << regions[3]->noofviporders << "]" << endl;
	int tot4 = (regions[3]->countoffrozen) + (regions[3]->countofnoraml) + (regions[3]->countofvip);
	out << "MotorC: " << tot4 << " [Norm: " << regions[3]->countofnoraml << " Froz: " << regions[3]->countoffrozen;
	out << " VIP: " << regions[3]->countofvip <<"]" <<endl;
	out << "Avg wait = " << AvgWait4;
	out << ", Avg Serv = " << AvgServ4 << endl;

	out << endl;
	out << "Whole Restaurant" << endl;
	out << "FT ID AT WT ST" << endl;


	int totOrder = 0;
	int totNormal = 0;
	int totFrozen = 0;
	int totVIP = 0;


	for (int i = 0; i < 4; i++)
	{
		while (regions[i]->AfterS.remove(O))
		{
			FTr = O->getfinishingtime();
			IDr = O->GetID();
			ATr = O->GetArrivalTime();
			WTr = O->getWaitingTime();
			STr = O->getServedTime();


			out << FTr << " " << IDr << " " << ATr << " " << WTr << " " << STr << endl;
			switch (O->GetType())
			{
			case 0:
			{
				totNormal++;
				break;
			}
			case 1:
			{
				totFrozen++;
				break;
			}
			case 2:
			{
				totVIP++;
				break;
			}
			}
		}
	}
	int sumofallwaiting=sumofwaiting1+sumofwaiting2+sumofwaiting3+sumofwaiting4;
	int sumofallserving=sumofserving1+sumofserving2+sumofserving3+sumofserving4;
	int sumofallorderss=countoforderss1+countoforderss2+countoforderss3+countoforderss4;
	totOrder = totNormal + totFrozen + totVIP;
	int totMN = regions[0]->countofnoraml + regions[1]->countofnoraml + regions[2]->countofnoraml + regions[3]->countofnoraml;
	int totMF = regions[0]->countoffrozen + regions[1]->countoffrozen + regions[2]->countoffrozen + regions[3]->countoffrozen;
	int totMV = regions[0]->countofvip + regions[1]->countofvip + regions[2]->countofvip + regions[3]->countofvip;
	int totC = tot1 + tot2 + tot3 + tot4;

	out << "orders: " << totOrder << " [Norm: " << totNormal;
	out << " Froz: " << totFrozen << " VIP: " << totVIP << "]" << endl;
	out << "MotorC: " << totC << " [Norm: " << totMN << " Froz: " << totMF;
	out << " VIP: " << totMV<<"]" << endl;
	double totWait = sumofallwaiting/sumofallorderss;
	double totserv = sumofallserving/sumofallorderss;
	out << "Avg wait = " << totWait << ", " << "Avg Serv = " << totserv << endl;
	out.close();




}

void Restaurant::AddtoDemoQueue(Order *pOrd)
{
	DEMO_Queue.enqueue(pOrd);
}

Order* Restaurant::getDemoOrder()
{
	Order* pOrd;
	DEMO_Queue.dequeue(pOrd);
	return pOrd;

}



void Restaurant::loadfunction() {
	fstream myfile;
	myfile.open("input.txt");

/*	int SN, SF, SV;
	myfile >> SN;
	myfile >> SF;
	myfile >> SV;*/
	for (int i = 0; i < 4; i++) {
		int N, F, V;
		myfile >> N;
		myfile >> F;
		myfile >> V;
		cout << V << endl;
		REGION R = A_REG;
		switch (i) {
		case 0:
			R = A_REG;
			break;
		case 1:
			R = B_REG;
			break;
		case 2:
			R = C_REG;
			break;
		case 3:
			R = D_REG;
			break;
		}
		regions[i] = new region(R, N, F, V,myfile);
	}
	cout<<"xxxxx"<<endl;
	myfile >> autopromotion;
	cout<<"yyyyy"<<endl;
	int noevents;
	myfile >> noevents;

	for (int j = 0; j < noevents; j++) {
		char s;
		myfile >> s;

		if (s == 'X') {
			Event*p = new CancellationEvent;
			p->Load(this, myfile);
			noofcancellationevents++;
		}
		if (s == 'R') {
			Event*p = new ArrivalEvent;
			p->Load(this, myfile);
			noofarrivalevents++;
			noofordersshouldbeserved++;
		}
		if (s == 'P') {
			Event*p = new PromotionEvent;
			p->Load(this, myfile);
			noofpromotionevents++;
		}
	}
	cout<<"zzz"<<endl;
}


void Restaurant::AddOrder(Order*O)
{
	if (O->GetRegion() == A_REG && O->GetType() == TYPE_NRM) {

		regions[0]->normalorders.enqueue(O);

		regions[0]->increment();
	}

	else if (O->GetRegion() == A_REG && O->GetType() == TYPE_FROZ) {


		regions[0]->frozenorders.enqueue(O);
		regions[0]->increment();

	}
	else if (O->GetRegion() == A_REG && O->GetType() == TYPE_VIP) {


		double x = O->GetTotalMoney()* O->GetTotalMoney() / (O->GetDistance()*O->GetArrivalTime());
		regions[0]->viporders.enqueue(O, x);
		regions[0]->increment();

	}
	if (O->GetRegion() == B_REG && O->GetType() == TYPE_NRM) {

		regions[1]->normalorders.enqueue(O);
		regions[1]->increment();
	}

	else if (O->GetRegion() == B_REG && O->GetType() == TYPE_FROZ) {


		regions[1]->frozenorders.enqueue(O);
		regions[1]->increment();

	}
	else if (O->GetRegion() == B_REG && O->GetType() == TYPE_VIP) {
		cout << "xaxaxaxaxaxaxaxaxaxax" << endl;

		double x = O->GetTotalMoney()* O->GetTotalMoney() / (O->GetDistance()*O->GetArrivalTime());
		regions[1]->viporders.enqueue(O, x);
		regions[1]->increment();

	}
	if (O->GetRegion() == C_REG && O->GetType() == TYPE_NRM) {

		regions[2]->normalorders.enqueue(O);
		regions[2]->increment();
	}

	else if (O->GetRegion() == C_REG && O->GetType() == TYPE_FROZ) {


		regions[2]->frozenorders.enqueue(O);
		regions[2]->increment();

	}
	if (O->GetRegion() == C_REG && O->GetType() == TYPE_VIP) {


		double x = O->GetTotalMoney()* O->GetTotalMoney() / (O->GetDistance()*O->GetArrivalTime());
		regions[2]->viporders.enqueue(O, x);
		regions[2]->increment();

	}
	if (O->GetRegion() == D_REG && O->GetType() == TYPE_NRM) {

		regions[3]->normalorders.enqueue(O);
		regions[3]->increment();
	}

	if (O->GetRegion() == D_REG && O->GetType() == TYPE_FROZ) {


		regions[3]->frozenorders.enqueue(O);
		regions[3]->increment();

	}
	if (O->GetRegion() == D_REG && O->GetType() == TYPE_VIP) {


		double x = O->GetTotalMoney()* O->GetTotalMoney() / (O->GetDistance()*O->GetArrivalTime());
		regions[3]->viporders.enqueue(O, x);
		regions[3]->increment();
	}

}
void Restaurant::Cancel(int id)
{
	cout << "start cancel" << endl;
	for (int i = 0; i < 4; i++)
	{
		Order*x;
		Queue<Order*>q;
		while (regions[i]->normalorders.isEmpty() == false)
		{
			regions[i]->normalorders.dequeue(x);
			if (x->GetID() != id)
			{
				q.enqueue(x);
			}
			else
			{
				noofordersshouldbeserved--;
				regions[i]->decrement();
			}

		}
		while (q.isEmpty() == false)
		{
			q.dequeue(x);
			regions[i]->normalorders.enqueue(x);
		}
	}
	cout << "end cancel" << endl;
}


void Restaurant::Promote(int id, double money)
{
	cout << "start promote" << endl;
	for (int i = 0; i < 4; i++)
	{
		Order* x;
		Queue<Order*> q;
		while (regions[i]->normalorders.isEmpty() == false)
		{
			regions[i]->normalorders.dequeue(x);
			if (x->GetID() != id)
			{
				q.enqueue(x);
			}
			else
			{
				double p = x->GetTotalMoney()* x->GetTotalMoney() / (x->GetDistance()*x->GetArrivalTime());
				x->setOrderType(3);
				x->setTotalMoney(x->GetTotalMoney() + money);
				regions[i]->viporders.enqueue(x, p);
			}
		}
		while (q.isEmpty() == false)
		{
			q.dequeue(x);
			regions[i]->normalorders.enqueue(x);
		}
	}
	cout << "end promote" << endl;
}





GUI* Restaurant::getgui() {
	return pGUI;
}
int Restaurant::AddPriorityQueue(PriorityQueue<Order*>Q) {
	Order** orders;
	int a = -1;
	Q.toarr(orders, a);
	cout << a << endl;
	for (int i = 0; i < a; i++) {
		pGUI->AddOrderForDrawing(orders[i]);
		cout << "2hoooooooooooooooooooooooooooooooooooooooooo" << endl;
	}
	return a;
};
int Restaurant::AddQueueForDrawing(Queue<Order*> Q) {
	Order** arr;
	cout << "start" << endl;
	int count;
	Q.toArray(arr, count);
	for (int i = 0; i < count; i++) {
		pGUI->AddOrderForDrawing(arr[i]);
	}
	return count;
	cout << "end" << endl;
};

