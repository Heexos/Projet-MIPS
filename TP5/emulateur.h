#include "../TP4/ram_emul.h"
#include "../TP4/registre_emul.h"
#include <stdio.h>
#include <errno.h>

//loader
// Permet le decodage d'un fichier assembleur
// et le remplissage de la VRAM par les instruction décodées
// Entrées : (FILE*) pointeur de fichier dejà ouvert
//           (uint32_t) offset du programme dans la ram
// Sortie : 0 succés, sinon echec
int loader(FILE* inputFile, uint32_t base_offset);

//emulateur_pas_a_pas
// Effectue l'instruction sur les registres et la VRAM
// Entrées : (uint32_t) code binaire de l'instruction à effectué
// Sortie : 0 succés, sinon echec
int emulateur_pas_a_pas(int32_t instruction);

//emulateur
// Effectue l'emulation du programme contenue dans la VRAM à partir
// de l'adresse base_offset
// Entrées : (uint32_t) offset du programme dans la VRAM
// Sortie : 0 succés, sinon echec
int emulateur(uint32_t base_offset);

//ouvrir_fichier
// Ouvre le fichier avec gestion d'erreur
// Entrées : (FILE*) fichier pré alloué
//           (char*) nom du ouvrir_fichier
// Sortie : 0 succes, 1 echec
int ouvrir_fichier(FILE* file, const char* nom);
