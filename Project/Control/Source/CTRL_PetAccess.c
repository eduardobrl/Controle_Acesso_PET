#ifndef __CTRL_BUTTON_C__
#define __CTRL_BUTTON_C__

#include "Hardware.h"
#include "Hooks.h"
#include "ior5f100le.h"
#include "ior5f100le_ext.h"
#include "intrinsics.h"
#include <stdint.h>

typedef enum {
  BLOQUEADO,
  DISPONIVEL,
  LIBERADO
} PetAccess_state;  


typedef struct {
  uint64_t              RFID_CODE;
  char                  CAT_NAME[40];
  uint8_t               SECS;
  uint8_t               MINS;
  PetAccess_state       STATE;
} Pet_Access_type;

#define NUM_OF_PETS     3

Pet_Access_type   Pets_Table[NUM_OF_PETS] = {
  {0,"Gato 1", 50,1, BLOQUEADO},
  {0,"Gato 2", 30,1, BLOQUEADO},
  {0,"Gato 3", 30,0, BLOQUEADO}
};

void CTRL_Pet_Access_Init(){
  
  

}

void CTRL_Pet_Access_Tasks(){
  
  int pet;
  uint64_t code;
  
  for(pet=0; pet<=NUM_OF_PETS; pet++){
    
    if(code == Pets_Table[pet].RFID_CODE){
      
    }
    
  }
  

}

#endif