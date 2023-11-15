#define LCD_COLS      8                                          // Pocet sloupcu pouziteho displeje
#define LCD_ROWS      2                                           // Pocet radku pouziteho displeje
#define KEYPAD_COLS   4                                           // Pocet sloupcu pouziteho KeyPad
#define KEYPAD_ROWS   4                                           // Pocet radku pouziteho KeyPad

#define LCD_8x2 (((LCD_COLS) == 8) && ((LCD_ROWS) == 2))
#define LCD_16x2 (((LCD_COLS) == 16) && ((LCD_ROWS) == 2))

#include "stm32_kit.h"                                    
#include "stm32_kit/led.h"
#include "stm32_kit/lcd.h"
#include "stm32_kit/keypad.h" 

#ifndef KEYPAD_STYLE
  static uint8_t KeyPad_KeyMap[KEYPAD_ROWS][KEYPAD_COLS] = {      // Defaultni rozlozeni pro 4x4 KeyPad
                            '1', '2', '3', 'A',
                            '4', '5', '6', 'B',
                            '7', '8', '9', 'C',
                            '*', '0', '#', 'D'
  };
#elif (KEYPAD_STYLE == 1)
  static uint8_t KeyPad_KeyMap[KEYPAD_ROWS][KEYPAD_COLS] = {      // Alternativni rozlozeni pro 4x4 KeyPad
                            'a', 'b', 'c', 'd',
                            'e', 'f', 'g', 'h',
                            'i', 'j', 'k', 'l',
                            'm', 'n', 'o', 'p'
  };
#elif (KEYPAD_STYLE == 2)
  static uint8_t KeyPad_KeyMap[KEYPAD_ROWS][KEYPAD_COLS] = {      // Alternativni rozlozeni pro 4x4 KeyPad
                            'q', 'r', 's', 't',
                            'u', 'v', 'w', 'x',
                            'y', 'z', '[', ']',
                            '.', ',', '-', '='
  };
#endif

int page = 0;
	
int cola_q = 2;
int chipsy_q = 3;
int pivo_q = 1;
int fanta_q = 0;
	
int canbuy = 0;
int buy_tmp = 0;


BOARD_SETUP void setup(void) {
	
	SystemCoreClockUpdate();                                        // Do SystemCoreClock se nahraje frekvence jadra.
  SysTick_Config(SystemCoreClock / 10000);                        // Konfigurace SysTick timeru.
  LED_setup();                                                    // Pocatecni inicializace pripravku.
	LCD_setup();                                                  // Pocatecni inicializace LCD, nutne pro dalsi praci s LCD.
  KeyPad_setup();                                               // Pocatecni inicializace keypadu, nutne pro dalsi praci s keypad.
  
}

void buy(){
	switch(buy_tmp){
		case 1:
			
		break;
	
	}
}

void EXTI0_IRQHandler(void) {
  if (EXTI->PR & (1UL << 0)) {
		// EXTI0 interrupt pending?                        
		EXTI->PR |= (1UL << 0);       // Clear pending interrupt
		if(canbuy == 1){
			buy();
		}
	}
}

void showMenu(){
	LCD_set(LCD_CUR_OFF);
	LCD_set(LCD_CLR);
	LCD_set(LCD_LINE1);
	switch(page){
		case 0:
			LCD_print("AUTOMAT");
			LCD_set(LCD_LINE2);	
			LCD_print(" * A # ");
		break;
		case 1:
			LCD_print("1.COLA");
			LCD_set(LCD_LINE2);	
			LCD_print("2.CHIPSY");
		break;
		case 2:
			LCD_print("3.PIVO");
			LCD_set(LCD_LINE2);
			LCD_print("4.FANTA");
		break;
	}
}

void showProduct(int e){
	switch(e){
		case 1:
			if(cola_q > 0){
				LCD_set(LCD_CLR);
				LCD_print(" JE");
				LCD_set(LCD_LINE2);
				LCD_print("SKLADEM");
				buy_tmp = 1;
				canbuy = 1;
				cola_q--;
				showMenu();
			}else{
				LCD_set(LCD_CLR);
				LCD_print(" NENI ");
				LCD_set(LCD_LINE2);
				LCD_print("SKLADEM");
				delay_ms(2000);
				page = 0;
				showMenu();
			}
		break;
		case 2:
			if(chipsy_q > 0){
				LCD_set(LCD_CLR);
				LCD_print(" JE");
				LCD_set(LCD_LINE2);
				LCD_print("SKLADEM");
				chipsy_q--;
				showMenu();
			}else{
				LCD_set(LCD_CLR);
				LCD_print(" NENI ");
				LCD_set(LCD_LINE2);
				LCD_print("SKLADEM");
				delay_ms(2000);
				page = 0;
				showMenu();
			}
		break;
		case 3:
			if(pivo_q > 0){
				LCD_set(LCD_CLR);
				LCD_print(" JE");
				LCD_set(LCD_LINE2);
				LCD_print("SKLADEM");
				pivo_q--;
				showMenu();
			}else{
				LCD_set(LCD_CLR);
				LCD_print(" NENI ");
				LCD_set(LCD_LINE2);
				LCD_print("SKLADEM");
				delay_ms(2000);
				page = 0;
				showMenu();
			}
		break;
		case 4:
			if(fanta_q > 0){
				LCD_set(LCD_CLR);
				LCD_print(" JE");
				LCD_set(LCD_LINE2);
				LCD_print("SKLADEM");
				fanta_q--;
				showMenu();
			}else{
				LCD_set(LCD_CLR);
				LCD_print(" NENI ");
				LCD_set(LCD_LINE2);
				LCD_print("SKLADEM");
				delay_ms(2000);
				page = 0;
				showMenu();
			}
		break;
	
	
	
	
	}
}

int main(void) {
	uint8_t z;
	
	RCC->APB2ENR |= (1UL << 14);          // Enable SYSCNFG
  SYSCFG->EXTICR[0] &= ~(0x0F << 0);    // Bits[3:2:1:0] = (0:0:0:0)  -> configure EXTI0 line for PA0
  EXTI->IMR |= (1UL << 0);              // Bit[0] = 1  --> Disable the Mask on EXTI 0
  EXTI->RTSR |= (1UL << 0);             // Enable Rising Edge Trigger for PA0
  EXTI->FTSR &= ~(1UL << 0);            // Disable Falling Edge Trigger for PA0
  NVIC_SetPriority (EXTI0_IRQn, 1);     // Set Priority
  NVIC_EnableIRQ (EXTI0_IRQn);          // Enable Interrupt
	LCD_set(LCD_CUR_OFF);
	showMenu();
	while(1){
		do{
			z = KeyPad_getKey();
		}while(!z);
		
		switch(z){
			case 0x23:
				if(page < 2){
					page++;
					showMenu();
				}
			break;
			case 0x2A:
				if(page > 0){
					page--;
					showMenu();
				}
			break;
			case 0x31:
				showProduct(1);
			break;
			case 0x32:
				showProduct(2);
			break;
			case 0x33:
				showProduct(3);
			break;
			case 0x34:
				showProduct(4);
			break;
		}
	
	
	}
	// return 0;
}
