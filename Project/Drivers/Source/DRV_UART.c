#include "Hardware.h"

#ifndef __DRV_UART_C__
#define __DRV_UART_C__

/****************************************************************************
                             INCLUDES
*****************************************************************************/
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

//RDM6300
#define HEAD_BYTE                 0x02
#define NUMBER_OF_DATA_BYTES      0x10
#define CHECKSUM_BITE             0x01
#define LAST_BITE                 0x03




/*CALCULATE BAUDURATE BASED ON DESIRED BAUDURATE*/
#define BAUDURATE_VAL        (unsigned short)((SYSTEM_CLOCK)/ ( CLOCK_DIV * 2.0 * DESIRE_BAUDURATE) - 1.0)

#define UART_BUFFER_SIZE        256



struct {
  uint8_t firstByteIdx;
  uint8_t lastByteIdx;
      
 struct{
      uint8_t head;
      uint8_t data[10];
      uint8_t checksum;
      uint8_t last;
    };
  
 
} drvUART_obj;

/****************************************************************************
                             FUNÇÕES GLOBAIS
*****************************************************************************/

/*
@brief: Inicializa o driver de UART 
@param: None
*/ 
void DRV_UART_Init(void)
{
  /*
  * Setting the PER0 register
  * Release the serial array unit from the
  * reset status and start clock supply.
  */
  SAU0EN = 1;

  /*
  * Setting the SPSm register
  * Set the operation clock.
  */
  
  SPS0 = SAU_CK0_DIV16;
  
   /*
  * Setting the SMRmn and SMRmr registers
  * Set an operation mode, etc.
  */
  
  SMR00 = SAU_MD_UART;
  
   /*
  * Setting the SCRmn register
  * Set a communication format.
  */
  
  SCR00 = SAU_8BITS | SAU_NO_PARITY | SAU_COMM_RX;
  
   /*
  * Setting the SDRmn register
  * Set a transfer baud rate
  */
  SDR00 = (BAUDURATE_VAL << 8);
   /*
  * Setting port
  * Enable data input of the target channel
  * by setting a port register and a port
  * mode register.
  */
  
   /*
  * Writing to the SSm register
  * 
  */
  SS0 = SAU_CH0;
  
}

void DRV_UART_RX_IT(){
  
  uint8_t received;
  
  drvUART_obj.head = TXD0;
  
  if(drvUART_obj.head == 0x02){
    
    
    
  }
  
  
}


#endif 