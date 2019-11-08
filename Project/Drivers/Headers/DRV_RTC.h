#ifndef __DRV_RTC_H__
#define __DRV_RTC_H__
#include <stdint.h>

typedef struct {
  
  uint16_t sec;
  uint16_t min;
  uint16_t hour;
  
  #if defined(I_SUPORT_FAST_DEMONSTRATION)
    uint16_t week;
    uint16_t day;
    uint16_t month;
    uint16_t year;
  #endif
} RTC_TIME;


void DRV_RTC_Init(void);
RTC_TIME DRV_RTC_Clock_Read(void);
void DRV_RTC_Clock_Write(RTC_TIME RTC_Time );
void DRV_RTC_Set_Alarm(uint8_t month, uint8_t hour, uint8_t minute);
void DRV_RTC_Reload(RTC_TIME * pTime, RTC_TIME * pReload);
void DRV_RTC_Add_Min(RTC_TIME * pTime, WORD mins);
void DRV_RTC_Add_Sec(RTC_TIME * pTime, WORD secs);
void DRV_RTC_Rem_Sec(RTC_TIME * pTime, WORD secs);
void DRV_RTC_Rem_Min(RTC_TIME * pTime, WORD mins);

WORD DRV_RTC_Is_Ready(RTC_TIME * pTime);
#endif //__DRV_RTC_H__