/**
 * @file   	app.c
 * @author Teodor Kapitanov
 * 
 */
 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stm32_kit.h"
#include "stm32_kit/lcd.h"
#include "stm32_kit/led.h"
#include "stm32_kit/keypad.h"

#ifndef KEYPAD_STYLE
  static uint8_t KBD_MAP[KEYPAD_ROWS][KEYPAD_COLS] = {      // Defaultni rozlozeni pro 4x4 KeyPad
    '1', '2', '3',// 'A',
    '4', '5', '6',// 'B',
    '7', '8', '9',// 'C',
    ':', '0', '#',// 'D'
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
	
uint8_t waitForKeyPress(void);
__task void timer(void);
	

OS_TID id_timer;
OS_TID id_timerSetup;
OS_TID id_lcd;
OS_TID id_keypad;

	
int timerSeconds = 0;
	
	

#define LCD_8x2 (((LCD_COLS) == 8) && ((LCD_ROWS) == 2))

__task void Keypad(){
	for(;;){
		
	}
}
__task void LCD(){
	for(;;){
		
	}
}

__task void timerSetup(){
	uint8_t ch;
	int mins, secs;
	char time[8];
	char *timeP = time;
	int l = 0;
	LCD_set(LCD_CUR_OFF);
	LCD_set(LCD_CUR_NO_BLINK);
	LCD_set(LCD_LINE1);
	LCD_print("CAS:      ");
	LCD_set(LCD_LINE2);
	for(;;){
		for(l=0;;l++){
			ch = waitForKeyPress();
			if(ch == '#') break;
			LCD_symbol(ch);
			delay_ms(100);
			*timeP++ = ch;
			l++;
		}
		
		char *tok;
		
		tok = strtok(time, ":");
		int j = 0;
		while(tok != NULL){
			if(j == 0){
				mins = atoi(tok);
				j++;
			}else if(j == 1){
				secs = atoi(tok);
				j++;
			}
			tok = strtok(NULL, ";");
		}
		LCD_set(LCD_LINE2);
		snprintf(time, 8, "%dm %ds", mins, secs);
		timerSeconds = mins*60 + secs;
		LCD_print(time);
		delay_ms(1000);
		id_timer = os_tsk_create(timer, 0);
		os_tsk_delete_self();
	}
}

__task void timer(void){
	
}

uint8_t waitForKeyPress(void){
	uint8_t ch;
	do{
			ch = KBD_read();
	}while(!ch);
	return ch;
}
	
__task void setup() {
	
	KBD_setup();
	LCD_setup();
	LED_setup();

	//id_keypad = os_tsk_create(Keypad, 0);
	//id_lcd = os_tsk_create(LCD, 0);
	id_timerSetup = os_tsk_create(timerSetup, 0);
	os_tsk_delete_self();
}

int main () {
	os_sys_init(setup);
}

