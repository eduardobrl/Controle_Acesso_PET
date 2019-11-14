#ifndef __PET_ACCESS_C__
#define __PET_ACCESS_C__


/************************************************
 *  INCLUDES
 ***********************************************/
#include <stdint.h>
   
#include "Types.h"
#include "Hardware.h"
#include "Hooks.h"
   
#include "CTRL_PetAccess.h"   
   
#include "ior5f100le.h"
#include "ior5f100le_ext.h"
#include "intrinsics.h"
#include "DRV_UART.h"
   
void ctrl_Pet_Access_Food_Reload(uint8_t * pFood, uint8_t pReload  );
/************************************************
 *  Structs Globais
 ***********************************************/
struct {
  WORD isEnabled;
  WORD nearPet;
  
  
} ctrlPetAccess_obj;

/************************************************
 *  Funções Globais
 ***********************************************/
void CTRL_Pet_Access_Init(){
  
  ctrlPetAccess_obj.isEnabled = TRUE; 
}

void CTRL_Pet_Access_Tasks(){
  
  int pet;
  uint64_t code;
  uint8_t * pTags ;
  static uint8_t index;
  
  pTags = DRV_UART_Get_Tags(DRV_UART_Get_Index());
  
  
  for(pet=0; pet < NUM_OF_PETS; pet++){
    if(Pets_Table[pet].RFID_Code == 1)//pTags[index])
    {
      switch(Pets_Table[pet].State){
        
        case(BLOQUEADO):
#if 0
          LCD_send8(0,CLR_DISPLAY);
          LCD_pos_xy(0,0);
          LCD_write_string(Pets_Table[pet].Cat_Name);
          LCD_write_char(' ');
          LCD_write_string("BLOQUEADO");
          LCD_pos_xy(0,1);
          LCD_write_string("FALTAM: ");
          LCD_write_word(Pets_Table[pet].Time.min);
          LCD_write_char(':');
          LCD_write_word(Pets_Table[pet].Time.sec);
#endif   
          HOOK_ACESSO_BLOQUEADO(&Pets_Table[pet]);
          break;
        
        case(DISPONIVEL):   
          
          HOOK_LIBERAR_ACESSO(&Pets_Table[pet]);
          Pets_Table[pet].State = ESPERANDO_LIBERAR;      
          break;
         
        case(LIBERADO):
          HOOK_ACESSO_LIBERADO(&Pets_Table[pet]);
          DRV_RTC_Reload(&Pets_Table[pet].Time, &Pets_Table[pet].Reload);
          ctrl_Pet_Access_Food_Reload(&Pets_Table[pet].Food_Amount, Pets_Table[pet].Food_Amount);
          Pets_Table[pet].State = BLOQUEADO; 
          break;  
        
         /*Estes estados são tratados dentro da rotina de interrupção*/
        case ESPERANDO_LIBERAR:
        case LIBERANDO:
        default:
          break;
          
      }
    }
  }
  
  index++;
}

/************************************************
 *  Funções Locais
 ***********************************************/

void ctrl_Pet_Access_Food_Reload(uint8_t * pFood, uint8_t pReload  ){
  *pFood = pReload;
}

void CTRL_PetAccess_Time_Event(void) {
  
  WORD pet;
  
  for(pet=0; pet<=NUM_OF_PETS; pet++){
    
    
    switch(Pets_Table[pet].State){
      
      case(BLOQUEADO):
        if( DRV_RTC_Is_Ready(&Pets_Table[pet].Time) == 1){
          Pets_Table[pet].State = DISPONIVEL; 
        }
        else{
          DRV_RTC_Rem_Sec(&Pets_Table[pet].Time, 1u);
        }
        
        break;
       
        case(ESPERANDO_LIBERAR):
          HOOK_INICIA_LIBERACAO();
          Pets_Table[pet].State = LIBERANDO;
          break;
          
        case(LIBERANDO):
          Pets_Table[pet].Food_Amount -= 1;
          
          if(Pets_Table[pet].Food_Amount == 0){
            HOOK_FINALIZA_LIBERACAO();
            Pets_Table[pet].State = LIBERADO;
          }
          break;
          
          
        default:
          break;
          
    }
    
  }

  
  RTCIF = 0;
}


 
#endif