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
#include <stdlib.h>

void ctrl_Pet_Access_Food_Reload(uint8_t * pFood, uint8_t pReload  );
void ctrl_Pet_Access_Novo_Match(uint8_t match);
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
  uint8_t * pTags ;
   uint8_t match;
   
void CTRL_Pet_Access_Tasks(){
  match = 0xFF;
  
  int pet, byte;
  uint64_t code;

  
  
  uint8_t match_num = 0;
  
  pTags = DRV_UART_Get_Tag();
  
  for(pet =0; pet<NUM_OF_PETS;pet++)
  {
    Pets_Table[pet].match = TRUE;
  }
  
  for(byte = (NUMBER_OF_DATA_BYTES - 1u) ; byte >= 0; byte--)
  {
    for(pet =0; pet<NUM_OF_PETS;pet++)
    {

      if(Pets_Table[pet].RFID_Code[byte] == pTags[byte] && Pets_Table[pet].match)
      {
           match = pet;
           match_num++;
      }
      else Pets_Table[pet].match = FALSE;
    }
    
    if(match_num == 1 ){
      break;
    }
    
    match_num = 0;
  }
  
  if(match == 0xFF) return;
  
  ctrl_Pet_Access_Novo_Match(match);
}


/************************************************
 *  Funções Locais
 ***********************************************/

void ctrl_Pet_Access_Novo_Match(uint8_t match){
  
    switch(Pets_Table[match].State){
      
      case(BLOQUEADO): 
        HOOK_ACESSO_BLOQUEADO(&Pets_Table[match]);
        LCD_send8(0,CLR_DISPLAY);
        LCD_pos_xy(0,0);
        LCD_write_string(Pets_Table[match].Cat_Name);
        LCD_write_char(' ');
        LCD_write_string("BLOQUEADO");
        LCD_pos_xy(0,1);
        LCD_write_string("FALTAM: ");
        LCD_write_word(Pets_Table[match].Time.min);
        LCD_write_char(':');
        LCD_write_word(Pets_Table[match].Time.sec);

        break;

      case(DISPONIVEL):   
        
        Pets_Table[match].State = ESPERANDO_LIBERAR;      
        break;

      case(LIBERADO):
        DRV_RTC_Reload(&Pets_Table[match].Time, &Pets_Table[match].Reload);
        Pets_Table[match].State = BLOQUEADO; 
        break;  

      case ESPERANDO_LIBERAR:
        break;
        
      case LIBERANDO:
        LCD_send8(0,CLR_DISPLAY);
        LCD_pos_xy(0,0);
        LCD_write_string(Pets_Table[match].Cat_Name);
        LCD_write_char(' ');
        LCD_write_string("LIBERANDO");
        LCD_pos_xy(0,1);
        LCD_write_string("FALTAM: ");
        LCD_write_word(0);
        LCD_write_char(':');
        LCD_write_word(Pets_Table[match].Food_Amount);
      default:
        break;
            
    }
}


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