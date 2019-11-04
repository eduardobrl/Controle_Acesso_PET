#ifndef __CTRL_BUTTON_C__
#define __CTRL_BUTTON_C__


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


/************************************************
 *  Structs Globais
 ***********************************************/
struct {
  WORD isEnabled;
  
  
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
  
  for(pet=0; pet<=NUM_OF_PETS; pet++){
    
    if(code == Pets_Table[pet].RFID_CODE){
      
    }
    
  }
  

}

/************************************************
 *  Funções Locais
 ***********************************************/
#endif