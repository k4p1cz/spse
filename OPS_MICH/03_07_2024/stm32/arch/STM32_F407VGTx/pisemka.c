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
char ipLoaded[100] = "IP loaded!\r\n";
char maskLoaded[100] = "Mask loaded!\r\n";

addressInfo calculateInfo(char ip[], char mask[]);
void displayInfo(addressInfo e);

__task void uartProcessFunc(){
	addressInfo info;
	char buff[999];
	int buff_len = 0;
	uint8_t e;
	int numOfArgs = 0;
	int enteredDetails = 0;
	int enteredIP = 0;
	int enteredMask = 0;
	char ip_[100];
	char mask_[100];
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
					numOfArgs = sscanf(buff, "%s %s %s", cmd, ip, mask_); // rozdelim si buffer do nekolika casti
					if(numOfArgs > 2){
						if(0 == strcmp(cmd, "ip")){ // overuju, jestli command, co uzivatel zadal je ip
							UART_write(newLine, strlen(newLine));
							enteredIP = 1;
							strcpy(ip_, ip);
							UART_write(ipLoaded, strlen(ipLoaded));
							//if(enteredIP == 1 && enteredMask == 1){
								info = calculateInfo(ip_, mask_);
								enteredDetails = 1;

							//}
						}
						/*if(0 == strcmp(cmd, "mask")){
							UART_write(newLine, strlen(newLine));
							enteredMask = 1;
							strncpy(mask_, ip, 100);
							UART_write(maskLoaded, strlen(maskLoaded));
							if(enteredIP == 1 && enteredMask == 1){
								info = calculateInfo(ip_, mask_);
								enteredDetails = 1;
								
							}
						}*/
					} // pokud jiz mame vsechny detaily
					if(0 == strcmp(buff, "show")){
						displayInfo(info);
					}
				// vycistim si pole buffer a pole command
				memset(buff, 0x00, 999);
				memset(cmd, 0x00, 100);
				memset(ip, 0x00, 100);
			break;
			default: // pokud ne backspace ani enter - vypsat znak a ulozit si ho do bufferu
				UART_putc(e);
				buff[buff_len] = e;
				buff_len++;
				break;
		}
	}
}

addressInfo calculateInfo(char ip[], char mask[]){
	addressInfo rtrn;
	int i;
	char *token = strtok(ip, ".");
	char *token2 = strtok(mask, ".");
	for(i=0; i<4; i++){
		rtrn.ip[i] = atoi(token);
		rtrn.mask[i] = atoi(token2);
		token = strtok(NULL, ".");
		token2 = strtok(NULL, ".");
	}
	
	rtrn.blockSize = 256-rtrn.mask[3];
	rtrn.numOfAddress = rtrn.blockSize;
	rtrn.numOfHosts	= rtrn.blockSize-2;
	rtrn.networkIP[0] = rtrn.ip[0];
	rtrn.networkIP[1] = rtrn.ip[1];
	rtrn.networkIP[2] = rtrn.ip[2];
	rtrn.networkIP[3] = 0;
	switch(rtrn.mask[3]){
		case 0:
			rtrn.CIDR = 24;
			break;
		case 128:
			rtrn.CIDR = 25;
			break;
		case 192:
			rtrn.CIDR = 26;
			break;
		case 224:
			rtrn.CIDR = 27;
			break;
		case 240:
			rtrn.CIDR = 28;
			break;
		case 248:
			rtrn.CIDR = 39;
			break;
		case 252:
			rtrn.CIDR = 30;
			break;
		case 254:
			rtrn.CIDR = 31;
			break;
		case 255:
			rtrn.CIDR = 32;
			break;
	}
	
	rtrn.hosts[0] = rtrn.networkIP[3]+1;
	rtrn.hosts[1] = rtrn.mask[3]-2;
	rtrn.broadcastIP[0] =	rtrn.ip[0];
	rtrn.broadcastIP[0] =	rtrn.ip[1];
	rtrn.broadcastIP[0] =	rtrn.ip[2];
	rtrn.broadcastIP[0] = rtrn.mask[3]-1;
	
	return rtrn;
}
void displayInfo(addressInfo e){
	int i;
	UART_write(newLine, strlen(newLine));
	char ip[100];
	char mask[100];
	sprintf(ip, "IP: %d.%d.%d.%d", e.ip[0], e.ip[1], e.ip[2], e.ip[3]);
	UART_write(ip, strlen(ip));
	UART_write(newLine, strlen(newLine));
	sprintf(mask, "Mask: %d.%d.%d.%d", e.mask[0], e.mask[1], e.mask[2], e.mask[3]); 
	UART_write(mask, strlen(mask));
	UART_write(newLine, strlen(newLine));


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
