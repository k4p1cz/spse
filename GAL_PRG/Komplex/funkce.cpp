#include "header.h"

KompCislo::KompCislo() {
	this->Realna = 0;
	this->Imaginarni = 0;
}

KompCislo::KompCislo(float r, float i) {
	this->Realna = r;
	this->Imaginarni = i;
}

ostream &operator<<(ostream &vystup, KompCislo x) {
	if(x.Imaginarni >= 0) {
		vystup << x.Realna << "+" << x.Imaginarni << "i" << endl;
	}
	else {
		vystup << x.Realna << x.Imaginarni << "i" << endl;
	}
	return vystup;
}

istream &operator>>(istream &vstup, KompCislo &x) {
	cout << endl << "Zadej komplexni cislo :" << endl;
	cout << "Realna cast: ";
	vstup >> x.Realna;
	cout << "Imaginarni cast: ";
	vstup >> x.Imaginarni;
	
	return vstup;
}

float KompCislo::AbsHodnota() {
	float x = sqrt(this->Realna * this->Realna + this->Imaginarni * this->Imaginarni);
	return x;
}

KompCislo operator+(KompCislo const& a, KompCislo const& b){
	return KompCislo((a.Realna + b.Realna),(a.Imaginarni + b.Imaginarni));
}
KompCislo operator-(KompCislo const& a, KompCislo const& b){
	return KompCislo((a.Realna - b.Realna),(a.Imaginarni - b.Imaginarni));
}
