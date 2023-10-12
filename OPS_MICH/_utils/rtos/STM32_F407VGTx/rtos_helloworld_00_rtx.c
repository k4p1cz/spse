#include <RTL.h>
#include "stm32_kit.h"
#include "stm32_kit/led.h"

OS_TID taskID1;
OS_TID taskID2;

__task void Turn_GreenLed_On(void) {
    for (;;) {
        //os_tsk_pass (); 
    }
}

__task void Turn_GreenLed_Off(void){
    for (;;) {
        //os_tsk_pass (); 
    }
}


__task void board_init(void) {
    LED_setup();
    
    taskID1 = os_tsk_create(Turn_GreenLed_On, 0);
    taskID2 = os_tsk_create(Turn_GreenLed_Off, 0);

    os_tsk_delete_self (); // Delete the init(self) task
}

int main(void) {
    os_sys_init(board_init);
}
