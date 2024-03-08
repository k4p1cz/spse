/**
 * @file   app.c
 * @author Teodor Kapitanov
 * 
 */

#include "stm32_kit.h"
#include "stm32_kit/led.h"
#include "stm32_kit/button.h"

const enum pin ledky[] = {
    LED_IN_0,
    LED_IN_1,
    LED_IN_2,
    LED_IN_3,
    P_INVALID
};

void start();

BOARD_SETUP void setup(void) {
	LED_setup();
	BTN_setup();
	SystemCoreClockUpdate();                  // Do SystemCoreClock se nahraje frekvence jadra.
  SysTick_Config(SystemCoreClock / 10000);  // Konfigurace SysTick timeru.
};

int main(void) {
	int i;
	int on = 0;
	while (1) {
		if (io_read(USER_BUTTON)) {
			if(on == 0){
				for (i = 0; ledky[i] != P_INVALID; i++) {
					io_set(ledky[i], 1);
					delay_ms(200);
				};
				on = 1;
			}else{
				for (i = 0; ledky[i] != P_INVALID; i++) {
					io_set(ledky[i], 0);
					delay_ms(200);
				};
				on = 0;
			}
		}
	}
}

void start(){
	int i;
	for (i = 0; ledky[i] != P_INVALID; i++) {
		io_set(ledky[i], 1);
		delay_ms(200);
  };
	delay_ms(500);
	for (i = 0; ledky[i] != P_INVALID; i++) {
		io_set(ledky[i], 0);
		delay_ms(200);
  };
	delay_ms(500);
}
