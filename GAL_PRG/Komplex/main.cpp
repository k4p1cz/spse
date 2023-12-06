#include "header.h"

int main() {
	KompCislo prvni(28, 12), druhe, treti;
	
	cin >> druhe;
	system("cls");
	cout << "Prvni: " << prvni;
	cout << "Druhe: " << druhe;
	cout << "Treti: " << treti;
	
	cout << "\nAbsolutni hodnota druheho k. cisla: " << druhe.AbsHodnota() << endl;

	cout << "\nSoucet prvniho cisla s druhym cislem: " << prvni + druhe << endl;
	
	cout << "\nRozdil druheho cisla s prvnim cislem: " << prvni - druhe << endl;
	
	cout << "\nSoucit prvniho cisla s druhym cislem: " << prvni * druhe << endl;
	
	cout << "\nPodil prvniho cisla s druhym cislem: " << prvni / druhe << endl;
	
	
	return 0;
}
