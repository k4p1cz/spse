#include "stm32_kit.h"
#include "stm32_kit/lcd.h"
#include "stm32_kit/led.h"
#include "stm32_kit/adc.h"
#include "stm32_kit/uart.h"
#include "stdio.h"
#include <string.h>
#include <math.h>

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

int err = 1;
char clear[100] = "\033[2J\033[1;1H";
char url[100] = "root@stm32:/dev/adc/ ";
char no_cmd[100] = "\r\nCommand not found!";
char inv_arg[100] = "\r\nInvalid argument!";
char line[100] = "\r\n";
int voltsSwitch = 0;


void toggleVolts(){
	if(voltsSwitch == 0){
		voltsSwitch = 1;
	}else{
		voltsSwitch = 0;
	}

	if(voltsSwitch == 1){
		char voltsCmd[100] = "\r\nVolts have been turned ON!\r\n";
		UART_write(voltsCmd, sizeof(voltsCmd));
	}else{
		char voltsCmd[100] = "\r\nVolts have been turned OFF!\r\n";
		UART_write(voltsCmd, sizeof(voltsCmd));
	}
}

void lcdPrint(char print[8]){
	LCD_set(LCD_LINE1);
	LCD_print(print);
	LCD_set(LCD_LINE2);
	LCD_print("                   ");
}

void sample(int n, int avg){
	int avgLength = 0;
	float avgArr[100];
	int len;
	for(int i = 0; i < n; i++){
		uint16_t read;
		float volts;
		do{
			read = ADC_read();
		}while(!read);
		char lcd_print[8];
		if(voltsSwitch == 1){
			volts = ((read / 4095.0) * 3.3) * 1000;
			if(avg == 1){
				avgArr[i] = volts;
				avgLength++;
			}
			char txt[32];
			char lcdTxt[8];
			snprintf(lcdTxt, 8, "%.0f mV ", volts);
			lcdPrint(lcdTxt);
			snprintf(txt, 32, "%.2f mV\r\n", volts);
			len = strlen(txt);
			UART_write(txt, len);
		}else{
			char txt[32];
			snprintf(txt, 32, "%d samples\r\n", read);
			char lcdTxt[8];
			snprintf(lcdTxt, 8, "%d sam", read);
			lcdPrint(lcdTxt);
			len = strlen(txt);
			if(avg == 1){
				avgArr[i] = read;
				avgLength++;
			}
			UART_write(txt, len);
		}

		
		delay_ms(1);
		turnOnLeds(read);
	}
	if(avg == 1){
			float avgResult = 0;
			char txt[32];
			if(voltsSwitch == 1){
				for(int i = 0; i < avgLength; i++){
					avgResult = avgResult + avgArr[i];
				}
				avgResult = (avgResult / avgLength);
				snprintf(txt, 32, "\r\nAverage %.1f mV\r\n", avgResult);
				UART_write(txt, strlen(txt));
			}else{
				for(int i = 0; i < avgLength; i++){
					avgResult = avgResult + avgArr[i];
				}
				avgResult = (avgResult / avgLength);
				snprintf(txt, 32, "\r\nAverage %.1f samples\r\n", avgResult);
				UART_write(txt, strlen(txt));
			}
		}
}

int main(void){
	LCD_set(LCD_CUR_OFF);
	LCD_set(LCD_LINE1);
	LCD_print("  UART  ");
	LCD_set(LCD_LINE2);
	LCD_print("WELCOME ");
	UART_write(clear, strlen(clear));
	char res[100];
	char cmd[10];
	int param_num;
	char param_str[100];
	int numOfArgs;
	while(1){
		err = 1;
		UART_write(url, strlen(url));
		memset(res, 0, sizeof(res));
		memset(cmd, 0, sizeof(cmd));
		memset(param_str, 0, sizeof(param_str));
		UART_read(res, 100);
		param_num = 0;
		numOfArgs = 0;
		numOfArgs = sscanf(res, "%s %s %d ", cmd, param_str, &param_num);
		
		if(0 == strcmp("clear", cmd)){
			UART_write(clear, strlen(clear));
			err = 0;
		}
		if(0 == strcmp("volts", cmd)){
			toggleVolts();
			err = 0;
		}

		if(0 == strcmp("sample",cmd)){
			if(numOfArgs < 2){
				UART_write(line, strlen(line));
				sample(1, 0);
				UART_write(line, strlen(line));
			}else{
				if(0 == strcmp("avg", param_str)){
					if(param_num == 0){
						UART_write(inv_arg, strlen(inv_arg));
						UART_write(line, strlen(line));
					}else{
						UART_write(line, strlen(line));
						sample(param_num, 1);
						UART_write(line, strlen(line));
					}
				}else{
					int numOfSubArgs = sscanf(param_str, "%d", &param_num);
					if(numOfSubArgs < 1){
						UART_write(inv_arg, strlen(inv_arg));
						UART_write(line, strlen(line));
					}else{
							UART_write(line, strlen(line));
							sample(param_num, 0);
							UART_write(line, strlen(line));
					}					
				}
			}
			err = 0;
		}
		
		if(err == 1){
				UART_write(no_cmd, strlen(no_cmd));
				UART_write(line, strlen(line));
		}
	}
}