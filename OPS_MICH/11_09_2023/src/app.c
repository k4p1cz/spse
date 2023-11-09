/**
 * @file   app.c
 * @author Teodor Kapitanov
 * 
 */

#include "stm32_kit.h"
#include "stm32_kit/lcd.h"
#include "stm32_kit/button.h"
#include "stdio.h"
#include "math.h"


#define LCD_8x2 (((LCD_COLS) == 8) && ((LCD_ROWS) == 2))
#define LCD_16x2 (((LCD_COLS) == 16) && ((LCD_ROWS) == 2))

OS_TID tsk_lcd_display;
OS_TID count_tsk;
OS_TID tsk_button;

#define COUNT_STEP 100;

int count_milisecs = 0;
int mezicas = 0;
int clicked_once = 0;
int saved_secs = 0;
int saved_milisecs = 0;
int saved_mins = 0;

__task void displayLCD() {
	for(;;){
			LCD_set(LCD_CUR_OFF);
			LCD_set(LCD_LINE1);
			char time[8];
			int loc_secs = 0;
			int loc_milisecs = count_milisecs;
			int loc_mins = 0;
				
			while(loc_milisecs >= 1000){
				loc_secs++;
				loc_milisecs = loc_milisecs-1000;
			}
			while(loc_secs > 60){
				loc_mins++;
				loc_secs = loc_secs-60;
			}
			sprintf(time, "%02d:%02d:%02d", loc_mins, loc_secs, loc_milisecs/10);
			LCD_print(time);
			
			if(mezicas > 0){
				/*if(mezicas > 1){
					int loc_c_milisecs = loc_milisecs - saved_milisecs;
					int loc_c_mins = loc_mins - saved_mins;
					int loc_c_secs = loc_secs - saved_secs;
					if(loc_c_milisecs < 0){
						loc_c_milisecs = loc_c_milisecs + 1000;
						loc_c_secs = loc_c_secs - 1;
					}
					if(loc_c_secs < 0){
						loc_c_secs = loc_c_secs + 60;
						loc_c_mins = loc_c_mins - 1;
					}

					
					char difference[8];
					sprintf(difference, "%02d:%02d:%02d", loc_c_mins, loc_c_secs, loc_c_milisecs/10);
					LCD_set(LCD_LINE2);
					LCD_print(difference);
					mezicas = 0;
				}else{*/
					LCD_set(LCD_LINE2);
					saved_secs = loc_mins;
					saved_milisecs = loc_milisecs;
					saved_mins = loc_mins;
					LCD_print(time);
					mezicas = 0;
				//}	
			}
	}
}

__task void count(){
	while(1){
		delay_ms(1);
		count_milisecs = count_milisecs + 1;
	}
}

__task void button(){
	for(;;){
		if (io_read(USER_BUTTON)){
			mezicas = 1;
			//clicked_once++;
			/*if(clicked_once > 0){
				mezicas = 2;
				clicked_once = 0;
			}*/
		}
		delay_ms(100);
	}
}


__task void setup() {   
  LCD_setup();    
	BTN_setup();
	
	tsk_lcd_display = os_tsk_create(displayLCD, 0);
	count_tsk = os_tsk_create(count, 0);
	tsk_button = os_tsk_create(button, 0);
	os_tsk_delete_self();
}

int main () {
	os_sys_init(setup);
}

