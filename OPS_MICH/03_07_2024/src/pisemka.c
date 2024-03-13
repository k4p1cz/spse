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

addressInfo calculateInfo(char ip[100], char mask[100]);
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
								int i;
								char *token = strtok(ip, ".");
								for(i=0; i<4; i++){
									info.ip[i] = atoi(token);
									token = strtok(NULL, ".");
								}
								char *token2 = strtok(mask_, ".");
								for(i=0; i<4; i++){
									info.mask[i] = atoi(token2);
									token2 = strtok(NULL, ".");
								}
								
								info.blockSize = 256-info.mask[3];
								info.numOfAddress = info.blockSize;
								info.numOfHosts	= info.blockSize-2;
								info.networkIP[0] = info.ip[0];
								info.networkIP[1] = info.ip[1];
								info.networkIP[2] = info.ip[2];
								info.networkIP[3] = 0;
								switch(info.mask[3]){
									case 0:
										info.CIDR = 24;
										break;
									case 128:
										info.CIDR = 25;
										break;
									case 192:
										info.CIDR = 26;
										break;
									case 224:
										info.CIDR = 27;
										break;
									case 240:
										info.CIDR = 28;
										break;
									case 248:
										info.CIDR = 39;
										break;
									case 252:
										info.CIDR = 30;
										break;
									case 254:
										info.CIDR = 31;
										break;
									case 255:
										info.CIDR = 32;
										break;
								}
								
								info.hosts[0] = info.networkIP[3]+1;
								info.hosts[1] = info.blockSize-2;
								info.broadcastIP[0] =	info.ip[0];
								info.broadcastIP[1] =	info.ip[1];
								info.broadcastIP[2] =	info.ip[2];
								info.broadcastIP[3] = info.blockSize-1;
							enteredDetails = 1;

						}
					} // pokud jiz mame vsechny detaily
					if(0 == strcmp(buff, "show")){
						displayInfo(info);
					}
				// vycistim si pole buffer a pole command
				memset(buff, 0x00, 999);
				buff_len = 0;
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
void displayInfo(addressInfo e){
	int i;
	UART_write(newLine, strlen(newLine));
	char print[100];
	sprintf(print, "IP: %d.%d.%d.%d", e.ip[0], e.ip[1], e.ip[2], e.ip[3]);
	UART_write(print, strlen(print));
	UART_write(newLine, strlen(newLine));
	
	sprintf(print, "Mask: %d.%d.%d.%d", e.mask[0], e.mask[1], e.mask[2], e.mask[3]); 
	UART_write(print, strlen(print));
	UART_write(newLine, strlen(newLine));
	
	sprintf(print, "Block: %d", e.blockSize);
	UART_write(print, strlen(print));
	UART_write(newLine, strlen(newLine));
	
	sprintf(print, "Num of address: %d", e.numOfAddress);
	UART_write(print, strlen(print));
	UART_write(newLine, strlen(newLine));
	
	sprintf(print, "Num of hosts: %d", e.numOfHosts);
	UART_write(print, strlen(print));
	UART_write(newLine, strlen(newLine));
	
	sprintf(print, "Hosts: .%d - .%d", e.hosts[0], e.hosts[1]);
	UART_write(print, strlen(print));
	UART_write(newLine, strlen(newLine));
	
	sprintf(print, "Network address: %d.%d.%d.%d", e.networkIP[0], e.networkIP[1], e.networkIP[2],e.networkIP[3]);
	UART_write(print, strlen(print));
	UART_write(newLine, strlen(newLine));
	
	sprintf(print, "Broadcast address: %d.%d.%d.%d", e.broadcastIP[0], e.broadcastIP[1], e.broadcastIP[2], e.broadcastIP[3]);
	UART_write(print, strlen(print));
	UART_write(newLine, strlen(newLine));
	
	sprintf(print, "CIDR: /%d", e.CIDR);
	UART_write(print, strlen(print));
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