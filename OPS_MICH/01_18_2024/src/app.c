/**
 * @file   app.c
 * @author Teodor Kapitanov
 * 
 */
 

#include "stm32_kit.h"
#include "stm32_kit/lcd.h"
#include "stm32_kit/keypad.h"
#include "stm32_kit/uart.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LCD_8x2 (((LCD_COLS) == 8) && ((LCD_ROWS) == 2))
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
	
typedef struct{
	int enablePass;
	int intrfLoopbackIp[4];
	int intrfLoopbackMask[4];
	int volts;
}CONFIG;
typedef struct{
	int leds[4];
	int periods[4];
	int turnedOnLeds;
}LED_CONFIG;
typedef struct{
	int routeIp[4];
	int routeMask[4];
}IP_ROUTE_CONFIG;

OS_TID tsk_initialCodeEntry;
OS_TID tsk_terminalProcess;


CONFIG globalConfig;
LED_CONFIG ledConfig;
IP_ROUTE_CONFIG ipRouteConfig;


void showConfiguration(int e);

	
char clear[100] = "\033[2J\033[1;1H";
char url[100] = "root@stm32:/dev/adc/ ";
char enUrl[100] = "root@stm32:/dev/adc/en/ ";
char line[100] = "\n\r";
char wrongPass[100] = "Wrong password!";
char invalidCommand[100] = "ESC[30mInvalid command! \r\n";
int ledsBlinking = 0;
	
__task void terminalProcess(){
	char buff[999];
	int buff_len = 0;
	uint8_t e;
	int showMode = 0;
	int enMode = 0;
	int enPassMode = 0;
	int numOfArgs = 0;
	char cmd[100];
	char param1[100];
	char param2[100];
	for(;;){
		e = UART_getc();
		switch(e){
			case '\b':
				buff_len--;
				buff[buff_len] = 0x00;
			break;
			case 0x0D:
				//UART_write(line, strlen(line));
				if(showMode == 1){
					numOfArgs = sscanf(buff, "%s %s", cmd, param1);
					if(0 == strcmp("config", cmd)){
						showConfiguration(0);
						UART_write(line, strlen(line));
					}else if(0 == strcmp("led", cmd)){
						showConfiguration(1);
						UART_write(line, strlen(line));
					}else if(0 == strcmp("ip", param1) && 0 == strcmp("route", param1)){
						showConfiguration(2);
						UART_write(line, strlen(line));
					}else{
						UART_write(line, strlen(line));
						UART_write(url, strlen(url));
						showMode = 0;
					}
					buff_len = 0;
				}else if(enMode == 1){
					int enNumOfArgs = sscanf(buff, "%s %s %s", cmd, param1, param2);
					//numOfArgs = sscanf(buff, "%s %s %s", cmd, param1, param2);
					if(strcmp("blink", cmd)){
						if(enNumOfArgs < 3){
							UART_write(invalidCommand, strlen(invalidCommand));
						}else if(atoi(param1) > 4){
							// invalid command
						}else if(atoi(param2) == 0){
							ledConfig.turnedOnLeds--;
							ledConfig.leds[atoi(param1)] = 0;
							ledConfig.periods[atoi(param1)] = 0;
							if(ledConfig.turnedOnLeds == 0){
								// vypnout global task 
						}else{ ///// VYRESIT problem 1 tasku - moznost rozdelit do 4 tasku a upravit tento kod
							if(ledConfig.turnedOnLeds == 0){
								// zapnout global task
							}
							ledConfig.turnedOnLeds++;
							ledConfig.leds[atoi(param1)] = 1;
							ledConfig.periods[atoi(param1)] = atoi(param2);
						}
					}
				}
					
					
					UART_write(line, strlen(line));
					UART_write(enUrl, strlen(enUrl));
					buff_len = 0;
					}else if(enPassMode == 1){
					numOfArgs = sscanf(buff, "%s", cmd);
					char setPass[5];
					memset(setPass, 0x00, 5);
					snprintf(setPass, 5, "%d", globalConfig.enablePass);
					if(0 == strcmp(cmd, setPass)){
						enPassMode = 0;
						enMode = 1;
						UART_write(line, strlen(line));
						UART_write(enUrl, strlen(enUrl));
						buff_len = 0;
					}else{
						//UART_write(line, strlen(line));
						UART_write(wrongPass, strlen(wrongPass));
						UART_write(line, strlen(line));
						UART_write(line, strlen(line));
						UART_write("Enter password: ", 16);
						buff_len = 0;
					} 
				}else{
					numOfArgs = sscanf(buff, "%s %s", cmd, param1);
					if(0 == strcmp("clear", cmd)){
						UART_write(clear, strlen(clear));
						UART_write(url, strlen(url));
						buff_len = 0;
					}else if(0 == strcmp("sh", cmd) || 0 == strcmp("show", cmd)){
						showMode = 1;
						UART_write(line, strlen(line));
						UART_write("[show] ", 6);
						buff_len = 0;
					}else if(0 == strcmp("en", cmd) || 0 == strcmp("enable", cmd)){
						enPassMode = 1;
						UART_write(line, strlen(line));
						UART_write("Enter password: ", 16);
						buff_len = 0;
					}else{
						UART_write(line, strlen(line));
						UART_write(url, strlen(url));
						buff_len = 0;
					}
				}
			
				memset(buff, 0x00, 999);
				memset(cmd, 0x00, 100);
				memset(param1, 0x00, 100);
				memset(param2, 0x00, 100);
			break;
		}
		UART_putc(e);
		buff[buff_len] = e;
		buff_len++;
	}
}


__task void initialCodeEntry(){
	LCD_set(LCD_LINE1);
	LCD_print("PIN:");
	int numOfChars = 0;
	uint8_t z;
	uint8_t zPin[4];
	for (;;) {
		do{
			z = KBD_read();
		}while(!z);
		zPin[numOfChars] = z;
		LCD_symbol(z);
		numOfChars++;
		if(numOfChars >= 4){
			if(strcmp((const char *)zPin, "1337") == 0){
				LCD_set(LCD_LINE1);
				LCD_print("UNLOCKED");
				tsk_terminalProcess = os_tsk_create(terminalProcess, 0);
				os_tsk_delete_self();
			}
			LCD_set(LCD_LINE1);
			LCD_print("        ");
			LCD_set(LCD_LINE1);
			LCD_print("PIN:");
			numOfChars = 0;
		}
	}	
}

__task void setup() {
	KBD_setup();
	LCD_setup();
	UART_setup();

	globalConfig.enablePass = 1234;
	memset(globalConfig.intrfLoopbackIp, 0x00, 4);
	memset(globalConfig.intrfLoopbackMask, 0x00, 4);
	globalConfig.volts = 0;
	
	ledConfig.turnedOnLeds = 0;
	memset(ledConfig.leds, 0x00, 4);
	memset(ledConfig.periods, 0x00, 4);
	
	memset(ipRouteConfig.routeIp, 0x00, 4);
	memset(ipRouteConfig.routeMask, 0x00, 4);
	
	tsk_initialCodeEntry = os_tsk_create(initialCodeEntry, 0);
	os_tsk_delete_self();
}

int main () {
	os_sys_init(setup);
}

void showConfiguration(int e){
	UART_write(line, strlen(line));
	switch(e){
		case 0:
			UART_write("Enable password = ", 18);
			char str[4];
			snprintf(str, 4, "%d", globalConfig.enablePass);
			UART_write(str, strlen(str));
				
			UART_write(line, strlen(line));
			UART_write("Interface loopback IPv4 = ", 26);
			for(int i = 0; i < 4; i++){
				char str[3];
				snprintf(str, 3, "%d", globalConfig.intrfLoopbackIp[i]);
				UART_write(str, strlen(str));
				if(i < 3){
					UART_write(".", 1);
				}
			}
			UART_write(line, strlen(line));
			UART_write("Interface loopback mask = ", 26);
			for(int i = 0; i < 4; i++){
				char str[3];
				snprintf(str, 3, "%d", globalConfig.intrfLoopbackMask[i]);
				UART_write(str, strlen(str));
				if(i < 3){
					UART_write(".", 1);
				}
			}
			UART_write(line, strlen(line));
			UART_write("Volts = ", 8);
			UART_write(globalConfig.volts?"ON" : "OFF", 3);
			
		break;
	}
}