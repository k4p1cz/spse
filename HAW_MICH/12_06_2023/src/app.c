/**
 * @file   app.c
 * @author Teodor Kapitanov
 * 
 */

#include "stm32_kit.h"
#include "stm32_kit/lcd.h"
#include "stm32_kit/led.h"
#include "stm32_kit/adc.h"
#include "stm32_kit/uart.h"
#include "stdio.h"
#include <string.h>


#define MAX_VAL 4095


BOARD_SETUP void setup(void) {
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 10000);
	LCD_setup();
	LED_setup();
	ADC_setup();
	UART_setup();
};

const enum pin ex_ledky[] = {
    LED_EX_3,
    LED_EX_2,
    LED_EX_1,
    LED_EX_0,
    P_INVALID
};
const enum pin ledky[] = {
    LED_IN_0,
    LED_IN_1,
    LED_IN_2,
    LED_IN_3,
    P_INVALID
};
void turnOnLeds(int read){
	read = (int)read;
	int i;
	 for (i = 0; ex_ledky[i] != P_INVALID; i++) {
        io_set(ex_ledky[i], 1);
				io_set(ledky[i], 0);
  }
	int index = MAX_VAL / 5;
	int x = read / index;
	if(x > 4){
		x = 4;
	}
	for(i = 0; i < x; i++){
		io_set(ex_ledky[i], 0);
	}
	for(i = 0; i < x; i++){
		io_set(ledky[i], 1);
	}
}

void KAP_read(int r){	
	for(int i = 0; i < r; i ++){
LCD_set(LCD_CUR_OFF);
		LCD_set(LCD_LINE1);
		uint16_t read;
		float volts;
		do{
			read = ADC_read();
		}while(!read);
		char lcd_print[8];
		volts = (read / 4095.0) * 3.3;
		sprintf(lcd_print,"%.3f V", volts);
		LCD_print(lcd_print);
		LCD_set(LCD_LINE2);
		sprintf(lcd_print,"%d      ", read);
		LCD_print(lcd_print);	
		delay_ms(1);
		turnOnLeds(read);
		char txt[32];
		snprintf(txt, 32, "%d, %.3f V\r\n", read, volts);
		int len = strlen(txt);
		UART_write(txt, len); 
	
	}
}



char eg_1[100] = "\r\n   _____________\r\n";
char eg_2[100] = " _/_|[][][][][] | - -\r\n";
char eg_3[100] = "(      183      | - -\r\n";
char eg_4[100] = "=--OO-------OO--=\r\n";
	

int page = 0;

int err = 1;
char clear[100] = "\033[2J\033[1;1H";
char url[100] = "root@stm32:/dev/adc/ ";
char no_cmd[100] = "\r\nCommand not found!";
char inv_arg[100] = "\r\nInvalid argument!";
char line[100] = "\r\n";

int main(void) {
	UART_write(clear, strlen(clear));
	
	while (1) {
		if(page == 0){
			err = 1;
			//UART_write(clear, strlen(clear));
			UART_write(url, strlen(url));
			char res[100];
			UART_read(res, 100);
			//UART_write(line, strlen(line));
			char cmd[10];
			int param;
			int numOfArgs = 0;
			numOfArgs = sscanf(res, "%s %d", cmd, &param);
			
			if(0 == strcmp("clear", cmd)){
				UART_write(clear, strlen(clear));
				err = 0;
			}
			if(0 == strcmp("read", cmd)){
				if(numOfArgs == 1){
					UART_write(line, strlen(line));
					KAP_read(1);
					UART_write(line, strlen(line));
					err = 0;
				}else{
					if(param != 0){
						UART_write(line, strlen(line));
						KAP_read(param);
						UART_write(line, strlen(line));
					}else{
						UART_write(inv_arg, strlen(inv_arg));
						UART_write(line, strlen(line));
					}
					err = 0;
				}
			}
			if(0 == strcmp("183", cmd)){
				if(param < 1){
					UART_write(line, strlen(line));
					UART_write(eg_1, strlen(eg_1));
					UART_write(eg_2, strlen(eg_2));
					UART_write(eg_3, strlen(eg_3));
					UART_write(eg_4, strlen(eg_4));
					UART_write(line, strlen(line));
				}else if(param  > 0){
					for(int i = 1; i < param; i++){
						UART_write(line, strlen(line));
						UART_write(line, strlen(line));
						UART_write(eg_1, strlen(eg_1));
						UART_write(eg_2, strlen(eg_2));
						UART_write(eg_3, strlen(eg_3));
						UART_write(eg_4, strlen(eg_4));
						UART_write(line, strlen(line));
						UART_write(line, strlen(line));
					}
				}
				err = 0;
			}
			
			
			
			
			
			
			if(err == 1){
				UART_write(no_cmd, strlen(no_cmd));
				UART_write(line, strlen(line));
			}
		}else{
			
		}
	}
}
