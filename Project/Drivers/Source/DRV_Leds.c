#ifndef __DRV_LEDS_C__
#define __DRV_LEDS_C__

#include "Hardware.h"
#include "DRV_leds.h"

void Liga_Led(LED_TYPE led){
  
  switch(led){
    
    case(LED1):
        CLR_PIN(LED1_OUT);
      break;  
      
  case (LED2):
        CLR_PIN(LED2_OUT);
      break;
      
  case(LED3):
        CLR_PIN(LED3_OUT);
      break;
  }
  
}

void Desliga_Led(LED_TYPE led){
  
  switch(led){
    
    case(LED1):
        SET_PIN(LED1_OUT);
      break;  
      
  case (LED2):
        SET_PIN(LED2_OUT);
      break;
      
  case(LED3):
        SET_PIN(LED3_OUT);
      break;
  }
  
}

#endif 