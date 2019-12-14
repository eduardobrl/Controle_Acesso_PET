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
                          CTRL_PetAccess.c
*****************************************************************************/
              
#include "lcd_16x28b.h"
#include "DRV_Motor.h"
                                          
#define HOOK_ACESSO_BLOQUEADO(petTable)                 0                                
#define HOOK_LIBERAR_ACESSO(petTable)                   0
#define HOOK_ACESSO_LIBERADO(petTable)                  0
#define HOOK_INICIA_LIBERACAO()                         DRV_Motor_Set_Angle(499)
#define HOOK_FINALIZA_LIBERACAO()                       DRV_Motor_Set_Angle(2499)

/*****************************************************************************
                          DRV_RTC.c
*****************************************************************************/
#include "CTRL_PetAccess.h"
                                          
#define HOOK_DRV_RTC_1_SEC_EVENT()                    CTRL_PetAccess_Time_Event();


#endif
