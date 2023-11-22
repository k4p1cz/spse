#include "head.h"

int main(int argc, char** argv) {
	Vehicle veh;
	bool err = false;
	do{
		system("cls");
		err = false;	
		cout << "Enter SPZ: " ;
		string e_spz;
		getline(cin, e_spz);
		err = veh.SetSPZ(e_spz);
		err = !err;
		fflush(stdin);
	}while(err);
	do{
		system("cls");
		err = false;	
		cout << "Enter type: " ;
		string e_type;
		getline(cin, e_type);
		err = veh.SetType(e_type);
		err = !err;
		fflush(stdin);
	}while(err);
	do{
		system("cls");
		err = false;	
		cout << "Enter year: " ;
		int e_year;
		cin >> e_year;
		err = veh.SetYear(e_year);
		err = !err;
	}while(err);
	do{
		system("cls");
		err = false;
		fflush(stdin);
		cout << "Is vehicle historical? (Yes or No)" ;
		string e_his;
		getline(cin, e_his);
		err = veh.SetHistorical(e_his);
		err = !err;
	}while(err);
	do{
		system("cls");
		err = false;
		cout << "Distance driven? (km) ";
		int e_km;
		cin >> e_km;
		err = veh.SetDistanceDriven(e_km);
		err = !err;
	}while(err);
	
	system("cls");
	cout << "	YOUR VEHICLE\n\n\n";
	cout << "SPZ: " << veh.GetSPZ() << "\n" << endl;
	cout << "Type: " << veh.GetType() << "\n" << endl;
	cout << "Year: " << veh.GetYear() << "\n" << endl;
	cout << "Historical: " << veh.IsHistorical() << "\n" << endl;
	cout << "Distance driven: " << veh.GetDistanceDriven() << "\n" << endl;
	cout << "\n\n\n";
}
