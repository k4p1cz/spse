#include "spoj.h"

int main(int argc, char** argv) {
	int sw, a=5, b=-2, c;
	Seznam s;
	do {
		cout << "0 - Konec vyberu" << endl << "1 - Prida na zacatek (zasobnik)" << endl << "2 - Vypise seznam" << endl << "3 - Prida na konec (fronta)" << endl << "Zadej:";
		cin >> sw;
		s.PridejNaZacatek(a);
		s.PridejNaZacatek(b);
		switch (sw) {
			case 1:
				cout << "Zadejte cislo:";
				cin >> c;
				s.PridejNaZacatek(c);
				break;
			case 2:
				s.VypisSeznam();
				break;
			case 3:
				cout << "Zadejte cislo:";
				cin >> c;
				s.PridejNaKonec(c);
				break;
		}
	} while (sw != 0);
	return 0;
}
