/**
 * @file   app.c
 * @author Teodor Kapitanov
 * 
 */

#include <stdio.h>
#include <string.h>

#include "stm32_kit.h"
#include "stm32_kit/lcd.h"
#include "stm32_kit/uart.h"


OS_SEM lock;


OS_TID pid_tsk_lcd_line1;
OS_TID pid_tsk_lcd_line2;
OS_TID pid_tsk_time_counter;
OS_TID pid_tsk_uart;

int time = 0;

char clear[100] = "\033[2J\033[1;1H";
char url[100] = "root@stm32:/dev/adc/ ";
char line[100] = "\r\n";

char buff[999];
int buff_len = 0;

__task void tsk_lcd_line1() {
	LCD_set(LCD_CUR_OFF);
	for (;;) {
		char rtrn[9];
		snprintf(rtrn, 9, "%d                 ", time);
		os_sem_wait(&lock, 0xffff);
		{
			LCD_set(LCD_LINE1);
			LCD_print(rtrn);
		}
		os_sem_send(&lock);
	}
}
__task void tsk_lcd_line2() {
	char line[9];
	for (;;) {
		snprintf(line, 9, "%d            ", time);
		os_sem_wait(&lock, 0xffff);
		{
			LCD_set(LCD_LINE2);
			LCD_print(line);
		}
		os_sem_send(&lock);
	}
}
__task void tsk_time_counter() {
//	char line[9];
	for (;;) {
		delay_ms(1000);
		time++;
		
	}
}
__task void tsk_uart(){
	UART_write(clear, strlen(clear));
	UART_write(url, strlen(url));
	uint8_t e;
	int numOfArgs;
	//char print[999];
	char cmd[100];
	//int param;
	for(;;){
		e = UART_getc();
		switch(e){
			case '\b':
				buff_len--;
				buff[buff_len] = 0x00;
				continue;
			break;
			case 0x0D:
				UART_write(line, strlen(line));
				numOfArgs = sscanf(buff, "%s", cmd);
			
				if(0 == strcmp("clear", cmd)){
					UART_write(clear, strlen(clear));
					UART_write(url, strlen(url)); // nejspis neustale clearuje
				}else{
					UART_write(line, strlen(line));
					UART_write(url, strlen(url));
				}
				
			
				/*for(int i = 0; i < buff_len; i++){
					UART_putc(buff[i]);
				}*/
				
				memset(buff, 0x00, 999);
				

				continue;
			break;
		}
		
		buff[buff_len] = e;
		buff_len++;
	}
}


__task void setup() {
	LCD_setup();
	UART_setup();
	
	os_sem_init(&lock, 0);
	os_sem_send(&lock);
	
	pid_tsk_uart = os_tsk_create(tsk_uart, 0);
	pid_tsk_lcd_line1 = os_tsk_create(tsk_lcd_line1, 0);
	pid_tsk_lcd_line2 = os_tsk_create(tsk_lcd_line2, 0);
	pid_tsk_time_counter = os_tsk_create(tsk_time_counter, 0);
	
	os_tsk_delete_self();
}

int main () {
	os_sys_init(setup);
}

