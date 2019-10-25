#include "Hardware.h"

#ifndef __DRV_SPEAKER_C__
#define __DRV_SPEAKER_C__

/*
@brief: Toca uma nota musical
@param: Valor de contagem para timer

*/ 
void DRV_Speaker_Nota_Musical (int CNT)
{
  ITMC = 0x8000 | CNT;
  /* RINTE=1 p habilitar a interrupção do o IT e configura o timer p gerar interrupções na frequência especificada pelo valor de CNT */
  ITMK = 0; // habilita a interrupção do IT
  __enable_interrupt(); // habilita as interrupções do RL78
}

void DRV_Speaker_Turn_Off(void){
  
  P7_bit.no7 = 0; // buzzer desligado
   __disable_interrupt();// desabilita as interrupções do RL78
  
}


__interrupt void DRV_Speaker_trata_IT(void)
{
    P7_bit.no7 = !P7_bit.no7; // inverte o estado do led
}


#endif __DRV_SPEAKER_C__