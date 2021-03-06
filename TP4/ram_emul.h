#include <stdint.h>
#include <stdlib.h>

typedef struct VRAM_bloc VRAM_bloc;
#define TAILLEMAX 4000000000

//Notre VRAM sera accessible uniquement par bloc de 4 octets.
struct VRAM_bloc {

	unsigned int address;
  uint32_t value;
  VRAM_bloc *suivant;
};

// init_VRAM
// Methode permettant l'initialisation de la VRAM
// (allocation du pointeur VRAM_head)
void init_VRAM();

static VRAM_bloc** VRAM_head;

//VRAM_load
//Permet de lire le contenu d'un bloc VRAM.
//Entrée : (uint32_t) adresse du bloc dans la memoire
//         (int) offset du bloc relatif à l'adresse
//				 (uint32_t*) pointeur vers la variable ou l'on stock le bloc lu
//Sortie : (Int), 0 = succes, 1 = echec
int VRAM_load(uint32_t address, int offset, uint32_t* value);


//VRAM_store
//Permet d'ecrire le contenu d'un bloc VRAM.
//Entrée : (uint32_t) adresse du bloc dans la memoire
//         (int) offset du bloc relatif à l'adresse
//				 (uint32_t) contenu à ecrire dans le bloc
//Sortie : (Int), 0 = succes, 1 = echec
int VRAM_store(uint32_t address, int offset, uint32_t value);
