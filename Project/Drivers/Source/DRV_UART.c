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
#define NUMBER_OF_DATA_BYTES      0x04
#define NUMBER_OF_CHECKSUM_BYTES  0x02
#define NUMBER_OF_FINISH_BYTES    0x01
#define LAST_BITE                 0x03

/*CALCULATE BAUDURATE BASED ON DESIRED BAUDURATE*/
#define BAUDURATE_VAL        (unsigned short)((SYSTEM_CLOCK)/ ( CLOCK_DIV * 2.0 * DESIRE_BAUDURATE) - 1.0)

#define UART_BUFFER_SIZE        256

typedef union {
  
  struct{
    uint8_t     nb1;
    uint8_t     nb2;
    uint8_t     nb3;
    uint8_t     nb4;
  };
  
  uint64_t buf;
  
} tag_64;

struct {
  
  enum{
    IDLE,
    DATA,
    CHECKSUM,
    FINISH,
    READY    
  } status;
      
 struct{
      uint8_t head;
      uint8_t data[NUMBER_OF_DATA_BYTES];
      uint8_t checksum;
      uint8_t last;
    };
  
 uint8_t data_count;
 
 tag_64  tag_buffer[UART_BUFFER_SIZE];
 
 uint8_t buffer_idx;
 
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
  /*Global structure initialization*/
  drvUART_obj.status            = IDLE;
  drvUART_obj.head              = 0x00;
  drvUART_obj.checksum          = 0x00;
  drvUART_obj.last              = 0x00;
  drvUART_obj.data_count        = 0x00;
  drvUART_obj.buffer_idx        = 0x00;
  
  /*Peripheral Initialization*/
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
  
  switch(drvUART_obj.status){
       
  
  case IDLE:   
    drvUART_obj.head = RXD0;
    if(drvUART_obj.head == HEAD_BYTE) 
    {
      drvUART_obj.status = DATA;
      drvUART_obj.data_count = NUMBER_OF_DATA_BYTES;
    }
    break;
    
  case DATA:
    if(drvUART_obj.data_count < NUMBER_OF_DATA_BYTES)
    {
      drvUART_obj.data[drvUART_obj.data_count] = RXD0;
      drvUART_obj.data_count++;
    }
    else{
      drvUART_obj.status = CHECKSUM;
      drvUART_obj.data_count = 0;
    }  
    break;
    
  case CHECKSUM:
    if(drvUART_obj.data_count < NUMBER_OF_CHECKSUM_BYTES)
    {
      drvUART_obj.checksum= RXD0;
      drvUART_obj.data_count++;
    }
    else{
      drvUART_obj.status = FINISH;
      drvUART_obj.data_count = 0;
    }  
    break;
    
  
  case FINISH:
    if(drvUART_obj.data_count < NUMBER_OF_FINISH_BYTES)
    {
      drvUART_obj.last = RXD0;
      drvUART_obj.data_count++;
      drvUART_obj.status = READY;
    }
    else{
      //ERROR DROP FRAME
      drvUART_obj.status = IDLE;
    }  
    break;
      
    default:
      break;
  }
  
  //LIMPAR FLAG
}


void DRV_UART_Checksum_Verify(void){

  if(drvUART_obj.status == FINISH ){
    int byte, checksum;
    
    for (byte = 0; byte < NUMBER_OF_DATA_BYTES; byte++){
      checksum ^= drvUART_obj.data[byte];
    }
    
    if(checksum != drvUART_obj.checksum){
     //error_drop_frame 
      drvUART_obj.status = IDLE;
    }
    
    else{
      //if checksum is verified then save the tag
      //drvUART_obj.tag_buffer[drvUART_obj.buffer_idx].buf = drvUART_obj.data;
      drvUART_obj.status = IDLE;
    }
    
  }
  
}


#endif 