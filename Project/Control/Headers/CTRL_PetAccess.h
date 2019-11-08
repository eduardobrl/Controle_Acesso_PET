#ifndef __CTRL_PET_ACCESS_H__
#define __CTRL_PET_ACCESS_H__

#include "DRV_RTC.h"

#define NUM_OF_PETS     3
typedef enum {
  /*Ainda não é permitido liberar a comida*/
  BLOQUEADO,
 /*Esta disponivel mas não foi solicitada*/
  DISPONIVEL,
 /*Foi solicitada e sera iniciada a liberação*/
  ESPERANDO_LIBERAR,
 /*Em processo de liberação*/
  LIBERANDO,
 /*Comida liberada*/
  LIBERADO
} PetAccess_state;  

typedef struct {
  uint64_t              RFID_Code;
  char                  Cat_Name[40];
  RTC_TIME              Time;
  RTC_TIME              Reload;
  uint8_t               Food_Amount;
  uint8_t               Food_Reload;
  PetAccess_state       State;
  
  
} Pet_Access_type;

#if defined(__PET_ACCESS_C__)
  #if defined(I_SUPORT_FAST_DEMONSTRATION)
    Pet_Access_type   Pets_Table[NUM_OF_PETS] = {
      {0u ,"Gato 1",{40u ,1u  ,0u  ,0u  ,0u  ,0u  ,0u},15u , 40u, 1u, BLOQUEADO},
      {1u ,"Gato 2",{0u  ,2u  ,0u  ,0u  ,0u  ,0u  ,0u},20u , 0u, 2u, BLOQUEADO},
      {2u ,"Gato 3",{30u ,0u  ,0u  ,0u  ,0u  ,0u  ,0u},30u , 30u, 0u, BLOQUEADO}
    };
  #else
    Pet_Access_type   Pets_Table[NUM_OF_PETS] = {
      {0u ,"Gato 1",{40u ,1u }, {40u ,1u }, 15u, 15u, BLOQUEADO},
      {1u ,"Gato 2",{0u  ,2u }, {0u  ,2u }, 20u, 20u, BLOQUEADO},
      {2u ,"Gato 3",{30u ,0u }, {30u ,0u }, 30u, 30u, BLOQUEADO}
    };
  #endif //I_SUPORT_FAST_DEMONSTRATION
#endif //__PET_ACCESS_C__



void CTRL_Pet_Access_Tasks();
void CTRL_PetAccess_Time_Event();

    
#endif //__CTRL_PET_ACCESS_H__