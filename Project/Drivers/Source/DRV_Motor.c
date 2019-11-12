#include "Hardware.h"
#include "DRV_Motor.h"
#include "ior5f100le.h"
#include "ior5f100le_ext.h"
#include "intrinsics.h"
#include "myRL78.h"

#ifndef __DRV_MOTOR_C__
#define __DRV_MOTOR_C__



void DRV_Motor_Init(){
  
 PM1 = 0x3F; // P17 e P16 como sa�das (canais 1 e 2 da TAU0)
 TAU0EN = 1; // habilita a TAU0
 TPS0 = DRV_MOTOR_CLOCK; // CK0=1MHz, CK1=32MHz, CK2=16MHz e CK3=125kHz
 // configura o canal 0 no modo mestre para PWM
 TMR00 = TAU_CK0 | TAU_TRIG_SOFT | TAU_MD_TIMER_TRIG_INT;
 // configura os canais 1 e 2 no modo escravo para PWM
 TMR01 = TAU_CK0 | TAU_TRIG_MASTER | TAU_MD_ONECOUNT_TRIG;
 //TMR02 = TAU_CK0 | TAU_TRIG_MASTER | TAU_MD_ONECOUNT_TRIG;
 TDR00 = DRV_MOTOR_FREQ_VAL; // per�odo do sinal PWM = 1kHz
 TDR01 = DRV_MOTOR_CLOCK_DUTY(DRV_MOTOR_0_GRAUS_VAL); // canal 1 = 10% de ciclo ativo
 TDR02 = DRV_MOTOR_CLOCK_DUTY(DRV_MOTOR_180_GRAUS_VAL); // canal 2 = 90% de ciclo ativo
 TOE0L = TAU_CH2 | TAU_CH1; // habilita a sa�da dos canais 1 e 2 da TAU0
 // sa�da dos canais 1 e 2 controladas pelo mestre/escravo
 TOM0L = TAU_CH2 | TAU_CH1;
 // dispara os canais mestre e escravos
 TS0L = TAU_CH0 | TAU_CH1 | TAU_CH2; 
  
  
}



void DRV_Motor_Set_Angle(WORD angle ){

    TDR01 = angle;

}




#endif 

