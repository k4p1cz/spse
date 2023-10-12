/**
 * @file   Led podle keypad
 * @author Teodor Kapitanov
 * 
 */

#include "stm32_kit.h"
#include "stm32_kit/led.h"
#include "stm32_kit/keypad.h"

const enum pin ledky[] = {
    LED_IN_0,
    LED_IN_1,
    LED_IN_2,
    LED_IN_3
};
const enum pin ex_ledky[] = {
    LED_EX_3,
    LED_EX_2,
    LED_EX_1,
    LED_EX_0
};
static uint8_t KBD_MAP[KEYPAD_ROWS][KEYPAD_COLS] = {    
    '1', '2', '3',// 'A',
    '4', '5', '6',// 'B',
    '7', '8', '9',// 'C',
    '*', '0', '#',// 'D'
};

int pressed = 0;
int numOfLeds = 0;
uint8_t pressed_num;
int debug = 0;

void turnOnLeds(int e){
	for(int i = 0; i < e; i++){
		
		if(i > 3){
			io_set(ex_ledky[i-4], 0);
		} else {
			io_set(ledky[i], 1);
		}
	}
}


OS_TID keypad;
OS_TID led;


__task void keypad_tsk(){
	while(1){
		do {
			pressed_num = KBD_read();
		} while(!pressed_num);
		pressed = 1;
		pressed_num = pressed_num - '0';
	}
	
}
__task void led_tsk(){
	while(1){
		if(pressed == 1){
			for(int i = 0; i < 4; i++){
				io_set(ledky[i], 0);
				io_set(ex_ledky[i], 1);
			}
			pressed = 0;
		}
		
		turnOnLeds(pressed_num);
		
	}
}



__task void setup() {
	LED_setup();
	KBD_setup();
	keypad = os_tsk_create(keypad_tsk, 0);
	led = os_tsk_create(led_tsk, 0);

	os_tsk_delete_self();
}

int main () {
	os_sys_init(setup);
}
