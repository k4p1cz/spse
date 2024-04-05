/**
 * @file   <nazev>.c
 * @author <Jmeno Prijmeni>
 * 
 */

#include "stm32_kit.h"
#include "stm32_kit/Keypad.h"
#include "stm32_kit/lcd.h"
#include "stm32_kit/led.h"
#include <stdio.h>

//MAPA KLAVESNICE DULEZITE NEZAPOMENOUT!!!!!
static uint8_t KBD_MAP[KEYPAD_ROWS][KEYPAD_COLS] = {      // Defaultni rozlozeni pro 4x4 KeyPad
    '1', '2', '3',// 'A',
    '4', '5', '6',// 'B',
    '7', '8', '9',// 'C',
    '*', '0', '#',// 'D'
  };

//definice tasku
OS_TID lcd_control, kbd_control, led_control;

//definice globalnich promennych
int count = 0, item = 1, currentItem = 0;
int totaldrunk[4];

//task pro vypis na LCD
__task void LCD_Control() {
	int i = 0;
	for (;;) {
		if(currentItem != item && count != 15){
			currentItem = item;
			
			//vycisteni displeje a nastaveni zpet na radek 1
			LCD_set(LCD_CLR);
			LCD_set(LCD_LINE1);
			LCD_set(LCD_CUR_OFF);
			LCD_set(LCD_CUR_NO_BLINK);
			//rozhodnuti o vypisu co se ma vypsat
			switch(item){
				case 0:{
					LCD_print("rum");
					break;
				}
				case 1:{
					LCD_print("vodka");
					break;
				}
				case 2:{
					LCD_print("pivo");
					break;
				}
				case 3:{
					LCD_print("konak");
					break;
				}
			}
			LCD_set(LCD_LINE2);
			LCD_print("<*    #>");
		}
		//pokud je pocet piti 15, mog opps
		if (count == 15){
			LCD_set(LCD_CLR);
			LCD_set(LCD_LINE1);
			LCD_print("ozralo");
			LCD_set(LCD_LINE2);
			LCD_print("   0    ");
			delay_ms(500);
			for(int i = 0; i < 4; i++){
				LCD_set(LCD_CLR);
				LCD_set(LCD_LINE1);
				if(count != 15) break;
				char string[8];
				switch(i){
					case 0:{
						sprintf(string, "%d rum", totaldrunk[i]);
						LCD_print(string);
						break;
					}
					case 1:{
						sprintf(string, "%d vodka", totaldrunk[i]);
						LCD_print(string);
						break;
					}
					case 2:{
						sprintf(string, "%d pivo", totaldrunk[i]);
						LCD_print(string);
						break;
					}
					case 3:{
						sprintf(string, "%d konak", totaldrunk[i]);
						LCD_print(string);
						break;
					}
				}
				delay_ms(500);
			}
		}
		delay_ms(200);
	}
}

//task pro ziskavani klaves a rozhodnuti co s tim vysledkem
__task void KBD_Control() {
	uint8_t znak;
	for (;;) {
		//nacteni znaku z klavesnice, loop se opakuje nez se neco nacte
		do{
			znak = KBD_read();
		}while(!znak);
		
		//rozhodnuti co s vysledkem
		switch(znak){
			case '0':{ //potvrzeni piti
				if(count < 15){
					count++;
					totaldrunk[item] += 1;
				}
				else{
					count = 0;
					totaldrunk[0] = 0;
					totaldrunk[1] = 0;
					totaldrunk[2] = 0;
					totaldrunk[3] = 0;
				}
				break;
			}
			case '*':{
				if(item > 0) item--;
				else item = 3;
				break;
			}
			case '#':{
				if(item < 3) item++;
				else item = 0;
				break;
			}
		}
		delay_ms(200);
	}
}

__task void LED_Control() {
	int n = 0;
	for (;;) {
		if(count <  15){
			int bin[4] = {0,0,0,0};
			int dec = count;
			int i = 0;
			//prevod dec na bin
			while(dec > 0){
				bin[i] = dec % 2;
				dec /= 2;
				i++;
			}
			
			io_set(LED_EX_0, bin[0]?0:1);
			io_set(LED_EX_1, bin[1]?0:1);
			io_set(LED_EX_2, bin[2]?0:1);
			io_set(LED_EX_3, bin[3]?0:1);
		}
		else{
			
			//blikani ledek kdyz jsme ochlasti a mame prepite
			io_set(LED_EX_0, n?0:1);
			io_set(LED_EX_1, n?0:1);
			io_set(LED_EX_2, n?0:1);
			io_set(LED_EX_3, n?0:1);
			
			n = n?0:1;
			delay_ms(500);
		}
	}
}

__task void setup() {
	KBD_setup();
	LCD_setup();
	LED_setup();
	
	lcd_control = os_tsk_create(LCD_Control, 0);
	kbd_control = os_tsk_create(KBD_Control, 0);
	led_control = os_tsk_create(LED_Control, 0);
	
	os_tsk_delete_self();
}

int main () {
	os_sys_init(setup);
}

