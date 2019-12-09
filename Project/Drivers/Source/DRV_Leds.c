#ifndef __DRV_LEDS_C__
#define __DRV_LEDS_C__

#include "Hardware.h"
#include "DRV_Leds.h"

void DRV_LEDS_Init(){
  _PORT_PIN_TO_MODE_REG(LED_RED_PORT, LED_RED_PIN)      = 1;
  _PORT_PIN_TO_MODE_REG(LED_GREEN_PORT, LED_GREEN_PIN)      = 1;
  _PORT_PIN_TO_MODE_REG(LED_BLUE_PORT, LED_BLUE_PIN)      = 1;
  
}


void DRV_LEDS_Liga(LED_TYPE led){
  
  switch(led){
    
    case(LED_RED):
        CLR_PIN(LED_RED_OUT);
      break;  
      
  case (LED_GREEN):
        CLR_PIN(LED_GREEN_OUT);
      break;
      
  case(LED_BLUE):
        CLR_PIN(LED_BLUE_OUT);
      break;
  }
  
}

void DRV_LEDS_Desliga_Led(LED_TYPE led){
  
  switch(led){
    
    case(LED_RED):
        SET_PIN(LED_RED_OUT);
      break;  
      
  case (LED_GREEN):
        SET_PIN(LED_GREEN_OUT);
      break;
      
  case(LED_BLUE):
        SET_PIN(LED_BLUE_OUT);
      break;
  }
  
}

#endif 