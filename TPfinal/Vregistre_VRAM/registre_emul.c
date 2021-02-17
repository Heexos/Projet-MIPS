#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "registre_emul.h"
#include "registre_struct.h"

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
  if(hex_adress != 0){
    while((temp_Register != NULL) && (find != 0)) {

      if(hex_adress == temp_Register -> address_value) {
        find = 0;
        temp_Register -> value = value;
      } else
        temp_Register = temp_Register -> suivant;
    }
  }
  else find = 0;

  return find;
}

void inc_pc_4(){

  pc.value += 4;

}

void Register_display() {
  Register* tmp = head_lst_register;
  while (tmp != NULL) {
    printf("%s :\t 0x%X\t",tmp->name, tmp->value);
    tmp = tmp -> suivant;
    if ( (tmp == NULL) || ((tmp -> address_value)%8 == 0) ) printf("\n");
  }
}
