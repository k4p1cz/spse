#include "stm32_kit.h"                                    
#include "stm32_kit/led.h"

#define LED_BLINK_STEP  300                           

int mode = 0;

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
const enum pin ledky_r[] = {
    LED_IN_3,
    LED_IN_2,
    LED_IN_1,
    LED_IN_0,
		P_INVALID
};
const enum pin ex_ledky_r[] = {
    LED_EX_0,
    LED_EX_1,
    LED_EX_2,
    LED_EX_3,
		P_INVALID
};


BOARD_SETUP void setup(void) {
  LED_setup();                                                    // Pocatecni inicializace pripravku.
  SystemCoreClockUpdate();                                        // Do SystemCoreClock se nahraje frekvence jadra.
  SysTick_Config(SystemCoreClock / 10000);                        // Konfigurace SysTick timeru.
}

void EXTI0_IRQHandler(void) {
  if (EXTI->PR & (1UL << 0)) {
		// EXTI0 interrupt pending?                        
		EXTI->PR |= (1UL << 0);       // Clear pending interrupt
		if(mode == 0){
			mode = 1;
		}else{
			mode = 0;
		}
	}
}

void turnOffAll(){
	for(int i = 0; i < 4; i++){
		io_set(ledky[i], 0);
		io_set(ex_ledky[i], 1);
	}
}

int main(void) {
  uint8_t i;
	
	RCC->APB2ENR |= (1UL << 14);          // Enable SYSCNFG
  SYSCFG->EXTICR[0] &= ~(0x0F << 0);    // Bits[3:2:1:0] = (0:0:0:0)  -> configure EXTI0 line for PA0
  EXTI->IMR |= (1UL << 0);              // Bit[0] = 1  --> Disable the Mask on EXTI 0
  EXTI->RTSR |= (1UL << 0);             // Enable Rising Edge Trigger for PA0
  EXTI->FTSR &= ~(1UL << 0);            // Disable Falling Edge Trigger for PA0
  NVIC_SetPriority (EXTI0_IRQn, 1);     // Set Priority
  NVIC_EnableIRQ (EXTI0_IRQn);          // Enable Interrupt
  
	
	while(1){
		if(mode == 0){
			// 1. rezim - HAD
			turnOffAll();
			for(i = 0; ledky[i] != P_INVALID; i++){
				if(i != 0){
					io_set(ledky[i - 1], 0);
				}else{
					io_set(ledky[3], 0);
				}
				io_set(ledky[i], 1);
				delay_ms(LED_BLINK_STEP);
				turnOffAll();
			}
			for(i = 0; ex_ledky[i] != P_INVALID; i++){
				if(i != 0){
					io_set(ex_ledky[i - 1], 1);
				}else{
					io_set(ex_ledky[3], 1);
				}
				io_set(ex_ledky[i], 0);
				delay_ms(LED_BLINK_STEP);
			}
			for(i = 0; ex_ledky_r[i] != P_INVALID; i++){
				if(i != 0){
					io_set(ex_ledky_r[i - 1], 1);
				}else{
					io_set(ex_ledky_r[3], 1);
				}
				io_set(ex_ledky_r[i], 0);
				delay_ms(LED_BLINK_STEP);
				turnOffAll();
			}
			for(i = 0; ledky_r[i] != P_INVALID; i++){
				if(i != 0){
					io_set(ledky_r[i - 1], 0);
				}else{
					io_set(ledky_r[3], 0);
				}
				io_set(ledky_r[i], 1);
				delay_ms(LED_BLINK_STEP);
			}
		}else if(mode == 1){ 
			// 2. rezim
			turnOffAll();
			for(i = 0; ledky[i] != P_INVALID; i++){
				if(i != 0){
					io_set(ledky[i - 1], 0);
					io_set(ex_ledky_r[i - 1], 1);
				}else{
					io_set(ledky[3], 0);
					io_set(ex_ledky_r[3], 1);
				}
				io_set(ledky[i], 1);
				io_set(ex_ledky_r[i], 0);
				delay_ms(LED_BLINK_STEP);
				turnOffAll();
			}
			
		
		
		}
		
	
	
	}
	
	
	
	
	// return 0;
}
