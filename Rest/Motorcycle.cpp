#include "Motorcycle.h"
#include<iostream>
using namespace std;
Motorcycle::Motorcycle()
{
	 cout<<"new motorcycle is created of id "<<ID<<endl;
}


Motorcycle::~Motorcycle()
{
}
void Motorcycle::settype(ORD_TYPE a){
	type=a;
}
void Motorcycle::setregion(REGION R){
	region =R;
};
void Motorcycle::setspeed(int s){
	speed=s;
}
void Motorcycle::setstatus(STATUS S){
	status=S;
}

bool Motorcycle::operator<(Motorcycle m)
{
	return(speed > m.speed);
}

bool Motorcycle::operator==(Motorcycle m)
{
	return(speed == m.speed);
}

bool Motorcycle::operator>(Motorcycle m)
{
	return(speed < m.speed);
}
STATUS Motorcycle::Getstatus()
{
	return status;
}
void  Motorcycle::setorder(Order*l)
{
	o = l;
}
int Motorcycle::getspeed(){
	return speed;
}
Order* Motorcycle::getorder(){
	return o;
}
void Motorcycle::setid(int i){
	ID=i;
}
ORD_TYPE Motorcycle::gettype(){
	return type;
}
int Motorcycle::getid(){
	return ID;
}