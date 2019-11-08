#include "Hardware.h"

#ifndef __DRV_UART_C__
#define __DRV_UART_C__

#ifdef I_SUPPORT_DRV_UART

/****************************************************************************
                             INCLUDES
*****************************************************************************/
#include "ior5f100le.h"
#include "ior5f100le_ext.h"
#include "intrinsics.h"

#include "DRV_UART.h"
#include "myRL78.h"
#include "Configurations.h"

/****************************************************************************
                             MACROS LOCAIS
*****************************************************************************/
#define pwrtwo(x)               (1 << (x))              
#define DESIRE_BAUDURATE       9600
#define SYSTEM_CLOCK           32E6
#define CLOCK_DIV              pwrtwo(SAU_CK0_DIV16) //*GLOBAL

/*CALCULATE BAUDURATE BASED ON DESIRED BAUDURATE*/
#define BAUDURATE_VAL        (unsigned short)((SYSTEM_CLOCK)/ ( CLOCK_DIV * 2.0 * DESIRE_BAUDURATE) - 1.0)

#define UART_BUFFER_SIZE        256

#define __9600BPS               51 << 9
#define LED P7_bit.no7

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


void drv_UART_0_Init(void);
void drv_UART_2_Init(void);


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
  
  drv_UART_0_Init();
  
#if defined(NOT_DEBUGGING)
  drv_UART_2_Init();
#endif
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


/****************************************************************************
                             FUNÇÕES LOCAIS
*****************************************************************************/




void drv_UART_0_Init(void){
   PM1_bit.no1 = 1; // P11/RXD0 como entrada
   PIM1_bit.no1 = 1;
   
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
  
  SPS0 = SAU_CK0_DIV32;//SAU_CK0_DIV16;
  
   /*
  * Setting the SMRmn and SMRmr registers
  * Set an operation mode, etc.
  */
  
  SMR01 = bSAU_STS | SAU_MD_UART;
  
   /*
  * Setting the SCRmn register
  * Set a communication format.
  */
  
  SCR01 = SAU_COMM_RX | SAU_NO_PARITY | SAU_LSB_FIRST | SAU_ONE_STOP | SAU_8BITS;
  
   /*
  * Setting the SDRmn register
  * Set a transfer baud rate
  */
  SDR01 = __9600BPS;
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
  
  NFEN0 = SNFEN00;
 // Dispara os canais 1 da SA0
  SS0 = SAU_CH1;
  SRMK0 = 0;
}


void drv_UART_2_Init(void)
{
 PM1_bit.no3 = 0; // P13/TXD2 como saída
 P1_bit.no3 = 1; // coloca TXD2 em 1 (importante!!!)
 PM1_bit.no4 = 1; // P14/RXD2 como entrada
 PM7_bit.no7 = 0; // P77 como saída (led)
 LED = 1; // desliga o led 
 
 SAU1EN = 1; // ativa a SAU1
 // Clock CK0 da SAU1 = 32MHz / 32 = 1MHz
 SPS1 = SAU_CK0_DIV32;
 // Configura o canal 0 da SAU1 (transmissão da UART2)
 SMR10 = SAU_MD_UART | SAU_INT_BUFFER;
 SCR10 = SAU_COMM_TX | SAU_NO_PARITY | SAU_LSB_FIRST | SAU_ONE_STOP | SAU_8BITS;
 SDR10 = __9600BPS; // seta o baud rate do transmissor
 // Configura o canal 1 da SAU1 (recepção da UART2)
 SMR11 = bSAU_STS | SAU_MD_UART;
 SCR11 = SAU_COMM_RX | SAU_NO_PARITY | SAU_LSB_FIRST | SAU_ONE_STOP | SAU_8BITS;
 SDR11 = __9600BPS; // seta o baud rate do receptor
 SOE1 = SAU_CH0; // habilita a saída da UART2
 SO1 = SAU_CH0; // seta a saída TXD2
 NFEN0 = SNFEN20; // ativa o filtro digital da entrada RXD2
 // Dispara os canais 0 e 1 da SAU1
 SS1 = SAU_CH1 | SAU_CH0;
 SRMK2 = 0; // habilita a interrupção de recepção da UART

}


/****************************************************************************
                             TRATAMENTO DE INTERRUPÇÕES
*****************************************************************************/

#pragma vector = INTSR0_vect // escreve função de interrupção no vetor do IT
__interrupt  void DRV_UART_RX_IT(){
  
 unsigned char temp;
 temp = RXD0; // lê o caractere recebido
 TXD2 = temp; // envia o caractere (seguinte)
  
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
      drvUART_obj.status = IDLE;      
      break;
  }
  
  SRIF0 = 0;
}


#pragma vector = INTSR2_vect
__interrupt void trata_rx_UART2(void)
{
 unsigned char temp;
 temp = RXD2; // lê o caractere recebido
 TXD2 = temp+1; // envia o caractere (seguinte)
 if (temp=='a') LED = 0; // se recebeu "a", liga o led
 if (temp=='b') LED = 1; // se recebeu "b", desliga o led
}
#pragma vector = INTST2_vect
__interrupt void trata_tx_UART2(void)
{
}






#endif
#endif 

