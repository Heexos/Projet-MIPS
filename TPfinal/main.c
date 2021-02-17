#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <math.h>

#include "emulateur/emulateur.h"


#define TAILLE 50
int main(int argc, char const *argv[]) {

  Initialisation_RAM();

  char instruction_char[TAILLE];
  char instruction_for_user_ui[TAILLE];
  uint32_t current_instruction;
  if (argc == 1) { // Mode interactif
    printf("Entrez l'instruction ou Q pour quitter : ");
    format_asm_line(instruction_char, instruction_for_user_ui, TAILLE, stdin);

    while(strcmp("Q", instruction_char) != 0) {
      if (decode_instruct(instruction_char, &current_instruction) != 0){
        printf("Invalid entry\n");
      }
      else{
      printf("%x\n", current_instruction);
      emulateur_pas_a_pas(current_instruction);

      afficher_registres();
      afficher_memoire();
      }

      printf("Entree une instruction ou Q pour quitter : ");
      format_asm_line(instruction_char, instruction_for_user_ui, TAILLE, stdin);
    }
  }
  else if (argc == 2) { // Mode non-interactif
    FILE* inputFile;
    if (ouvrir_fichier(&inputFile, argv[1]) == 0) {
      if (loader(inputFile, 0, argv[1]) == 0) {
        emulateur(0,0);
      }
    }
  }
  else if ((argc == 3) && strcmp(argv[2], "-pas") == 0) { // Mode non-interactif pas a pas
    FILE* inputFile;
    if (ouvrir_fichier(&inputFile, argv[1]) == 0) {
      if (loader(inputFile, 0, argv[1]) == 0) {
        emulateur(0,1);
      }
    }
  }
  else { // Erreur
    printf("Erreur : Veuillez utiliser emul-mips en mode interactif ou emul-mips <prog_filename> [-pas] en mode non-interactif [pas a pas]\n");
  }
  Nettoyage_RAM();
  return 0;
}
