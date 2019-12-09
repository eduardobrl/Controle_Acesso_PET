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
#include "lcd_16x28b.h"
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

typedef uint8_t tag_64[NUMBER_OF_DATA_BYTES];

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
      uint8_t checksum[NUMBER_OF_CHECKSUM_BYTES];
      uint8_t last;
    };
  
 uint8_t data_count;
 
 tag_64  tag_buffer[UART_BUFFER_SIZE];
 
 uint8_t buffer_idx;
 
 uint8_t last_read_idx;
 
 
 
} drvUART_obj;


void drv_UART_1_Init(void);
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
  drvUART_obj.last              = 0x00;
  drvUART_obj.data_count        = 0x00;
  drvUART_obj.buffer_idx        = 0x00;
  drvUART_obj.last_read_idx     = 0x00;
  
  drv_UART_2_Init();
  drv_UART_1_Init();
}

void DRV_UART_Taks(void){
  int i;
  
  if(drvUART_obj.status == READY){
    
    if(DRV_UART_Checksum_Verify() && drvUART_obj.last == LAST_BITE){
     drvUART_obj.status = IDLE; 
     
     for(i=0;i< NUMBER_OF_DATA_BYTES; i++)
     
     drvUART_obj.tag_buffer[drvUART_obj.buffer_idx][i] = drvUART_obj.data[i];
     drvUART_obj.buffer_idx++;

    }
    drvUART_obj.status = IDLE;
  }
  
}



int DRV_UART_Checksum_Verify(void){
    int byte, checksum = 0;
    
    for (byte = 0; byte < NUMBER_OF_DATA_BYTES;byte= byte + 2){
     checksum ^= lcd_ASCII_2_Number(drvUART_obj.data[byte], drvUART_obj.data[byte+1]);
      
    }
    
    if(checksum != lcd_ASCII_2_Number(drvUART_obj.checksum[0], drvUART_obj.checksum[1])){
      return 0;
    }
    
    else{
      return 1;
    }
}


uint8_t * DRV_UART_Get_Tag()
{
  
  uint8_t * tag = drvUART_obj.tag_buffer[drvUART_obj.last_read_idx];
  
  if( drvUART_obj.last_read_idx++ > drvUART_obj.buffer_idx)
    drvUART_obj.last_read_idx = drvUART_obj.buffer_idx;
  
  
  return tag ;
}




/****************************************************************************
                             FUNÇÕES LOCAIS
*****************************************************************************/
void drv_UART_1_Init(void)
{
 PM0_bit.no2 = 0; // P13/TXD2 como saída
 P0_bit.no2 = 1; // coloca TXD2 em 1 (importante!!!)
 PM0_bit.no3 = 1; // P14/RXD2 como entrada
 PMC0_bit.no3 = 0;
 
 SAU0EN = 1; // ativa a SAU1
 // Clock CK0 da SAU1 = 32MHz / 32 = 1MHz
 SPS0 = SAU_CK0_DIV32;
 // Configura o canal 0 da SAU0 (transmissão da UART2)
 SMR02 = SAU_MD_UART | SAU_INT_BUFFER;
 SCR02 = SAU_COMM_TX | SAU_NO_PARITY | SAU_LSB_FIRST | SAU_ONE_STOP | SAU_8BITS;
 SDR02 = __9600BPS; // seta o baud rate do transmissor
 // Configura o canal 1 da SAU1 (recepção da UART2)
 SMR03 = bSAU_STS | SAU_MD_UART;
 SCR03 = SAU_COMM_RX | SAU_NO_PARITY | SAU_LSB_FIRST | SAU_ONE_STOP | SAU_8BITS;
 SDR03 = __9600BPS; // seta o baud rate do receptor
 SOE0 = SAU_CH2; // habilita a saída da UART2
 //SO0 = SAU_CH2; // seta a saída TXD2
 NFEN0 = SNFEN10; // ativa o filtro digital da entrada RXD2
 // Dispara os canais 0 e 1 da SAU1
 SS0 = SAU_CH2 | SAU_CH3;
 SRMK1 = 0; // habilita a interrupção de recepção da UART

}


void drv_UART_2_Init(void)
{
 PM1_bit.no3 = 0; // P13/TXD2 como saída
 P1_bit.no3 = 1; // coloca TXD2 em 1 (importante!!!)
 PM1_bit.no4 = 1; // P14/RXD2 como entrada
 
 SRIF2 = 0;
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
 //SO1 = SAU_CH0; // seta a saída TXD2
 NFEN0 = SNFEN20; // ativa o filtro digital da entrada RXD2
 // Dispara os canais 0 e 1 da SAU1
 SS1 = SAU_CH1 | SAU_CH0;
 SRMK2 = 0; // habilita a interrupção de recepção da UART

}


/****************************************************************************
                             TRATAMENTO DE INTERRUPÇÕES
*****************************************************************************/
#pragma vector = INTSR1_vect
__interrupt void trata_rx_UART1(void)
{
 unsigned int temp;
    temp = RXD1; // lê o caractere recebido
    
  switch(drvUART_obj.status){
       

  case IDLE:

    drvUART_obj.head = temp;
    if(drvUART_obj.head == HEAD_BYTE) 
    {
      drvUART_obj.status = DATA;
      drvUART_obj.data_count = 0;
    }
    break;
    
  case DATA:
    
      drvUART_obj.data[drvUART_obj.data_count] = temp;
      drvUART_obj.data_count++;
      
    if(drvUART_obj.data_count == NUMBER_OF_DATA_BYTES)
    {
      drvUART_obj.status = CHECKSUM;
      drvUART_obj.data_count = 0;
    }
     
    break;
    
  case CHECKSUM:
      drvUART_obj.checksum[drvUART_obj.data_count]= temp;
      drvUART_obj.data_count++;
    if(drvUART_obj.data_count == NUMBER_OF_CHECKSUM_BYTES)
    {
      drvUART_obj.status = FINISH;
      drvUART_obj.data_count = 0;
    }
    break;
    
  
  case FINISH:
    drvUART_obj.last = temp;
    drvUART_obj.data_count++; 
    
    if(drvUART_obj.data_count == NUMBER_OF_FINISH_BYTES)
    {
      drvUART_obj.status = READY; 
    }
    break;
      
  case READY:  
    break;
    
    default:
      drvUART_obj.status = IDLE;      
      break;
  }
  
 
}
#pragma vector = INTST1_vect
__interrupt void trata_tx_UART1(void)
{
}



#pragma vector = INTSR2_vect
__interrupt void trata_rx_UART2(void)
{
 unsigned char temp;
 temp = RXD2; // lê o caractere recebido
 TXD2 = temp+1; // envia o caractere (seguinte)
 //if (temp=='a') LED = 0; // se recebeu "a", liga o led
 //if (temp=='b') LED = 1; // se recebeu "b", desliga o led
}
#pragma vector = INTST2_vect
__interrupt void trata_tx_UART2(void)
{
}


#endif
#endif 

