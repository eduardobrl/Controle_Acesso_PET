#ifndef __DRV_RTC_H__
#define __DRV_RTC_H__
#include <stdint.h>

typedef struct {
  
  uint16_t sec;
  uint16_t min;
  uint16_t hour;
  uint16_t week;
  uint16_t day;
  uint16_t month;
  uint16_t year;
    
} RTC_TIME_TYPE;


void DRV_RTC_Init(void);
RTC_TIME_TYPE DRV_RTC_Clock_Read(void);
void DRV_RTC_Clock_Write(RTC_TIME_TYPE RTC_Time );
void DRV_RTC_Set_Alarm(uint8_t month, uint8_t hour, uint8_t minute);

#endif 