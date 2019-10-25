#ifndef __DRV_LEDS_H__
#define __DRV_LEDS_H__




typedef enum{
  LED1,
  LED2,
  LED3 
  
} LED_TYPE;


void Liga_Led(LED_TYPE led);
void Desliga_Led(LED_TYPE led);
void Alterna_Led();


#endif 