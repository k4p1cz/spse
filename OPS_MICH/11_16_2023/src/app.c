/**
 * @file   app.c
 * @author Teodor Kapitaniv
 * 
 */


#define LCD_8x2 (((LCD_COLS) == 8) && ((LCD_ROWS) == 2))
#define LCD_16x2 (((LCD_COLS) == 16) && ((LCD_ROWS) == 2))

#include "stm32_kit.h"
#include "stm32_kit/led.h"
#include "stm32_kit/lcd.h"
#include "stm32_kit/keypad.h"
#include "stm32_kit/button.h"
#include "stdio.h"

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

#define NUM_OF_MODES 4;
	

const enum pin ledky[] = {
    LED_IN_0,
    LED_IN_1,
    LED_IN_2,
    LED_IN_3,
    P_INVALID
};

const enum pin ex_ledky[] = {
    LED_EX_0,
    LED_EX_1,
    LED_EX_2,
    LED_EX_3,
    P_INVALID
};


int page_id = 0;
int update_lcd = 1;
int waitingForDoor = 0;
int mode = 0; 
int modeTime = 0;
int countMilisecs = 0;
/*
	0 - NONE SELECTED
	1 - FAST
	2 - SHIRTS
	3 - WOOL
	4 - TEST
*/

typedef struct{
	int running; // 1 - running
	int door;
	int pause;
	int canConfirm;
	int phase;
}Statuses;


OS_TID task_lcd;
OS_TID task_kbd;
OS_TID task_btn;
OS_TID task_count;

Statuses Sts;

__task void LCD_main() {
	int modeMs = 0;
	int wash = 0;
	int rinse = 0;
	int spin = 0;
	int presoak = 0;
	int remainingTime = 0;
	char time[8];
	int	loc_secs = 0;
	int loc_milisecs = 0;
	int loc_mins = 0;
	for (;;) {
		if(update_lcd == 1){
			LCD_set(LCD_CUR_OFF);
			LCD_set(LCD_LINE1);
			switch(page_id){
				case 0:
					LCD_print(" PRACKA ");
					LCD_set(LCD_LINE2);
					LCD_print(" * 0 #  ");
					update_lcd = 0;
				break;
				case 1:
					LCD_print("  FAST  ");
					LCD_set(LCD_LINE2);
					LCD_print(" 15 min ");
					mode = 1;
					modeTime = 900;
				break;
				case 2:
					LCD_print(" SHIRTS ");
					LCD_set(LCD_LINE2);
					LCD_print(" 45 min ");
					mode = 2;
					modeTime = 2700;
				break;
				case 3:
					LCD_print("  WOOL  ");
					LCD_set(LCD_LINE2);
					LCD_print(" 90 min ");
					mode = 3;
					modeTime = 5400;
				break;
				case 4:
					LCD_print("  TEST  ");
					LCD_set(LCD_LINE2);
					LCD_print(" 1 min ");
					mode = 4;
					modeTime = 10;
				break;
				case 5:
					LCD_print(" CLOSE  ");
					LCD_set(LCD_LINE2);
					LCD_print("  DOOR  ");
				break;
				case 6:
					LCD_print(" CAN'T  ");
					LCD_set(LCD_LINE2);
					LCD_print("  OPEN  ");
				break;
			}
		}else if(update_lcd == 2){
			LCD_set(LCD_CUR_OFF);
			LCD_set(LCD_LINE1);
			LCD_print(" CLOSE  ");
			LCD_set(LCD_LINE2);
			LCD_print("  DOOR  ");
			update_lcd = 0;
			waitingForDoor = 1;
			
		}else if(update_lcd == 4){
			LCD_set(LCD_CUR_OFF);
			LCD_set(LCD_LINE1);
			LCD_print(" PAUSE  ");
			LCD_set(LCD_LINE2);
			LCD_print("0 RESUME");
		}else if(update_lcd == 5){
			LCD_set(LCD_CUR_OFF);
			LCD_set(LCD_LINE1);
			modeMs = modeTime * 1000;
			wash = modeMs*0.4;
			rinse = modeMs*0.3;
			spin = modeMs*0.15;
			presoak = modeMs - (wash + rinse + spin);
			remainingTime = modeMs - countMilisecs;
			if(remainingTime <= 0){
				update_lcd = 6;
				//Sts.running = 1;
			}
			loc_secs = 0;
			loc_milisecs = remainingTime;
			loc_mins = 0;
				
			while(loc_milisecs >= 1000){
				loc_secs++;
				loc_milisecs = loc_milisecs-1000;
			}
			while(loc_secs > 60){
				loc_mins++;
				loc_secs = loc_secs-60;
			}
			sprintf(time, " %02d:%02d  ", loc_mins, loc_secs);
			
			if(presoak > remainingTime){
				LCD_print("PRESOAK ");
			}else if((wash+presoak) > remainingTime){
				LCD_print("  WASH  ");
			}else if((rinse+wash+presoak) > remainingTime){
				LCD_print(" RINSE  ");
			}else{
				LCD_print("  SPIN  ");
			}
			LCD_set(LCD_LINE2);
			LCD_print(time);
		}else if(update_lcd == 6){
			LCD_set(LCD_CUR_OFF);
			LCD_set(LCD_LINE1);
			LCD_print("  DONE  ");
			LCD_set(LCD_LINE2);
			LCD_print("0 - BACK");
			modeMs = 0;
			wash = 0;
			rinse = 0;
			spin = 0;
			presoak = 0;
			remainingTime = 0;
			loc_secs = 0;
			loc_milisecs = 0;
			loc_mins = 0;
		}
	}
}

__task void KBD_main(){
	for(;;){
		uint8_t z;
		do{
			z = KBD_read();
		}while(!z);
		if(Sts.running == 0){
			switch(z){
				case 0x23: // #
					if(page_id <= 3){
						page_id++;
						update_lcd = 1;
					}
				break;
				case 0x2A: // *
					if(page_id != 0){
						page_id--;
						update_lcd = 1;
					}
				break;
				case 0x30:
					if(Sts.door == 0){
						update_lcd = 2;
					}else{
						update_lcd = 5;
					}
				break;
			}
		}else{
			switch(z){
				case 0x30:
					if(update_lcd == 6 && Sts.pause != 1){
						Sts.phase = 0;
						Sts.running = 0;
						Sts.canConfirm = 0;
						countMilisecs = 0;
						page_id = 0;
						mode = 0;
						update_lcd = 1;
					}else if(Sts.pause == 0 && update_lcd == 5){
						Sts.pause = 1;
						update_lcd = 4;
					}else if(Sts.pause == 1){
						Sts.pause = 0;
						update_lcd = 5;
					}
				break;
			}
			
		}
		delay_ms(200);
	}
}

__task void BTN_main(){
	for(;;){
		if (io_read(USER_BUTTON)){
			if(Sts.door == 0){
				for(int i = 0; i < 4; i++){
					io_set(ex_ledky[i], 0);
				} 
				Sts.door = 1;
				if(waitingForDoor == 1){
					update_lcd = 5;
					Sts.running = 1;
					waitingForDoor = 0;
				}
			}else{
				if(Sts.running != 1){
					for(int i = 0; i < 4; i++){
						io_set(ex_ledky[i], 1);
					} 
					Sts.door = 0;
				}
			}
			delay_ms(500);
		}
	}
}

__task void count(){
	while(1){
		if(Sts.running == 1 && Sts.pause == 0){
			delay_ms(1);
			countMilisecs = countMilisecs + 1;
		}
	}
}

__task void setup() {
	LED_setup();
	LCD_setup();
	KBD_setup();
	BTN_setup();
	Sts.door = 0;
	Sts.pause = 0;
	Sts.running = 0;
	Sts.phase = 1;
	Sts.canConfirm = 0;
	task_lcd = os_tsk_create(LCD_main, 0);
	task_kbd = os_tsk_create(KBD_main, 0);
	task_btn = os_tsk_create(BTN_main, 0);
	task_count = os_tsk_create(count, 0);
	os_tsk_delete_self();
}

int main () {
	os_sys_init(setup);
}

