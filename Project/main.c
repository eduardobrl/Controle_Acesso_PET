/**************************************************
* Centro Universitario FEI
* Disciplina EL9630 / NEA630
* Mini Projeto Dirigido 02 – Timer / Interrupções – Agosto / 2017 rev03
* Silvana Gasparotto de Souza
**************************************************/
#include "Hardware.h"

#include "ior5f100le.h"
#include "ior5f100le_ext.h"
#include "intrinsics.h"
#include "myRL78.h"
#include "CTRL_Button.h"

#include "DRV_UART.h"
#include "DRV_RTC.h"
#include "lcd_16x28b.h"
#include "CTRL_PetAccess.h"

#include "Hardware.h"

// Configura watchdog = desligado
#pragma location = "OPTBYTE"
__root __far const char opbyte0 = WDT_OFF;
// Configura detector de baixa tensão = desligado
#pragma location = "OPTBYTE"
__root __far const char opbyte1 = LVD_OFF;
// oscilador 32MHz flash high speed
#pragma location = "OPTBYTE"
__root __far const char opbyte2 = FLASH_HS | CLK_32MHZ; 
// debug ativado, com apagamento em caso de falha de autenticação
#pragma location = "OPTBYTE"
__root __far const char opbyte3 = DEBUG_ON_ERASE;
/* Configura security ID */
#pragma location = "SECUID"
__root __far const char senha[10] = {0,0,0,0,0,0,0,0,0,0};

void main( void )
{
  //PU7 = P7_PULL;
  //PM7 = P7_MODE;
  //P7 = P7_PORT;
  
  //PM1 = P1_MODE;
  //P1 = P1_PORT;
  
  //CTRL_Button_Init();
  LCD_init_4_bits();
  DRV_UART_Init();
  DRV_RTC_Init();
  DRV_Motor_Init();
  __enable_interrupt(); // habilita as interrupções do RL78
  while (1)
  {  
    CTRL_Pet_Access_Tasks();
    DRV_UART_Taks();
  }
}
