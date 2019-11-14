/**************************************************
* Centro Universitario FEI
* Disciplina EL9630 / NEA630
* Mini Projeto Dirigido 02 – Timer / Interrupções – Agosto / 2017 rev03
* Silvana Gasparotto de Souza
**************************************************/
#include "Hardware.h"



#if !defined(I_SUPPORT_DRV_UART)

#include "ior5f100le.h"
#include "ior5f100le_ext.h"
#include "intrinsics.h"
#include "myRL78.h"


// Configura watchdog = desligado
#pragma location = "OPTBYTE"
__root __far const char opbyte0 = WDT_OFF;
// Configura detector de baixa tensão = desligado
#pragma location = "OPTBYTE"
__root __far const char opbyte1 = LVD_OFF;
// oscilador 32MHz flash high speed
#pragma location = "OPTBYTE"
__root __far const char opbyte2 = FLASH_HS | CLK_32MHZ; 
// debug ativado, com apagamento em caso de falha de autenticação
#pragma location = "OPTBYTE"
__root __far const char opbyte3 = DEBUG_ON_ERASE;
/* Configura security ID */
#pragma location = "SECUID"
__root __far const char senha[10] = {0,0,0,0,0,0,0,0,0,0};
#define __9600BPS 51 << 9
#define LED P7_bit.no7
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
void MCU_init(void)
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
 __enable_interrupt(); // habilita as interrupções do RL78
}
void main(void)
{
 MCU_init();
 while (1);
} 


#else

#include "ior5f100le.h"
#include "ior5f100le_ext.h"
#include "intrinsics.h"
#include "myRL78.h"
#include "CTRL_Button.h"

#include "DRV_UART.h"
#include "DRV_RTC.h"
#include "lcd_16x28b.h"
#include "CTRL_PetAccess.h"

#include "Hardware.h"

// Configura watchdog = desligado
#pragma location = "OPTBYTE"
__root __far const char opbyte0 = WDT_OFF;
// Configura detector de baixa tensão = desligado
#pragma location = "OPTBYTE"
__root __far const char opbyte1 = LVD_OFF;
// oscilador 32MHz flash high speed
#pragma location = "OPTBYTE"
__root __far const char opbyte2 = FLASH_HS | CLK_32MHZ; 
// debug ativado, com apagamento em caso de falha de autenticação
#pragma location = "OPTBYTE"
__root __far const char opbyte3 = DEBUG_ON_ERASE;
/* Configura security ID */
#pragma location = "SECUID"
__root __far const char senha[10] = {0,0,0,0,0,0,0,0,0,0};

void main( void )
{
  //PU7 = P7_PULL;
  //PM7 = P7_MODE;
  //P7 = P7_PORT;
  
  //PM1 = P1_MODE;
  //P1 = P1_PORT;
  
  //CTRL_Button_Init();
  DRV_UART_Init();
  DRV_RTC_Init();
  //LCD_init_4_bits();
  __enable_interrupt(); // habilita as interrupções do RL78
  while (1)
  {  
    //CTRL_Pet_Access_Tasks();
    DRV_UART_Taks();
  }
}
#endif