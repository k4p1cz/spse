#ifndef header
#define header

#include <iostream>
#include <cmath>
using namespace std;

class KompCislo {
private:
	float Realna, Imaginarni;
public:
	KompCislo();
	KompCislo(float Realna, float Imaginarni);
	
	friend ostream &operator<<(ostream &vystup, KompCislo x);
	friend istream &operator>>(istream &vstup, KompCislo &x);
	
	float AbsHodnota();
	friend KompCislo operator+(KompCislo const& a, KompCislo const& b);
	friend KompCislo operator-(KompCislo const& a, KompCislo const& b);
	friend KompCislo operator*(KompCislo const& a, KompCislo const& b);
	friend KompCislo operator/(KompCislo const& a, KompCislo const& b);
	
	void KompSdruzene(KompCislo e);
};

#endif
