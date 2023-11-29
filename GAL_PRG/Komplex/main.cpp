#include "header.h"

int main() {
	KompCislo prvni(28, 12), druhe, treti;
	
	cin >> druhe;
	system("cls");
	cout << "Prvni: " << prvni;
	cout << "Druhe: " << druhe;
	cout << "Treti: " << treti;
	
	cout << "\nAbsolutni hodnota druheho k. cisla: " << druhe.AbsHodnota() << endl;

	cout << "\nSoucet prvniho cisla s druhym cislem\n" << prvni + druhe << endl;
	
	cout << "\nRozdil druheho cisla s prvnim cislem\n" << prvni - druhe << endl;
	
	return 0;
}
