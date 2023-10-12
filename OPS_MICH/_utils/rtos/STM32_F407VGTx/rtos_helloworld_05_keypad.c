/**
  ******************************************************************************
  * @file    rtos_helloworld_05_keypad.c
  * @author  SPSE Havirov
  * @version 2.0
  * @date    29-June-2022 [v1.0]
  * @brief   Testovaci program pro keypad (s rozlozenim 3x4 nebo 4x4).
  ******************************************************************************
  * @attention
  *
  * Otestovano na:  F407
  * Netestovano:    F411, L152, F401, G071
  *
  ******************************************************************************
  * @history
  *
  *   v1.1  [29-March-2022]
  *         - Port basic prikladu na RTOS
  *
  ******************************************************************************
*/

#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"
#include <stdio.h>


#define DELAY_STEP    750                                  // Krok v ms pro pozdrzeni programu

#define LCD_COLS      8                                    // Pocet sloupcu pouziteho displeje
#define LCD_ROWS      2                                    // Pocet radku pouziteho displeje

#define LCD_8x2 (((LCD_COLS) == 8) && ((LCD_ROWS) == 2))
#define LCD_16x2 (((LCD_COLS) == 16) && ((LCD_ROWS) == 2))

#define KEYPAD_COLS   4                                    // Pocet sloupcu pouziteho KeyPad
#define KEYPAD_ROWS   4                                    // Pocet radku pouziteho KeyPad
#define KEYPAD_STYLE  0                                    // Vyber znaku pro keypad, mozno uzivatelsky rozsirit/menit. Pokud bude zakomnentovano, nastavi se defaultni rozlozeni

#include "stm32_kit.h"                                     // Pripojeni globalniho konfiguracniho souboru pro praci s pripravkem.                          
#include "stm32_kit/lcd.h"                                 // Pripojeni konfiguracniho souboru pro praci s LCD.
#include "stm32_kit/keypad.h"                              // Pripojeni konfiguracniho souboru pro praci s KeyPad.

#if !defined(KEYPAD_STYLE) || (KEYPAD_STYLE == 0)
static uint8_t KeyPad_KeyMap[KEYPAD_ROWS][KEYPAD_COLS] = {
    // Defaultni rozlozeni pro 4x4 KeyPad
    {'1', '2', '3', 'A' },
    {'4', '5', '6', 'B' },
    {'7', '8', '9', 'C' },
    {'*', '0', '#', 'D' }
};
#elif (KEYPAD_STYLE == 1)
static uint8_t KeyPad_KeyMap[KEYPAD_ROWS][KEYPAD_COLS] = {
    // Alternativni rozlozeni pro 4x4 KeyPad
    { 'a', 'b', 'c', 'd' },
    { 'e', 'f', 'g', 'h' },
    { 'i', 'j', 'k', 'l' },
    { 'm', 'n', 'o', 'p' }
};
#elif (KEYPAD_STYLE == 2)
static uint8_t KeyPad_KeyMap[KEYPAD_ROWS][KEYPAD_COLS] = {
    // Alternativni rozlozeni pro 4x4 KeyPad
    { 'q', 'r', 's', 't' },
    { 'u', 'v', 'w', 'x' },
    { 'y', 'z', '[', ']' },
    { '.', ',', '-', '=' }
};
#endif
 
/*----------------------------------------------------------------------------
 * Application main thread
 *---------------------------------------------------------------------------*/
__NO_RETURN static void app_main (void *argument) {
  (void)argument;
  LCD_setup();      // Pocatecni inicializace LCD, nutne pro dalsi praci s LCD.
  KeyPad_setup();   // Pocatecni inicializace keypadu, nutne pro dalsi praci s keypad.

                      //"        "
  char text0802_1[] = "  Test  ";
  char text0802_2[] = " KeyPad ";

                    //"                "
  char text1602_1[] = "      Test      ";
  char text1602_2[] = "     KeyPad     ";

  for (;;) {
    LCD_set(LCD_CLR);
    LCD_set(LCD_CUR_OFF);

    if (LCD_8x2) {
      LCD_set(LCD_LINE1);
      LCD_print(text0802_1);

      LCD_set(LCD_LINE2);
      LCD_print(text0802_2);
    }
    else if (LCD_16x2) {
      LCD_set(LCD_LINE1);
      LCD_print(text1602_1);

      LCD_set(LCD_LINE2);
      LCD_print(text1602_2);
    }

    delay_ms(2 * DELAY_STEP);
  
    LCD_set(LCD_CLR);
    LCD_set(LCD_LINE1);
    LCD_set(LCD_CUR_BLINK);

    uint8_t znak;
    for (int i = 2 * LCD_COLS; i; --i) {
      if (LCD_COLS == i) {
          LCD_set(LCD_LINE2);
      }

      do {
        znak = KeyPad_getKey();
      } while(!znak);

      LCD_symbol(znak);
    }
  }
}

BOARD_SETUP void setup_rtos(void) {
    SystemCoreClockUpdate();
    osKernelInitialize();
    osThreadNew(app_main, NULL, NULL);
    osKernelStart();
}
 
int main (void) {
  while (1) {} /* main STUB */
}
