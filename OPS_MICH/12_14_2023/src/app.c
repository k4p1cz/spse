/**
 * @file   	app.c
 * @author Teodor Kapitanov
 * 
 */

#include "stm32_kit.h"
#include "stm32_kit/lcd.h"
#include "stm32_kit/led.h"
#include "stm32_kit/keypad.h"
#include <stdio.h>

#ifndef KEYPAD_STYLE
  static uint8_t KBD_MAP[KEYPAD_ROWS][KEYPAD_COLS] = {      // Defaultni rozlozeni pro 4x4 KeyPad
    '1', '2', '3',// 'A',
    '4', '5', '6',// 'B',
    '7', '8', '9',// 'C',
    '*', '0', '#',// 'D'
  };
#elif (KEYPAD_STYLE == 1)
  static uint8_t KBD_MAP[KEYPAD_ROWS][KEYPAD_COLS] = {      // Alternativni rozlozeni pro 4x4 KeyPad
    'a', 'b', 'c', 'd',
    'e', 'f', 'g', 'h',
    'i', 'j', 'k', 'l',
    'm', 'n', 'o', 'p'
  };
#elif (KEYPAD_STYLE == 2)
  static uint8_t KBD_MAP[KEYPAD_ROWS][KEYPAD_COLS] = {      // Alternativni rozlozeni pro 4x4 KeyPad
    'q', 'r', 's', 't',
    'u', 'v', 'w', 'x',
    'y', 'z', '[', ']',
    '.', ',', '-', '='
  };
#endif


OS_TID id_time;
OS_TID id_lcd;
OS_TID id_keypad;
OS_SEM lock;

int time_work = 10000;
int time_rest = 5000;
int time_longrest = 7500;


int countMs = 0;
int init = 0;
int state = 0;
int countCycles = 0;
int remainingTime = 10000;
int pause = 1;
int mode = 1; // 1 - work, 2 - rest, 3 - long rest, 4 - skip
char modeName[8] = "  WORK  ";

#define LCD_8x2 (((LCD_COLS) == 8) && ((LCD_ROWS) == 2))

void showWelcomeLCD(int e){
	LCD_set(LCD_CUR_OFF);
	LCD_set(LCD_LINE1);
	LCD_print(modeName);
	LCD_set(LCD_LINE2);
	
	int secs;
	int mins;
	int milisecs = e;
	char print[8];
	while(milisecs >= 1000){
		secs++;
		milisecs = milisecs - 1000;
	}
	while(secs >= 60){
		mins++;
		secs = secs - 60;
	}
	snprintf(print, 8, "  %02d:%02d  ", mins, secs);
	LCD_print(print);
	LCD_set(LCD_CUR_OFF);
}

__task void Time() {
	for (;;) {
		if(state == 1 && init == 1){
			switch(mode){
				case 1:
					remainingTime = time_work;
					init = 0;
				break;
				case 2:
					remainingTime = time_rest;
					init = 0;
				break;
			}
		}
		if(pause != 1){
			remainingTime = remainingTime - 1;
			delay_ms(1);
		}
	}
}
__task void LCD(){
	showWelcomeLCD(time_work);
	int sec;
	int mins;
	int milisecs;
	for(;;){
		if(state == 1){
			sec = 0;
			mins = 0;
			milisecs = 0;
			LCD_set(LCD_LINE1);
			LCD_print(modeName);
			char time[8];
			milisecs = remainingTime;
			while(milisecs >= 1000){
				sec++;
				milisecs = milisecs - 1000;
			}
			while(sec >= 60){
				mins++;
				sec = sec - 60;
			}
			snprintf(time, 8, " %02d:%02d  ", mins, sec);
			LCD_set(LCD_LINE2);
			LCD_print(time);
			if(remainingTime <= 0){
				countCycles++;
				pause = 1;
				state = 0;
				mode++;
				init = 1;
				remainingTime = 0;
				switch(mode){
					case 2:
						sprintf(modeName, "  REST  ");
						showWelcomeLCD(7000);
					break;
				}
			}
		}
	}
}
__task void Keypad(){
	for(;;){
		uint8_t z;
		do{
			z = KBD_read();
		}while(!z);
		if(state == 0){
			switch(z){
				case '#':
					state = 1;
					init = 1;
					pause = 0;
					id_time = os_tsk_create(Time, 0);
				break;
			}
		}else{
			switch(z){
				case '#':
					
				break;
			}
		}
	}
}

__task void setup() {
	
	KBD_setup();
	LCD_setup();
	LED_setup();
	
	os_sem_init(&lock, 0);
	os_sem_send(&lock);
	
	id_keypad = os_tsk_create(Keypad, 0);
	id_lcd = os_tsk_create(LCD, 0);
	os_tsk_delete_self();
}

int main () {
	os_sys_init(setup);
}

