#ifndef __DRV_MOTOR_H__
#define __DRV_MOTOR_H__

#include "Types.h"
#include "Hardware.h"


#define  DRV_MOTOR_CLOCK                    (TAU_CK0_DIV32)
#define  DRV_MOTOR_CLOCK_VAL                (SYSTEM_CLOCK/(1<<TAU_CK0_DIV32))
#define  DRV_MOTOR_FREQ_HZ                  (1 / 20E-3) 

#define  DRV_MOTOR_FREQ_VAL                (WORD)( ( DRV_MOTOR_CLOCK_VAL/ DRV_MOTOR_FREQ_HZ) - 1)

#define DRV_MOTOR_CLOCK_DUTY(duty)          (( DRV_MOTOR_FREQ_VAL*duty) / 100)

#define DRV_MOTOR_0_GRAUS_FREQ              (1 / 1.0E-3) 
#define DRV_MOTOR_90_GRAUS_FREQ             (1 / 0.6E-3)  
#define DRV_MOTOR_180_GRAUS_FREQ            (1 / 1.5E-3)        
#define DRV_MOTOR_270_GRAUS_FREQ            (1 / 2.4E-3)    

#define DRV_MOTOR_0_GRAUS_VAL               (WORD)( (DRV_MOTOR_CLOCK_VAL / DRV_MOTOR_90_GRAUS_FREQ) - 1)             
#define DRV_MOTOR_90_GRAUS_VAL              (WORD)( (DRV_MOTOR_CLOCK_VAL / DRV_MOTOR_180_GRAUS_FREQ) - 1)   
#define DRV_MOTOR_180_GRAUS_VAL             (WORD)( (DRV_MOTOR_CLOCK_VAL / DRV_MOTOR_270_GRAUS_FREQ) - 1)   
#define DRV_MOTOR_270_GRAUS_VAL             (WORD)( (DRV_MOTOR_CLOCK_VAL / DRV_MOTOR_270_GRAUS_FREQ) - 1)   

void DRV_Motor_Init(void);
void DRV_Motor_Set_Angle(WORD angle );

#endif 