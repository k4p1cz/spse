#include "header.h"
Uzel::Uzel(){
	pred = nullptr;
	nasl = nullptr;
	id = 0;
}
Uzel::Uzel(int e){
	pred = nullptr;
	nasl = nullptr;
	id = e;
}
istream &operator>>(istream &vstup, Uzel &x) {
	system("cls");
	cout <<"Zadej cislo: ";
	cin >> x.id;
	
	return vstup;
}
int Uzel::dejCislo(){
	return this->id;
}
