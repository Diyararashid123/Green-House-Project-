#include "at91sam3x8.h"

#include "system_sam3x.h"

#include "functions.h"

#include <time.h>

#include <stdio.h>

#include <string.h>


int main() {
  SystemInit();
  SysTick_Config(SystemCoreClock * 0.001);
  
  set_Display();
  Init_Display();
  clear_Display();
  Read_Status_Display();
  set_KeyPad();
  Init_Temp();
  Init_Light();
  Init_PWM_Servo();
  set_menu();
  set_tempscreen();
  set_Buttons();
  set_Date();

  while (1) {

   
    
    Green_House();

  }

  return 0;
}

