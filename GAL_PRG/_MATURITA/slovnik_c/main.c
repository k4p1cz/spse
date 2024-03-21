#include "headers.h"

int main(int argc, char *argv[]) {
	int error = 0;
	int volba = 0;
	SLOVNIK slovnik;
	slovnik.pocetZaznamu = 0;
	slovnik = nacistSlovnikZeSouboru();
	do{
		do{
			system("cls");
			printf("------------------\n");
			printf("1. Pridat slovo do slovniku\n");
			printf("2. Odebrat slovo ze slovniku\n");
			printf("3. Preklad\n");
			printf("4. Zkouseni nahodne\n");
			printf("5. Zkouseni podle lekce\n");
			printf("6. Vypsani slovniku\n");
			printf("------------------\n");
			printf("Vyber: ");
			scanf("%d", &volba);
		}while(volba < 1 || volba > 6);
		switch (volba) {
		case 1:
			slovnik = pridatSlovo(slovnik);
			break;
		case 2:
			slovnik = odstranitZaznam(slovnik);
			break;
		case 3:
			prekladSlova(slovnik);
			break;
		case 6:
			vypsatSlovnik(slovnik);
			break;
		}
	}while(error == 0);
	system("cls");
	printf("ERROR\n\n");
	
	return 0;
}
