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
#include "stm32_kit/button.h"

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
__task void button(void);
__task void buttonPause(void);
int getTimeFromUser(int e);
	

OS_TID id_timer;
OS_TID id_timerSetup;
OS_TID id_lcd;
OS_TID id_keypad;
OS_TID id_button;
OS_TID id_buttonPause;

OS_SEM semaphore;
	
int workTimer = 0;
int restTimer = 0;
int timerSeconds = 0;
int cycle = 0; // 0 work , 1 rest
int pause = 0; 
	
	

#define LCD_8x2 (((LCD_COLS) == 8) && ((LCD_ROWS) == 2))

__task void buttonPause(){
	delay_ms(500);
	for(;;){
		if(io_read(USER_BUTTON)){
			pause ^= 1;
			int led = pause;
			led ^= 1;
			io_set(cycle?LED_EX_0 : LED_EX_3, pause);
			io_set(LED_EX_2, led);
			io_set(LED_EX_1, led);
			os_sem_wait(&semaphore, 0xffff);
			LCD_set(LCD_LINE1);
			LCD_print(pause?cycle?"PAUSED        " : "PAUSED        " : cycle?"REST         " : "WORK        ");
			os_sem_send(&semaphore);
			delay_ms(500);
		}
	}
}

__task void timerSetup(){
	workTimer = getTimeFromUser(0);
	restTimer = getTimeFromUser(1);
	timerSeconds = workTimer;
	
	id_button = os_tsk_create(button, 0);
	os_tsk_delete_self();
}


__task void button(void){
	for(;;){
		if(io_read(USER_BUTTON)){
			id_timer = os_tsk_create(timer, 0);
			id_buttonPause = os_tsk_create(buttonPause, 0);
			os_tsk_delete_self();
		}
	}
}

__task void timer(void){
	char l1[9];
	int mins, secs;
	
	io_set(LED_EX_0, 1);
	io_set(LED_EX_3, 1);
	io_set(cycle?LED_EX_0 : LED_EX_3, 0);
	
	for(;timerSeconds;timerSeconds--){
		while(pause);
		
		mins = timerSeconds/60;
		secs = timerSeconds%60;
		LCD_set(LCD_LINE1);
		os_sem_wait(&semaphore, 0xffff);
		LCD_print(cycle?"REST     ":"WORK      ");
		LCD_print("ZBYVA:   ");
		LCD_set(LCD_LINE2);
		snprintf(l1, 9, "%d:%d      ", mins, secs);
		LCD_print(l1);
		os_sem_send(&semaphore);
		delay_ms(1000);
	}
	//id_timer = os_tsk_create(timer, 0);
	if(cycle == 0){
		cycle = 1;
		timerSeconds = restTimer;
	}else{
		cycle = 0;
		timerSeconds = workTimer;
	}
	id_timer = os_tsk_create(timer, 0);
	os_tsk_delete_self();
}

int getTimeFromUser(int e){
	uint8_t ch;
	int mins, secs;
	char time[8];
	char *timeP = time;
	int l = 0;
	LCD_set(LCD_CLR);
	LCD_set(LCD_CUR_OFF);
	LCD_set(LCD_CUR_NO_BLINK);
	
	LCD_set(LCD_LINE1);
	if(e == 0) LCD_print("CAS WORK:");
	else LCD_print("CAS REST:");
	
	LCD_set(LCD_LINE2);
	
	for(;;){
		ch = waitForKeyPress();
		if(ch == '#') break;
		LCD_symbol(ch);
		delay_ms(100);
		*timeP++ = ch;
		l++;
	}
	
	LCD_set(LCD_CLR);
	LCD_set(LCD_LINE1);
	LCD_print("ZMACKNI ");
	LCD_set(LCD_LINE2);
	LCD_print("TLACITKO");

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
	return mins*60 + secs;
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
	BTN_setup();

	os_sem_init(&semaphore, 0);
	os_sem_send(&semaphore);
	id_timerSetup = os_tsk_create(timerSetup, 0);
	os_tsk_delete_self();
}

int main () {
	os_sys_init(setup);
}

