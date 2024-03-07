#include "stm32_kit.h"
#include "stm32_kit/uart.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>




__task void setup() {
	UART_setup();

	os_tsk_delete_self();
}
int main () {
	os_sys_init(setup);
}
