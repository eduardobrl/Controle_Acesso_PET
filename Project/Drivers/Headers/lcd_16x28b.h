

#ifndef LCD_16x28B_H
#define LCD_16x28B_H



//**************************************************************************
//*As defini��es a seguir s�o utilizadas para acesso aos pinos do display
//**************************************************************************


#ifndef PIN_LCD_EN // verifica se esta defini��o ja existe, se n�o, realiza 
                   // defini��es abaixo
#define PIN_LCD_EN          P5_bit.no4  // pino enable do LCD

#include "ior5f100le.h"
#include "ior5f100le_ext.h"
#include "intrinsics.h"
#include "myRL78.h"
#include "stdint.h"
#include "Types.h"

#define PIN_LCD_EN_DIR	    PM5_bit.no4 // dire��o do pino enable
#define PIN_LCD_RS          P5_bit.no5  // pino rs do LCD
#define PIN_LCD_RS_DIR      PM5_bit.no5 // dire��o do pino rs
#define PORT_LCD_DATA8      P7   
#define PORT_LCD_DATA4      P7       
#define PORT_LCD_DATA8_DIR  PM7
#endif            // finaliza defini��es

// se pino RS = 1 dado se RS =0 comando
#define PIN_LCD_RS_1      1  //Display recebe dado
#define PIN_LCD_RS_0      0  //Display recebe comando

#define CPU_CLOCK         32000 // define valor do clock

//**************************************************************************
//* Defini��es de comandos do Display
//**************************************************************************

// Instru��o: Clear Display do datasheet
#define CLR_DISPLAY         0x01  // Limpa Display

// Instru��o: Cursor at home do datasheet
#define CURSOR_HOME         0x02  // Cursor posi��o: linha 0 coluna 0

// Instru��o: Entry Mode Set do datasheet
#define MODE_SET           0x06  // Configura cursor para escrever para direita

// Instru��o: Display ON/OFF Control do datasheet
#define APAGA_DISPLAY       0x08  // Apaga Display
#define ACENDE_DISPLAY      0x0C  // Acende Display
#define PISCA_CURSOR_ON     0x0D  // Pisca Display
#define PISCA_CURSOR_OFF    0x0C  // Pisca Display
#define CURSOR_ON           0x0E  // Liga Cursor
#define CURSOR_OFF          0x0C  // Liga Cursor

// Instru��o: Cursor Display Shift do datasheet
#define SHIFT_L_CURSOR      0x10  // desloca cursor p/ a esquerda (decrementa x)
#define SHIFT_R_CURSOR      0x14  // desloca cursor p/ a diretia (incrementa x)
#define SHIFT_L_CHAR        0x18  // desloca caraceteres p/ a esquerda
#define SHIFT_R_CHAR        0x1C  // desloca caracteres p/ a direita 

  typedef union{
    char value;
    
    struct { 
      char low : 4;
      char high : 4;
    };
    
    uint8_t number;
    
  } DATA_TYPE;

  typedef union{
    
    uint8_t number;
    
    struct { 
      uint8_t low  : 4;
      uint8_t high : 4;
    };

  } uint8t_nibble;

  void LCD_delay_ms(unsigned char time);
  void LCD_send8(char addr, char data );
  void LCD_send4(char addr, char data );
  void LCD_init_4_bits(void);
  void LCD_pos_xy(char x, char y);
  void LCD_write_char(char data);
  void LCD_write_string (char *ptr);
  void LCD_write_word(uint16_t number);
  char lcd_Number_2_ASCII(uint8_t number );
  uint8_t lcd_ASCII_2_Number(char nb1, char nb2);
  
#define ASCII_TABLE_ELEMENTS    16

typedef struct{ 
  
    WORD dec_number;
    char asc_char; 
  
} ASCII_TABLE;  
  




#endif