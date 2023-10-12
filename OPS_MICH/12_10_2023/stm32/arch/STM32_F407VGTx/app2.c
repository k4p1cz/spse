/**
 * @file   Blikani Ledkama
 * @author Teodor Kapitanov
 * 
 */

#include "stm32_kit.h"
#include "stm32_kit/led.h"
#include "stm32_kit/button.h"

#define CLK_led 5000

int speed_multiplier = 1; // 1, 1.5, 2

const enum pin ex_ledky[] = {
    LED_EX_3,
    LED_EX_2,
    LED_EX_1,
    LED_EX_0
};

OS_TID led_0;
OS_TID led_1;
OS_TID led_2;
OS_TID led_3;
OS_TID speed;

__task void led0() {
	for (;;) {
		io_set(ex_ledky[0],1);
		delay_ms((CLK_led/2) * speed_multiplier);
		io_set(ex_ledky[0], 0);
		delay_ms((CLK_led/2) * speed_multiplier);
	}
}

__task void led1() {
	for (;;) {
		io_set(ex_ledky[1], 1);
		delay_ms((CLK_led/4) * speed_multiplier);
		io_set(ex_ledky[1], 0);
		delay_ms((CLK_led/4) * speed_multiplier);
	}
}

__task void led2() {
	for (;;) {
		io_set(ex_ledky[2], 1);
		delay_ms((CLK_led/8) * speed_multiplier);
		io_set(ex_ledky[2], 0);
		delay_ms((CLK_led/8) * speed_multiplier);
	}
}

__task void led3() {
	for (;;) {
		io_set(ex_ledky[3], 1);
		delay_ms((CLK_led/16) * speed_multiplier);
		io_set(ex_ledky[3], 0);
		delay_ms((CLK_led/16) * speed_multiplier);
	}
}

__task void speed_btn(){
	for (;;){
		if (io_read(USER_BUTTON)){
			if(speed_multiplier >= 5){
				speed_multiplier = 1;
			}else{
				speed_multiplier = speed_multiplier + 2;
			}
			os_tsk_delete(led_0);
			os_tsk_delete(led_1);
			os_tsk_delete(led_2);
			os_tsk_delete(led_3);
			
			io_set(ex_ledky[0], 1);
			io_set(ex_ledky[1], 1);
			io_set(ex_ledky[2], 1);
			io_set(ex_ledky[3], 1);
				
			led_0 = os_tsk_create(led0, 0);
			led_1 = os_tsk_create(led1, 0);
			led_2 = os_tsk_create(led2, 0);
			led_3 = os_tsk_create(led3, 0);
			
			delay_ms(200);
		}
	}
}

__task void setup() {
	LED_setup();
	BTN_setup();
	
	led_0 = os_tsk_create(led0, 0);
	led_1 = os_tsk_create(led1, 0);
	led_2 = os_tsk_create(led2, 0);
	led_3 = os_tsk_create(led3, 0);
	speed = os_tsk_create(speed_btn, 0);
	os_tsk_delete_self();
}

int main () {
	os_sys_init(setup);
}
