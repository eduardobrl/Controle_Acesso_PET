#ifndef __CTRL_PET_ACCESS_H__
#define __CTRL_PET_ACCESS_H__

#define NUM_OF_PETS     3

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

Pet_Access_type   Pets_Table[NUM_OF_PETS] = {
  {0,"Gato 1", 50,1, BLOQUEADO},
  {0,"Gato 2", 30,1, BLOQUEADO},
  {0,"Gato 3", 30,0, BLOQUEADO}
};



#endif