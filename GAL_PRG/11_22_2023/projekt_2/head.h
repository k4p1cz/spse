#ifndef HEAD_H
#define HEAD_H

#include <iostream>
using namespace std;

class Vehicle{
private:
	string spz;
	string type;
	int year;
	string historical;
	int distanceDriven;
public:
	Vehicle();
	bool SetSPZ(string e);
	bool SetType(string e);
	bool SetYear(int e);
	bool SetHistorical(string e);
	bool SetDistanceDriven(int e);
	string GetSPZ();
	string GetType();
	int GetYear();
	string IsHistorical();
	int GetDistanceDriven();
};

#endif
