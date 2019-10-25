#ifndef __CTRL_BUTTON_C__
#define __CTRL_BUTTON_C__

#include "CTRL_Button.h"
#include "Hardware.h"
#include "Hooks.h"
#include "ior5f100le.h"
#include "ior5f100le_ext.h"
#include "intrinsics.h"
#include <stdint.h>

#define SW(x)        !( 1 << x)
#define NUM_DE_BOTOES    7




typedef enum{
  SW0 = 0xFE,
  SW1 = 0XFD,
  SW2 = 0XFB,
  SW3 = 0XF7,
  SW4 = 0XEF,
  SW5 = 0XDF,
  SW6 = 0XBF,
  NONE = 0xFF
} BUTTON_STATE_MACHINE;



typedef struct {
  BUTTON_STATE_MACHINE SWX;
  int freq;
} notas;

const notas Notas[NUM_DE_BOTOES] = {
  {SW0, 100},
  {SW1, 500},
  {SW2, 1000},
  {SW3, 1500},
  {SW4, 2000},
  {SW5, 2500},
  {SW6, 3000},
};


struct {
  BUTTON_STATE_MACHINE button_state;
  unsigned int button_pressed : 1; 
  
} ctrl_button_obj;


void CTRL_Button_Init(){
  
}

BUTTON_STATE_MACHINE CTRL_Button_Read(){
  
  int static reads_count;
  BUTTON_STATE_MACHINE read = NONE ;

  
  while(read == (P7 | 128) ){
    
    read = (BUTTON_STATE_MACHINE)(P7 & 127);
    
    if(reads_count++ == 0x4){
      return read;
    }
    
  }
  
  return ctrl_button_obj.button_state;
  
}



void CTRL_Button_Task(){
  int botao;
  ctrl_button_obj.button_state = (BUTTON_STATE_MACHINE)(P7 | 64); //CTRL_Button_Read() ;
  
  
  
  for (botao = 0; botao < NUM_DE_BOTOES; botao++){
    
    if( ctrl_button_obj.button_state == Notas[botao].SWX ){
      ctrl_button_obj.button_pressed = 1;
      HOOK_SET_MUSICAL_NOTE(Notas[botao].freq);
    }
  }
  
  if(ctrl_button_obj.button_pressed == 0) HOOK_TURN_OFF_MUSICAL();
  
  
  ctrl_button_obj.button_pressed = 0;
  
}




#endif