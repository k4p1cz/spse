/**
 * @file   Blikani Ledkama
 * @author Teodor Kapitanov
 * 
 */

#include "stm32_kit.h"
#include "stm32_kit/led.h"


OS_TID t_ledgreen;
OS_TID t_ledorange;

__task void LedGreen() {
	for (;;) {
		io_set(LED_IN_0, 1);
		delay_ms(200);
		io_set(LED_IN_0, 0);
		delay_ms(200);
	}
}

__task void LedOrange() {
	for (;;) {
		io_set(LED_IN_2, 1);
		delay_ms(400);
		io_set(LED_IN_2, 0);
		delay_ms(400);
	}
}

__task void setup() {
	LED_setup();
	
	t_ledgreen = os_tsk_create(LedGreen, 0);
	t_ledorange = os_tsk_create(LedOrange, 0);
	os_tsk_delete_self();
}

int main () {
	os_sys_init(setup);
}
