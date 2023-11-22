#include "head.h"

Vehicle::Vehicle(){
	this->spz = "";
	this->type = "";
	this->year = -1;
	this->historical = false;
}
bool Vehicle::SetSPZ(string e){
	if(e.length() < 7 or e == ""){
		return false;
	}
	this->spz = e;
	return true;
}
bool Vehicle::SetType(string e){
	if(e.length() < 1 or e == ""){
		return false;
	}
	this->type = e;
	return true;
}
bool Vehicle::SetYear(int e){
	if(e < 1800 or e > 2023){
		return false;
	}
	this->year = e;
	return true;
}
bool Vehicle::SetHistorical(string e){
	/*if(e != "yes" or e != "Yes" or e != "no" or e != "No"){
		return false;
	  }*/
	this->historical = e;
	return true;
}
bool Vehicle::SetDistanceDriven(int e){
	if(e < 0){
		return false;
	}
	this->distanceDriven = e;
	return true;
}
string Vehicle::GetSPZ(){
	return this->spz;
}
string Vehicle::GetType(){
	return this->type;
}
int Vehicle::GetYear(){
	return this->year;
}
string Vehicle::IsHistorical(){
	return this->historical;
}
int Vehicle::GetDistanceDriven(){
	return this->distanceDriven;
}
