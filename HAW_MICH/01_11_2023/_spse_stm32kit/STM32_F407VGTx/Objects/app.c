/**
  ********************************************************************************************************************************************
  * @file    STM32_00_HelloWorld_05-KeyPad.c
  * @author  SPSE Havirov
  * @version 1.1
  * @date    29-March-2022 [v1.0]
  * @brief   Testovaci program pro keypad (s rozlozenim 3x4 nebo 4x4).
  *
  ********************************************************************************************************************************************
  * @attention
  *
  * Otestovano na: F407; F401, G071
  *
  * Netestovano: F411, L152
  *
  ********************************************************************************************************************************************
  * @history
  *
  *   v1.1  [29-March-2022]
  *         - Uprava makra pro definovani rozlozeni KeyPad
  *         - Otestovano pro pripravek G071
  *
  *   v1.0  [29-March-2022]
  *         - 1. verze programu pouze pro pripravky F407 a F401
  *
  ********************************************************************************************************************************************
*/

#define DELAY_STEP    750                                         // Krok v ms pro pozdrzeni programu
#define DELAY_CONF		1500

#define LCD_COLS      8                                          // Pocet sloupcu pouziteho displeje
#define LCD_ROWS      2                                           // Pocet radku pouziteho displeje

#define LCD_8x2 (((LCD_COLS) == 8) && ((LCD_ROWS) == 2))
#define LCD_16x2 (((LCD_COLS) == 16) && ((LCD_ROWS) == 2))

#define KEYPAD_COLS   4                                           // Pocet sloupcu pouziteho KeyPad
#define KEYPAD_ROWS   4                                           // Pocet radku pouziteho KeyPad
//#define KEYPAD_STYLE  2                                           // Vyber znaku pro keypad, mozno uzivatelsky rozsirit/menit. Pokud bude zakomnentovano, nastavi se defaultni rozlozeni

#include "stm32_kit.h"                                     // Pripojeni globalniho konfiguracniho souboru pro praci s pripravkem.                          
#include "stm32_kit/lcd.h"                                 // Pripojeni konfiguracniho souboru pro praci s LCD.
#include "stm32_kit/keypad.h"                              // Pripojeni konfiguracniho souboru pro praci s KeyPad.
#include "stdio.h"

#ifndef KEYPAD_STYLE
  static uint8_t KeyPad_KeyMap[KEYPAD_ROWS][KEYPAD_COLS] = {      // Defaultni rozlozeni pro 4x4 KeyPad
                            '1', '2', '3', 'A',
                            '4', '5', '6', 'B',
                            '7', '8', '9', 'C',
                            '*', '0', '#', 'D'
  };
#elif (KEYPAD_STYLE == 1)
  static uint8_t KeyPad_KeyMap[KEYPAD_ROWS][KEYPAD_COLS] = {      // Alternativni rozlozeni pro 4x4 KeyPad
                            'a', 'b', 'c', 'd',
                            'e', 'f', 'g', 'h',
                            'i', 'j', 'k', 'l',
                            'm', 'n', 'o', 'p'
  };
#elif (KEYPAD_STYLE == 2)
  static uint8_t KeyPad_KeyMap[KEYPAD_ROWS][KEYPAD_COLS] = {      // Alternativni rozlozeni pro 4x4 KeyPad
                            'q', 'r', 's', 't',
                            'u', 'v', 'w', 'x',
                            'y', 'z', '[', ']',
                            '.', ',', '-', '='
  };
#endif
	
	
int fuel = 0; // 0 -> NULL, 1 -> BENZIN, 2 -> NAFTA
float fuelAmmount = 0;
#define FUEL_PRICE_BENZIN		38.81
#define FUEL_PRICE_NAFTA		35.59
  
BOARD_SETUP void setup(void) {
  SystemCoreClockUpdate();                                      
  SysTick_Config(SystemCoreClock / 10000);                      
  LCD_setup();
  KeyPad_setup();
}

void welcomeSetup(){
	char welcome_text[] = "Welcome!";
  LCD_set(LCD_CLR);
	LCD_set(LCD_CUR_OFF);
	LCD_print(welcome_text);
}

int fuelChoose(){
	uint8_t z;
	int e = 0;
	LCD_set(LCD_CLR);
	LCD_set(LCD_CUR_OFF);
	LCD_print(" VYBER  ");
	LCD_set(LCD_LINE2);
	LCD_print("<BENZIN>");
	/*do{
		z = KeyPad_getKey();
	}while(!z);
	switch(z){
		case 0x2A:
			e = 1;
		break;
		case 0x23:
			e = 2;
		break;
		default:
			fuelChoose();
		break;
	}
	delay_ms(100);
	LCD_set(LCD_CLR);
	LCD_set(LCD_CUR_OFF);
	LCD_set(LCD_LINE1);
	LCD_print("POTVRDTE");
	LCD_set(LCD_LINE2);
	LCD_print(" VYBER ");
	delay_ms(DELAY_CONF);
	if(e == 1){
		LCD_set(LCD_CLR);
		LCD_set(LCD_CUR_OFF);
		LCD_set(LCD_LINE1);
		LCD_print(" VYBER: ");
		LCD_set(LCD_LINE2);
		LCD_print(" BENZIN ");
	}else{
		LCD_set(LCD_CLR);
		LCD_set(LCD_CUR_OFF);
		LCD_set(LCD_LINE1);
		LCD_print(" VYBER: ");
		LCD_set(LCD_LINE2);
		LCD_print(" NAFTA  ");
	}
	do{
		conf = KeyPad_getKey();
	}while(!conf);
	if(conf != 0x30){
		fuelChoose();
	}*/
	
	while(1){
		do{
			z = KeyPad_getKey();
		}while(!z);
		if(z == 0x2a){
			e = 1;
			LCD_set(LCD_CLR);
			LCD_set(LCD_CUR_OFF);
			LCD_print(" VYBER  ");
			LCD_set(LCD_LINE2);
			LCD_print("<BENZIN>");
		}else if(z == 0x23){
			e = 2;
			LCD_set(LCD_CLR);
			LCD_set(LCD_CUR_OFF);
			LCD_print(" VYBER  ");
			LCD_set(LCD_LINE2);
			LCD_print("<NAFTA >");
		}else if(z == 0x38){
			return e;
		}
	}
}

int showFuelPrices(){
	uint8_t z;
	LCD_set(LCD_CLR);
	LCD_set(LCD_CUR_OFF);
//	LCD_set(LCD_LINE1);
	char benzin[8];
	char nafta[8];
	float benzin_d = FUEL_PRICE_BENZIN;
	float nafta_d = FUEL_PRICE_NAFTA;
	sprintf(benzin, "B: %.2f", benzin_d);
	LCD_print(benzin);
	LCD_set(LCD_LINE2);
	sprintf(nafta, "N: %.2f", nafta_d);
	LCD_print(nafta);
	do {
		z = KeyPad_getKey();
	} while(!z);
	welcomeSetup();
	return 0;
}

int waitForStart(){
	uint8_t z;
	while(1){
		do {
			z = KeyPad_getKey();
		} while(!z);
		
		if(z == 0x30){
			fuel = fuelChoose();
			return 1;
		}else if(z == 0x31){
			showFuelPrices();
		}else{
			waitForStart();
		}
	}
}

int waitForRefuelingConf(){
	uint8_t z;
	LCD_set(LCD_CLR);
	LCD_set(LCD_CUR_OFF);
	LCD_set(LCD_LINE1);
	LCD_print(" READY? ");
	while(1){
		do{
			z = KeyPad_getKey();
		}while(!z);
		if(z == 0x35){
			return 1;
		}
	}
}

void updateLCD(float e){
	LCD_set(LCD_CLR);
	LCD_set(LCD_CUR_OFF);
	LCD_set(LCD_LINE1);
	char str[8];
	sprintf(str, "%.2fL", e);
	LCD_print(str);
	LCD_set(LCD_LINE2);
	float price;
	if(fuel == 1){
		price = e * FUEL_PRICE_BENZIN;
	}else{
		price = e * FUEL_PRICE_NAFTA;
	}
	char price_str[8];
	sprintf(price_str, "%.2f,-", price);
	LCD_print(price_str);
}

int startRefueling(){
	uint8_t z;
	float fuel_amm = 0;
	LCD_set(LCD_CLR);
	LCD_set(LCD_CUR_OFF);
	LCD_set(LCD_LINE1);
	while(1){
		do{
			z = KeyPad_getKey();
			delay_ms(100);
			fuel_amm = fuel_amm + 0.029;
			fuelAmmount = fuel_amm;
			updateLCD(fuel_amm);
		}while(!z);
		if(z == 0x38){
			return 1;
		}
	}
}

void finalCheck(void);

int main(void) {
	welcomeSetup();
	int startEnabled = waitForStart();
	int readyToStart = waitForRefuelingConf();
	int interrupt = startRefueling();
	finalCheck();
	
	return 0;
}

void finalCheck(void){
	delay_ms(200);
	uint8_t z;
	do{
		z = KeyPad_getKey();
	}while(!z);
	fuelAmmount = 0;
	fuel = 0;
	main();
}
