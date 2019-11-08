#include "Hardware.h"

#ifndef __DRV_RTC_C__
#define __DRV_RTC_C__

/****************************************************************************
                             INCLUDES
*****************************************************************************/
#include "DRV_RTC.h"
#include "ior5f100le.h"
#include "ior5f100le_ext.h"
#include "intrinsics.h"
#include "myRL78.h"
/****************************************************************************
                             MACROS LOCAIS
*****************************************************************************/
#define pwrtwo(x)               (1 << (x))              
#define DESIRE_BAUDURATE       9600
#define SYSTEM_CLOCK           32E6
#define CLOCK_DIV              pwrtwo(SAU_CK0_DIV16) //*GLOBAL

/*CALCULATE BAUDURATE BASED ON DESIRED BAUDURATE*/
#define BAUDURATE_VAL        (unsigned short)((SYSTEM_CLOCK)/ ( CLOCK_DIV * 2.0 * DESIRE_BAUDURATE) - 1.0)

/****************************************************************************
                             VARIAVEIS GLOBAIS
*****************************************************************************/
struct {
  
  RTC_TIME lastRead;
  
  
} drvRTC_Obj;

enum {
  DOMINGO,
  SEGUNDA,
  TERCA,
  QUARTA,
  QUINTA,
  SEXTA,
  SABADO
} week_days;


/****************************************************************************
                             DELCARAÇÃO DE FUNÇÕES LOCAIS
*****************************************************************************/
void drv_RTC_Pause_Count();
void drv_RTC_Resume_Count();
/****************************************************************************
                             FUNÇÕES GLOBAIS
*****************************************************************************/
/*
@brief: Inicializa o driver de UART 
@param: None
*/ 
void DRV_RTC_Init(void)
{
  /*Supplies input clock.*/
  RTCEN         = 1 ; 
  
  /*Stops counter operation.*/
  RTCE          = 0;
    
  //Sets fRTC
  OSMC          = bWUTMMCK0;

  //Selects 12-/24-hour system and interrupt (INTRTC).
  RTCC0         = bAMPM | INT_RTC_1S;

  //Sets timer registers
  SEC           = 0;
  MIN           = 0;
  HOUR          = 0;
  WEEK          = 0;
  DAY           = 0;
  MONTH         = 0;
  YEAR          = 0;
  
  //Sets watch error correction register.
  SUBCUD         = 0;
  
  //Clears interrupt request flags (RTCIF).
  RTCIF         = 0;
  
  //Clears interrupt mask flags (RTCMK).
  RTCMK         = 0;
  
  RTCE          = 1;
  
  //while(RTCIF == 0);
}

/*
@brief: Lê todos os registradores de tempo do RTC
@param: None
@return: Devolve uma struct contendo todas as leituras
*/ 
RTC_TIME DRV_RTC_Clock_Read(void){
  
  drv_RTC_Pause_Count();
  
  drvRTC_Obj.lastRead.sec        = SEC;
  drvRTC_Obj.lastRead.min        = MIN;
  drvRTC_Obj.lastRead.hour       = HOUR;

  #if defined(I_SUPORT_FAST_DEMONSTRATION)
    drvRTC_Obj.lastRead.day        = DAY;
    drvRTC_Obj.lastRead.month      = MONTH;
    drvRTC_Obj.lastRead.year       = YEAR;
    drvRTC_Obj.lastRead.week       = WEEK;
  #endif
  
  drv_RTC_Resume_Count();
  
  return drvRTC_Obj.lastRead;
  
}

/*
@brief: Lê todos os registradores de tempo do RTC
@param: RTC_TIME - Struct com informações de tempo
@return: 
*/ 
void DRV_RTC_Clock_Write(RTC_TIME RTC_Time ){
  
  drv_RTC_Pause_Count();
  
  drvRTC_Obj.lastRead.hour       = RTC_Time.hour;
  drvRTC_Obj.lastRead.min        = RTC_Time.min;
  drvRTC_Obj.lastRead.sec        = RTC_Time.sec;

  HOUR                           = drvRTC_Obj.lastRead.hour;
  MIN                            = drvRTC_Obj.lastRead.min;
  SEC                            = drvRTC_Obj.lastRead.sec;
 
  #if defined(I_SUPORT_FAST_DEMONSTRATION)
    drvRTC_Obj.lastRead.day        = RTC_Time.day;
    drvRTC_Obj.lastRead.month      = RTC_Time.month;
    drvRTC_Obj.lastRead.year       = RTC_Time.year;
    drvRTC_Obj.lastRead.week       = RTC_Time.week;
    
    DAY                            = drvRTC_Obj.lastRead.day;
    WEEK                           = drvRTC_Obj.lastRead.week;
    MONTH                          = drvRTC_Obj.lastRead.month;
    YEAR                           = drvRTC_Obj.lastRead.year;
  #endif
  
  drv_RTC_Resume_Count();
 
}

/*
@brief: Escolhe 
@param: RTC_TIME - Struct com informações de tempo
@return: 
*/ 
void DRV_RTC_Set_Alarm(uint8_t month, uint8_t week, uint8_t hour){
   
  WALE                          = 0;
  WALIE                         = 1;
  
  ALARMWM                       = month;
  ALARMWH                       = hour;
  ALARMWW                       = week;
  
  WALE = 1;

}

/*
@brief: Escolhe 
@param: RTC_TIME - Struct com informações de tempo
@return: 
*/ 
void DRV_RTC_Reload(RTC_TIME * pTime, RTC_TIME * pReload){
  
  pTime -> sec = pReload ->sec;
  pTime -> min = pReload ->min;
  pTime -> hour = pReload ->hour;

}

/*
@brief: Escolhe 
@param: RTC_TIME - Struct com informações de tempo
@return: 
*/ 
void DRV_RTC_Add_Sec(RTC_TIME * pTime, WORD secs){
  WORD min;
  
  min = secs / 60;
  secs = secs % 60;
  
  DRV_RTC_Add_Min(pTime, min);
  
  pTime ->sec +=  secs;
  
  pTime ->sec %= 60;
    
}


/*
@brief: Escolhe 
@param: RTC_TIME - Struct com informações de tempo
@return: 
*/ 
void DRV_RTC_Add_Min(RTC_TIME * pTime, WORD mins){
  
  pTime ->min +=  mins;
  
  pTime ->min %= 60;
}


/*
@brief: Escolhe 
@param: RTC_TIME - Struct com informações de tempo
@return: 
*/ 
void DRV_RTC_Rem_Sec(RTC_TIME * pTime, WORD secs){
  volatile WORD min, temp;
  
  min = secs / 60;
  secs %= 60;
   
  if(pTime->sec > secs){
    pTime->sec -= secs;
  }
  
  else{
    temp = pTime->sec;
    secs = secs - temp;
    pTime->sec = 60 - secs ;  
    
    DRV_RTC_Rem_Min(pTime,1); //removes 1 minute
  }
  
  DRV_RTC_Rem_Min(pTime,min);
  
}


/*
@brief: Escolhe 
@param: RTC_TIME - Struct com informações de tempo
@return: 
*/ 
void DRV_RTC_Rem_Min(RTC_TIME * pTime, WORD mins){
  volatile WORD temp;
  
  mins %= 60;
  
  if(pTime->min > mins){
    pTime->min -= mins; 
  }
  
  else{
    temp = pTime->min;
    mins = mins - temp;
    pTime->min = 60 - mins ;
  }

}

/*
@brief: Escolhe 
@param: RTC_TIME - Struct com informações de tempo
@return: 
*/ 
WORD DRV_RTC_Is_Ready(RTC_TIME * pTime){
  
  if( (pTime ->sec == 0) && (pTime ->min == 0) ){
    return 1;
  }
  
  return 0;
  
}

#pragma vector = INTRTC_vect // escreve função de interrupção no vetor do IT
__interrupt void DRV_RTC_IT_Handler(void){
  

}
  


/****************************************************************************
                             FUNÇÕES LOCAIS
*****************************************************************************/



void drv_RTC_Pause_Count(){
  RWAIT = 1;
  while(RWST ==0);
  
}

void drv_RTC_Resume_Count(){
  RWAIT = 0;
  while(RWST == 1);
}

#endif 