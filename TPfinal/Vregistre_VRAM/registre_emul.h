typedef struct Register Register;

struct Register {

	char* name;
	char address_value;
  uint32_t value;
  Register *suivant;
};

//------------------------
//------ FUNCTIONS -------
//------------------------

//read_register
//Permet de lire le contenu d'un registre.
//Entrée : (int32_t*) pointeur vers espace
//         memoire qui contiendra la valeur du registre
//         (char) l'addresse du registre
//Sortie : (Int), 0 = succes, 1 = echec
int read_register(uint32_t* value, char hex_address);

//write_register
//Permet de lire le contenu d'un registre.
//Entrée : (int32_t) valeur que l'on veut mettre dans le registre
//         (char) l'addresse du registre
//Sortie : (Int), 0 = succes, 1 = echec
int write_register(uint32_t value, char hex_address);

//incremente le registre du program_counter de 4
void inc_pc_4();

void Register_display();






//
