#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "ram_emul.h"

static VRAM_bloc** VRAM_head;

void init_VRAM(){

  VRAM_head = malloc(sizeof(void));
}

void free_VRAM() {
  if (*VRAM_head != NULL) recursif_free_vram(*VRAM_head);
  free(VRAM_head);
}

void recursif_free_vram(VRAM_bloc *VRAM_bloc){

  if(VRAM_bloc-> suivant != NULL) recursif_free_vram(VRAM_bloc->suivant);
  free(VRAM_bloc);
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

      if(temp_bloc->address > adr){
        new_bloc -> address = adr;
        new_bloc -> value = value;
        new_bloc -> suivant = temp_bloc;

        *VRAM_head = new_bloc;
        find = 0;
      }


      while ((temp_bloc != NULL) && (find != 0)) {

        if (temp_bloc -> address == adr) {
          //Modifier le bloc existant
          temp_bloc -> value = value;
          find = 0;

        }

        else if ((temp_bloc -> suivant != NULL) && (temp_bloc -> suivant -> address > adr)) {
          //Créer un nouveau bloc et l'insérer dans la liste chainée
          new_bloc->suivant = temp_bloc -> suivant;
          new_bloc->address = adr;
          new_bloc->value = value;
          temp_bloc -> suivant = new_bloc;
          find = 0;

        }
        else if (temp_bloc -> suivant == NULL) {
          new_bloc->suivant = NULL;
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
      find = 0;
    }
  }

  // printf("1 adress : %d, value : %d\n", (*VRAM_head) -> address, (*VRAM_head) -> value);
  // printf("1 adress : %p\n", *VRAM_head);
  return find;
}


void VRAM_display(uint32_t adr_pc) {
  int adr_to_read;
  uint32_t value;

  //Affichage autour du PC
  for(int i = -2; i < 3; i++) {
    if (i != 0) {
      printf("\t");
    } else {
      printf("PC ->\t");
    }
    adr_to_read = adr_pc - adr_pc%4 + 4*i;
    if (adr_to_read >= 0) {
      if (VRAM_load(adr_pc, 4*i, &value) == 0) {
        printf("@0x%X : 0x%X", adr_to_read, value);
      } else {
        printf("@0x%X : 0x00", adr_to_read);
      }
    }
    printf("\n");
  }

  int i = 0;
  VRAM_bloc* tmp = *VRAM_head;

  printf("\nMemoire brute :\n");

  while (tmp != NULL) {
    printf("@0x%X : 0x%X", tmp -> address, tmp -> value);
    if (++i%4 == 0) {
      printf("\n");
    } else {
      printf("\t");
    }
    tmp = tmp -> suivant;
  }
  printf("\n");
}
