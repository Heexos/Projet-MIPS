#include "../TP4/ram_emul.h"
#include "../TP4/registre_emul.h"
#include <stdio.h>
#include <stdint.h>

//afficher_registres
// Affiche les registres, 8 par lignes
// Pas d'IO
void afficher_registres();

//afficher_memoire
// Affiche la memoire brute et celle autour du PC
// Entrée : (unint32_t) adresse du PC
void afficher_memoire(uint32_t adr_pc);
