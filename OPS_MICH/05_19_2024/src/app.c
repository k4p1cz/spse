/**
 * @file   app.c
 * @author Kapitanov, Blaha
 * 
 */
#define LCD_8x2 (((LCD_COLS) == 8) && ((LCD_ROWS) == 2))
#include "stm32_kit.h"
#include "stm32_kit/led.h"
#include "stm32_kit/lcd.h"
#include "stm32_kit/keypad.h"
#include "stdio.h"
static uint8_t KBD_MAP[KEYPAD_ROWS][KEYPAD_COLS] = {
	'1', '2', '3',// 'A',
	'4', '5', '6',// 'B',
	'7', '8', '9',// 'C',
	'*', '0', '#',// 'D'
};

typedef struct{
	char name[10];
	int perc;
}CHLAST;
typedef struct{
	float promile;
	int vypito;
}STATUS;


STATUS userStatus = {0,0};
CHLAST alkohol[4] = {
	{" Becher ", 40},
	{"  Rum  ", 90},
	{"  Vodka ", 42},
	{" Slivka ", 60}
};

OS_TID lcd_task;
OS_TID kbd_task;
OS_TID timer_task;

int update = 1;
int page;

__task void LCDHandler(){
	for(;;){
		if(update == 1){
			LCD_set(LCD_CUR_OFF);
			LCD_set(LCD_LINE1);
			if(userStatus.promile > 5){
				LCD_print("NA KARY");
				LCD_set(LCD_LINE2);
				LCD_print("NA KARY");
			}else{
				LCD_print(alkohol[page].name);
				LCD_set(LCD_LINE2);
				char print[8];
				sprintf(print, "%d  %.2f%%", userStatus.vypito, userStatus.promile);
				LCD_print(print);
			}
			update = 0;
		}else if(update == 2){
			LCD_set(LCD_CLR);
			float hmotnost_alkoholu = (40 * alkohol[page].perc *0.8)/100;
			float promile = hmotnost_alkoholu / (75*0.7);
			userStatus.vypito += 1;
			userStatus.promile += promile;
			LCD_set(LCD_LINE1);
			LCD_print("Pijes...");
			delay_ms(500);
			int i;
			LCD_set(LCD_LINE2);
			for(i = 0; i < 8; i++){
				LCD_symbol('#');
				delay_ms(200);
			}
			update = 1;
			LCD_set(LCD_CLR);
		}
	}
}
__task void KBDHandler(){
	uint8_t key;
	for(;;){
		do{
			key = KBD_read();
		}while(!key);
		switch(key){
		case '*':
			if(page < 1){
				page = 3;
			}else{
				page--;
			}
			update = 1;
			break;
		case '#':
			if(page > 2){
				page = 0;
			}else{
				page++;
			}
			update = 1;
			break;
		case '0':
			update=2;
			break;
		}
	}
}

__task void timerHandler(){
	for(;;){
		if(userStatus.promile > 0){
			delay_ms(2000);
			userStatus.promile -= 0.01;
			update =1;
		}
	}
}

__task void setup() {
	LED_setup();
	LCD_setup();
	KBD_setup();
	
	LCD_set(LCD_CLR);
	LCD_set(LCD_LINE1);
	LCD_set(LCD_CUR_OFF);
	LCD_set(LCD_CUR_NO_BLINK);
	
	lcd_task = os_tsk_create(LCDHandler, 0);
	kbd_task = os_tsk_create(KBDHandler, 0);
	timer_task = os_tsk_create(timerHandler, 0);
	os_tsk_delete_self();
}

int main () {
	os_sys_init(setup);
}


