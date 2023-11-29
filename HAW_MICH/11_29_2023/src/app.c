/**
 * @file   app.c
 * @author Teodor Kapitanov
 * 
 */

#include "stm32_kit.h"
#include "stm32_kit/lcd.h"
#include "stm32_kit/led.h"
#include "stm32_kit/adc.h"
#include "stdio.h"


#define MAX_VAL 4095


BOARD_SETUP void setup(void) {
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 10000);
	LCD_setup();
	LED_setup();
	ADC_setup();
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

int main(void) {
	while (1) {
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
		
	}
}

