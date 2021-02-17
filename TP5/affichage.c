#include "affichage.h"

void afficherRegistres() {
  Register* tmp = head_lst_register;
  while (tmp != NULL) {
    printf("%d\t", tmp -> value);
    tmp = tmp -> suivant;
    if ( (tmp == NULL) || ((tmp -> address_value)%8 == 0) ) printf("\n");
  }
}

void afficherMemoire(uint32_t adr_pc) {
  int adr_to_read;
  uint32_t value;

  //Affichage autour du PC


  for(int i = -2; i < 3; i++) {
    if (i != 0) {
      printf("\t\t\t");
    } else {
      printf("PC -> ");
    }

    adr_to_read = adr_pc - adr_pc%4 + 4*i;
    if (adr_to_read >= 0) {
      if (VRAM_load(adr_pc, 4*i, &value)) {
        printf("@0x%X : 0x%X\n", adr_to_read, value);
      } else {
        printf("@0x%X : 0x00\n", value);
      }
    }
  }

  // Affichage brut memoire

  int i = 0;
  VRAM_bloc* tmp = *VRAM_head;

  printf("\nMemoire brute :\n");

  while (tmp != NULL) {
    printf("@0x%X : @0x%X", tmp -> address, tmp -> value);
    if (++i%4 == 0) {
      printf("\n");
    } else {
      printf("\t");
    }
    tmp = tmp -> suivant;
  }


}
