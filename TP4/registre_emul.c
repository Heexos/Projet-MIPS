#include "registre_emul.h"

int read_register(uint32_t* value, char hex_adress) {

  Register* temp_Register = head_lst_register;

  char find = 1;

  while((temp_Register != NULL) && (find != 0)) {

    if(hex_adress == temp_Register -> address_value) {
      find = 0;
      *value = temp_Register -> value;
    } else
      temp_Register = temp_Register -> suivant;
  }

  return find;
}



int write_register(uint32_t value, char hex_adress) {

  Register* temp_Register = head_lst_register;

  char find = 1;

  while((temp_Register != NULL) && (find != 0)) {

    if(hex_adress == temp_Register -> address_value) {
      find = 0;
      temp_Register -> value = value;
    } else
      temp_Register = temp_Register -> suivant;
  }

  return find;
}

void inc_pc_4(){

  pc.value += 4;

}
