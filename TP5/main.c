//#include "affichage.h"
#include "emulateur.h"
#include <string.h>

#define TAILLE 50
int main(int argc, char const *argv[]) {
  char instruction_char[TAILLE];
  uint32_t current_instruction;
  if (argc == 1) { // Mode interactif
    fgets(instruction_char, TAILLE, stdin);
    while(strcmp("EXIT", instruction_char) == 0) {
      inc_pc_4();
      if (emulateur_pas_a_pas(current_instruction) != 0) {
        printf("Erreur");
        return 1;
      }
      VRAM_load(0, pc.address_value, &current_instruction);
      afficher_registres();
      afficher_memoire(pc.address_value);
      printf("Appuyez sur Entree pour continuer.\n");
    }

  } else if (argc == 2) { // Mode non-interactif
    FILE* inputFile;
    if (!ouvrir_fichier(inputFile, argv[1])) {
      if (!loader(inputFile, 0)) {
        emulateur(0);
        afficher_registres();
        afficher_memoire(pc.address_value);
      }
    }


  } else if ((argc == 3) && strcmp(argv[2], "-pas") == 0) { // Mode non-interactif pas a pas
    FILE* inputFile;
    uint32_t current_instruction = 0;
    if (!ouvrir_fichier(inputFile, argv[1])) {
        if (!loader(inputFile, 0)) {
          while(current_instruction != 0) {
            inc_pc_4();
            if (emulateur_pas_a_pas(current_instruction) != 0) {
              printf("Erreur");
              return 1;
            }
            VRAM_load(0, pc.address_value, &current_instruction);
            afficher_registres();
            afficher_memoire(pc.address_value);
            printf("Appuyez sur Entree pour continuer.\n");
            while(getchar() != '\n');
            getchar();
          }
      }
    }


  } else { // Erreur
    printf("Erreur : Veuillez utiliser emul-mips en mode interactif ou emul-mips <prog_filename> [-pas] en mode non-interactif\n");
  }
  return 0;
}
