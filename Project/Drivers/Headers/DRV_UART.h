#ifndef __DRV_UART_H__
#define __DRV_UART_H__

void DRV_UART_Init(void);
void DRV_UART_Taks(void);
uint8_t * DRV_UART_Get_Tags(uint8_t index);
int DRV_UART_Get_Index();
int DRV_UART_Checksum_Verify(void);
#endif 