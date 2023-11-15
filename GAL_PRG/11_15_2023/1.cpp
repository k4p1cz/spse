#include <iostream>
using namespace std;


class Vozidlo {	
private:
	string Spz;
	int Year;
	int Speed;
public:
	Vozidlo();
	Vozidlo(string s, int y, int sp);
	
	bool SetSPZ(string e);
	string GetSPZ();
	bool SetYear(int e);
	int GetYear();
	bool SetSpeed(int e);
	int GetSpeed();
};

Vozidlo::Vozidlo(){
	this->Spz = "0A0 0000";
	this->Year = 0;
	this->Speed = 0;
}

Vozidlo::Vozidlo(string s, int y, int sp){
	this->Spz = s;
	this->Year = y;
	this->Speed = sp;
}


bool Vozidlo::SetSPZ(string e){
	if(e.length() > 8 || e.length() < 3){
		return false;
	}
	this->Spz = e;
	return true;
}

string Vozidlo::GetSPZ(){
	return this->Spz;
}

bool Vozidlo::SetYear(int e){
	if(e == 0){
		return false;
	}
	this->Year = e;
	return true;
}

int Vozidlo::GetYear(){
	return this->Year;
}

bool Vozidlo::SetSpeed(int e){
	if(e == 0){
		return false;
	}
	this->Speed = e;
	return true;
}

int Vozidlo::GetSpeed(){
	return this->Speed;
}



int main()
{
	Vozidlo first;
	string spz;
	int speed;
	int year;
	cout << "SPZ: " ;
	getline(cin, spz);
	cout << "Year: ";
	cin >> year;
	cout << "Speed: ";
	cin >> speed;
	
	
	
	bool spz_ = first.SetSPZ(spz);
	bool speed_ = first.SetSpeed(speed);
	bool year_ = first.SetYear(year);
	if(!spz_ || !speed_ || !year_){
		cout << "error" << endl;
	}else{
		cout << "\n" << endl;
		cout << first.GetSPZ() <<  "\n" << first.GetSpeed() << "\n" << first.GetYear() << endl;
		
	}
	return 0;
}
