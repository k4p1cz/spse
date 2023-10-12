#define KEYPAD_ROWS 4
#define KEYPAD_COLS 3

#include "stm32_kit.h"
#include "stm32_kit/lcd.h"
#include "stm32_kit/keypad.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef KEYPAD_STYLE
	static uint8_t KeyPad_KeyMap[KEYPAD_ROWS][KEYPAD_COLS] = {
		'1','2','3',
		'4','5','6',
		'7','8','9',
		'.','0','#',
	};
#endif

BOARD_SETUP void setup(void) {
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/10000);
	LCD_setup();
	KeyPad_setup(); 
	LCD_set(LCD_CUR_OFF);
	LCD_set(LCD_ON);
}

float nactiCislo(void);

int main() {
	char str[8];
	float cena, l, cenab, cenan;
	uint8_t vyber;

	LCD_print("Benzin:");
	LCD_set(LCD_LINE2);
	cenab = nactiCislo();
	
	LCD_set(LCD_CLR);
	LCD_print(" Nafta:");
	LCD_set(LCD_LINE2);
	cenan = nactiCislo();
	
	while(1) {
		l = 0;
		vyber = 0;
		LCD_set(LCD_CLR);
		
		LCD_print(" 1 - Benz");
		LCD_set(LCD_LINE2);
		LCD_print("2 - Naft");
		
		while(vyber!='1' && vyber!='2'){
			vyber = KeyPad_getKey();
		}
			
		cena = (vyber == '1' ? cenab : cenan);
		
		LCD_set(LCD_CLR);

		LCD_set(LCD_LINE1);LCD_print("0.0 l");
		LCD_set(LCD_LINE2);LCD_print("0.0 lKc");
		
		while(1) {
			if(KeyPad_getKey() == '4') {
				l += 0.1f;
				
				delay_ms(1000);
				LCD_set(LCD_CLR);
				
				sprintf(str,"%.1f l",l);
				LCD_set(LCD_LINE1);LCD_print(str);
				
				sprintf(str,"%.2fKc",cena*l);
				LCD_set(LCD_LINE2);LCD_print(str);
			}
			if(KeyPad_getKey() == '5' || l>=50) {
				break;
			}
		}
	}
}

float nactiCislo(void) {
	char string[8] = "";
	uint8_t znak,tecka = 0;
	
	do {
		znak = KeyPad_getKey();
		if (znak != '#' && (tecka == 0 || znak != '.') && znak) {
			LCD_symbol(znak);
			sprintf(string,"%s%c",string,znak);
			if (znak == '.') { tecka = 1;}
		}
	} while(znak!='#');
	
	return atof(string);
}
