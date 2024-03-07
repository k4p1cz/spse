#include "stm32_kit.h"
#include "stm32_kit/uart.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

OS_TID uartProcess;

typedef struct{
	int ip[4];
	int mask[4];
	int blockSize;
	int numOfAddress;
	int numOfHosts;
	int hosts[2]; // 1. a posledni host
	int networkIP[4];
	int broadcastIP[4];
	int CIDR;
}addressInfo;

char newLine[100] = "\r\n";
char clear[100] = "\033[2J\033[1;1H";

__task void uartProcessFunc(){
	char buff[999];
	int buff_len = 0;
	uint8_t e;
	int numOfArgs = 0;
	int enteredDetails = 0;
	int enteredIP = 0;
	int enteredMask = 0;
	char cmd[100];
	char ip[100];
	for(;;){
		e = UART_getc(); // nactu znak
		switch(e){
			case '\b': // backspace - NEMUSI FUNGOVAT 100%
				buff_len--;
				buff[buff_len] = 0x00;
			break;
			case 0x0D: // enter
				if(strcmp(buff, "clear") == 0){
					UART_write(clear, strlen(clear));
				}
				if(enteredDetails == 0){
					numOfArgs = sscanf(buff, "%s %s", cmd, ip); // rozdelim si buffer do nekolika casti
					if(numOfArgs > 1){
						if(0 == strcmp(cmd, "ip")){ // overuju, jestli command, co uzivatel zadal je ip
							UART_write(newLine, strlen(newLine));
							enteredIP = 1;
							if(enteredIP == 1 && enteredMask == 1){
								// process
							}
						}
						if(0 == strcmp(cmd, "mask")){
						
						}
					}
				}
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
	UART_write(clear, strlen(clear));
	uartProcess = os_tsk_create(uartProcessFunc, 0); // vytvorim task
	os_tsk_delete_self();
}
int main () {
	os_sys_init(setup);
}
