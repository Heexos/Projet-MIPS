#include <stdio.h>
#include "ram_emul.h"

void init_VRAM(){

  VRAM_head = malloc(sizeof(void));
}

int VRAM_load(uint32_t address, int offset, uint32_t* value){

  VRAM_bloc* temp_VRAM_bloc = *VRAM_head;

  unsigned int adr = address + offset;
  adr -= adr%4; //On se recentre sur le bloc

  char find = 1;

  while((temp_VRAM_bloc != NULL) && (find != 0)) {
    //printf("1 adress : %d, value : %d\n", temp_VRAM_bloc -> address, temp_VRAM_bloc -> value);
    if(adr == (temp_VRAM_bloc -> address)) {
      find = 0;
      *value = temp_VRAM_bloc -> value;
    }
    else {
      temp_VRAM_bloc = temp_VRAM_bloc -> suivant;
    }
  }

  if(find == 1){
    *value = 0;
  }
  return find;
}




int VRAM_store(uint32_t address, int offset, uint32_t value) {

  VRAM_bloc* temp_bloc = (*VRAM_head);
  VRAM_bloc* new_bloc = malloc(sizeof(VRAM_bloc));
  unsigned int adr = address + offset;
  adr -= adr%4;
  char find = 1;

  if (adr > TAILLEMAX) {
    printf("Erreur : memory overflow\n");
  }
  else {

    if (temp_bloc != NULL) {
      while ((temp_bloc != NULL) && (find != 0)) {

        if (temp_bloc -> address == adr) {
          //Modifier le bloc existant
          temp_bloc -> value = value;
          find = 0;

        }
        else if ((temp_bloc -> suivant != NULL) && (temp_bloc -> suivant -> address < adr)) {
          //Créer un nouveau bloc et l'insérer dans la liste chainée
          new_bloc->suivant = temp_bloc -> suivant;
          new_bloc->address = adr;
          new_bloc->value = value;
          temp_bloc -> suivant = new_bloc;
          find = 0;

        }
        else {
          //Parcours de la liste
          temp_bloc = temp_bloc -> suivant;
        }
      }
    }
    else {
      new_bloc->suivant = NULL;
      new_bloc->address = adr;
      new_bloc->value = value;
      *VRAM_head = new_bloc;
    }
  }

  // printf("1 adress : %d, value : %d\n", (*VRAM_head) -> address, (*VRAM_head) -> value);
  // printf("1 adress : %p\n", *VRAM_head);
  return find;
}
