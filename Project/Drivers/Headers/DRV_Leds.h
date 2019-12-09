#ifndef __DRV_LEDS_H__
#define __DRV_LEDS_H__




typedef enum{
  LED_RED,
  LED_GREEN,
  LED_BLUE 
  
} LED_TYPE;



#define         LED_RED_PORT            5
#define         LED_GREEN_PORT          5
#define         LED_BLUE_PORT           5

#define         LED_RED_PIN             3
#define         LED_GREEN_PIN           2
#define         LED_BLUE_PIN            1

#define         REGISTER_MASK2(port, pin)              P ## port ## _bit.no ## pin 
#define         REGISTER_MASK(port, pin)             REGISTER_MASK2(port, pin) 

#define         _PORT_PIN_TO_OUT_REG(port, pin)       REGISTER_MASK(port, pin)
#define         _PORT_PIN_TO_MODE_REG(port, pin)      P ## port ## _bit.no ## pin  



void DRV_LEDS_Liga(LED_TYPE led);
void DRV_LEDS_Desliga_Led(LED_TYPE led);
void Alterna_Led();


#endif 