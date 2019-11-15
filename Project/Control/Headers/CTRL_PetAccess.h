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
  char                  RFID_Code[10];
  char                  Cat_Name[40];
  RTC_TIME              Time;
  RTC_TIME              Reload;
  uint8_t               Food_Amount;
  uint8_t               Food_Reload;
  uint8_t               match;
  PetAccess_state       State;
  
  
} Pet_Access_type;

#define TAG_AMARELA     {'3','1','0','0','E','2','8','7','D','1'}
#define TAG_ROXA        {'2','E','0','0','C','7','F','D','9','B'}
#define TAG_LARANJA     {'3','1','0','0','B','0','F','A','A','5'}



#if defined(__PET_ACCESS_C__)
  #if defined(I_SUPORT_FAST_DEMONSTRATION)
    Pet_Access_type   Pets_Table[NUM_OF_PETS] = {
      {TAG_AMARELA ,"Gato 1",{40u ,1u  ,0u  ,0u  ,0u  ,0u  ,0u},15u , 40u, 1u, TRUE, BLOQUEADO},
      {TAG_ROXA ,"Gato 2",{0u  ,2u  ,0u  ,0u  ,0u  ,0u  ,0u},20u , 0u, 2u, TRUE, BLOQUEADO},
      {TAG_LARANJA ,"Gato 3",{30u ,0u  ,0u  ,0u  ,0u  ,0u  ,0u},30u , 30u, 0u, TRUE, BLOQUEADO}
    };
  #else
    Pet_Access_type   Pets_Table[NUM_OF_PETS] = {
      {TAG_AMARELA ,"Jade",{40u ,1u }, {40u ,1u }, 5u, 5u, TRUE, BLOQUEADO},
      {TAG_ROXA ,"Nico",{0u  ,2u }, {0u  ,2u }, 5u, 5u, TRUE, BLOQUEADO},
      {TAG_LARANJA ,"Bianca",{30u ,0u }, {30u ,0u }, 8u, 8u, TRUE, BLOQUEADO}
    };
  #endif //I_SUPORT_FAST_DEMONSTRATION
#endif //__PET_ACCESS_C__



void CTRL_Pet_Access_Tasks();
void CTRL_PetAccess_Time_Event();

    
#endif //__CTRL_PET_ACCESS_H__