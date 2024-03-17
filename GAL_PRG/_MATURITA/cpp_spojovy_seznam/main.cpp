#include "header.h"

int main(int argc, char** argv) {
	system("cls");
	Uzel item;
	Seznam list;
	int volba = 0;
	fs_init();
	for(;;){
		do{
			system("cls");
			cout << "----------------" << endl;
			cout << "1. Pridat zaznam (na konec)" << endl;
			cout << "2. Pridat zaznam (na zacatek)" << endl;
			cout << "3. Zapsat seznam do souboru" << endl;
			cout << "4. Nacist seznam ze souboru" << endl;
			cout << "5. Vypsat seznam" << endl;
			cout << "6. Odstranit zaznam" << endl;
			cout << "7. Duplikovat zaznam" << endl;
			cout << "----------------" << endl;
			cout << "Vyber: ";
			cin >> volba;
		}while(volba < 1 || volba > 7);
		switch (volba) {
		case 1:
			cin >> item;
			list.pridejNaKonec(item.dejCislo(), true);
			break;
		case 2:
			cin >> item;
			list.pridejNaZacatek(item.dejCislo());
			break;
		case 3:
			list.zapisDoSouboru();
			break;
		case 4:
			list.nacistZeSouboru();
			break;
		case 5:
			list.vypisSeznam();
			break;
		default:
			//TODO
			break;
		}
		volba = 0;
	}
	
	return 0;
}
