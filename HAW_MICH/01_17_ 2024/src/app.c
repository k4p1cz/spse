#include "stm32_kit.h"
#include "stm32_kit/led.h"
#include "stm32_kit/button.h"
#include "stm32_kit/lcd.h"
#include <stdio.h>

const enum pin ledky_in[] = {
    LED_IN_0,
    LED_IN_1,
    LED_IN_2,
    LED_IN_3,
    P_INVALID
};
const enum pin ledky_ex[] = {
    LED_EX_0,
    LED_EX_1,
    LED_EX_2,
    LED_EX_3,
    P_INVALID
};

#define LED_BLINK_STEP  50              
volatile uint16_t step = LED_BLINK_STEP; 

BOARD_SETUP void setup(void) {
  SystemCoreClockUpdate();    
  SysTick_Config(SystemCoreClock / 10000); 
  
  LED_setup();
  BTN_setup();
	LCD_setup();
  
  //=== Nastaveni prerusovaciho systemu - prozatim pouze pro F407 - ZACATEK
  RCC->APB2ENR |= (1UL << 14);          // Enable SYSCNFG
  SYSCFG->EXTICR[0] &= ~(0x0F << 0);    // Bits[3:2:1:0] = (0:0:0:0)  -> configure EXTI0 line for PA0
  EXTI->IMR |= (1UL << 0);              // Bit[0] = 1  --> Disable the Mask on EXTI 0
  EXTI->RTSR |= (1UL << 0);             // Enable Rising Edge Trigger for PA0
  EXTI->FTSR &= ~(1UL << 0);            // Disable Falling Edge Trigger for PA0
  NVIC_SetPriority (EXTI0_IRQn, 1);     // Set Priority
  NVIC_EnableIRQ (EXTI0_IRQn);          // Enable Interrupt
  //=== Nastaveni prerusovaciho systemu - prozatim pouze pro F407 - KONEC
}

/*void LED_toggle(const pin_t leds[], int state, int delay) {
  for (int i = 0; leds[i] != P_INVALID; i++) {
    io_set(leds[i], state);
    delay_ms(delay);
  }
}*/

int sec = 0;
int ledsOn = 0;
int operation = 0; // 0 - +, 1 - -

void ledToggle(){
	for(int i = 0; i < 4; i++){
		io_set(ledky_in[i], 0);
		io_set(ledky_ex[i], 1);
	}
	for(int i = 0; i < ledsOn; i++){
		if(i < 4){
			io_set(ledky_in[i], 1);
		}
		if(ledsOn > 3){
			io_set(ledky_ex[i - 4], 0);
		}
	}
	if(ledsOn > 7 && operation == 0){
		operation = 1;
	}else if(ledsOn == 0 && operation == 1){
		operation = 0;
	}
	
	
	if(operation == 0){
		ledsOn++;
	}else{
		ledsOn--;
	}
}

int main(void) {
	LCD_set(LCD_LINE1);
	LCD_set(LCD_CUR_OFF);
  char print[9];
	while (1) {
		LCD_set(LCD_LINE1);
		snprintf(print, 9, "  %d     ", sec);
		LCD_print(print);
    sec++;
		delay_ms(1000);
  }

  // return 0;
}

// Handler pro preruseni - prozatim pouze pro F407
void EXTI0_IRQHandler(void) {
  if (EXTI->PR & (1UL << 0)) {
    // EXTI0 interrupt pending?                        
    EXTI->PR |= (1UL << 0); // Clear pending interrupt
		
    step /= 2;
    if (step < 26) {
			ledToggle();
      step = LED_BLINK_STEP;
    }
  }
}
