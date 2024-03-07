#include "stm32_kit.h"
#include "stm32_kit/uart.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

OS_TID uartProcess;

__task void uartProcessFunc(){
	char buff[999];
	int buff_len = 0;
	uint8_t e;
	int numOfArgs = 0;
	char cmd[100];
	for(;;){
		e = UART_getc(); // nactu znak
		switch(e){
			case '\b': // backspace - NEMUSI FUNGOVAT 100%
				buff_len--;
				buff[buff_len] = 0x00;
			break;
			case 0x0D: // enter
				
			
			
			
				// vycistim si pole buffer a pole command
				memset(buff, 0x00, 999);
				memset(cmd, 0x00, 100);
			break;
			default: // pokud ne backspace ani enter - vypsat znak a ulozit si ho do bufferu
				UART_putc(e);
				buff[buff_len] = e;
				buff_len++;
				break;
		}
	}
}

__task void setup() {
	UART_setup();

	uartProcess = os_tsk_create(uartProcessFunc, 0); // vytvorim task
	os_tsk_delete_self();
}
int main () {
	os_sys_init(setup);
}
