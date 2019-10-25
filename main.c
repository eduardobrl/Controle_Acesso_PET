/**************************************************
* Centro Universitario FEI
* Disciplina EL9630 / NEA630
* Mini Projeto Dirigido 02 – Timer / Interrupções – Agosto / 2017 rev03
* Silvana Gasparotto de Souza
**************************************************/
#include "ior5f100le.h"
#include "ior5f100le_ext.h"
#include "intrinsics.h"
#include "myRL78.h"
#include "Modules.h"
#include "CTRL_Button.h"
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
// Configura security ID
#pragma location = "SECUID"
__root __far const char senha[10] = {0,0,0,0,0,0,0,0,0,0};



void init_oscilator(){
  CMC = 0; // desativa osciladores X1 e XT1
  OSMC = 0x10; // configura o LOCO (15kHz) como fonte de clock do IT/RTC
  RTCEN = 1; // habilita o RTC e o IT
  
}


void main( void )
{
  init_oscilator();
  PU7 = P7_PULL;
  PU5 = P5_PULL;
  
  PM7 = P7_MODE;
  PM5 = P5_MODE;
  
  P7 = P7_PORT;
  P5 = P5_PORT;
  
  CTRL_Button_Init();
  
  while (1)
  {  
    CTRL_Button_Task();
  }
}