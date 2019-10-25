#ifndef __HOOKS_H__
#define __HOOKS_H__


/*****************************************************************************
                          DRV_LEDS
*****************************************************************************/

#include "DRV_Leds.h"

#define HOOK_TURN_LED1_ON()             Liga_Led(LED1)

#define HOOK_TURN_LED2_ON()             Liga_Led(LED1)

#define HOOK_TURN_LED3_ON()             Liga_Led(LED3)

#define HOOK_TURN_ALL_LEDS_OFF()        Desliga_Led(LED1); \
                                        Desliga_Led(LED2); \
                                        Desliga_Led(LED3) 

#include "DRV_Speaker.h"
#define HOOK_SET_MUSICAL_NOTE(note)     DRV_Speaker_Nota_Musical(note)
#define HOOK_TURN_OFF_MUSICAL()         DRV_Speaker_Turn_Off()
                                          
/*****************************************************************************
                          
*****************************************************************************/
#endif