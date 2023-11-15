/**
  ********************************************************************************************************************************************
  * @file     STM32_00_HelloWorld_01-blinkLED.c
  * @author   SPSE Havirov
  * @version  1.0
  * @date     03-March-2022 [v1.0]
  * @brief    Blikani vestavene(ych) LED v nekonecne smycce, pokud neni stisknuto uzivatelske tlacitko.
  *           Pri stisku uzivatelskeho tlacitka LED sviti.
  *
  ********************************************************************************************************************************************
  * @attention
  *
  * Otestovano na: F407, F401, G071
  *
  * Netestovano: F411, L1529
  *
  ********************************************************************************************************************************************
*/

#include "stm32_kit.h"                                     // Pripojeni globalniho konfiguracniho souboru pro praci s pripravkem.
#include "stm32_kit/led.h"

#define LED_BLINK_STEP  50                                        // Krok blikani LED

volatile uint8_t out;                                             // Pro Debug.

int step = 400;

const enum pin ledky[] = {
    LED_IN_0,
    LED_IN_1,
    LED_IN_2,
    LED_IN_3,
		P_INVALID
};
const enum pin ex_ledky[] = {
    LED_EX_3,
    LED_EX_2,
    LED_EX_1,
    LED_EX_0,
		P_INVALID
};

BOARD_SETUP void setup(void) {
  LED_setup();                                                    // Pocatecni inicializace pripravku.
  SystemCoreClockUpdate();                                        // Do SystemCoreClock se nahraje frekvence jadra.
  SysTick_Config(SystemCoreClock / 10000);                        // Konfigurace SysTick timeru.
}

void turnOffAll(){
	for(int i = 0; i < 4; i++){
		io_set(ledky[i], 0);
		io_set(ex_ledky[i], 1);
	}
}

void led_handle(uint8_t i, int stav){
	io_set(ledky[i], stav);
	delay_ms(step);
	io_set(ledky[i], stav-1);
}
void led_ex_handle(uint8_t i, int stav){
	io_set(ex_ledky[i], stav-1);
	delay_ms(step);
	io_set(ex_ledky[i], stav);
}

void enableButton(){
	delay_ms(10);
}

void EXTI0_IRQHandler(void) {
  if (EXTI->PR & (1UL << 0)) {
		// EXTI0 interrupt pending?                        
		EXTI->PR |= (1UL << 0);       // Clear pending interrupt
			step = step - 50;
			if(step <= 0){
				step = 400;
			}
		}
  }
}


int main(void) {
  uint8_t i;
	uint8_t x;
	int cat = 0;
	int _switch = 0;
  i = 0;
	x = -1;
	
	RCC->APB2ENR |= (1UL << 14);          // Enable SYSCNFG
  SYSCFG->EXTICR[0] &= ~(0x0F << 0);    // Bits[3:2:1:0] = (0:0:0:0)  -> configure EXTI0 line for PA0
  EXTI->IMR |= (1UL << 0);              // Bit[0] = 1  --> Disable the Mask on EXTI 0
  EXTI->RTSR |= (1UL << 0);             // Enable Rising Edge Trigger for PA0
  EXTI->FTSR &= ~(1UL << 0);            // Disable Falling Edge Trigger for PA0
  NVIC_SetPriority (EXTI0_IRQn, 1);     // Set Priority
  NVIC_EnableIRQ (EXTI0_IRQn);          // Enable Interrupt
  
  while(1){
		
		if(cat == 0){
			for(int i = 0; ledky[i] != P_INVALID; i++){
				led_handle(i, 1);
			}
		}else{
			for(int i = 0; ex_ledky[i] != P_INVALID; i++){
				led_ex_handle(i, 1);
			}
		}
		cat++;
		if(cat == 2){
			cat = 0;
		}
	}	

  return 0;
}
