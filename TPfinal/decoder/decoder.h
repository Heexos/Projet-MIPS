#define LEN_INSTRUCT_MAX 70

//decode
//Effectue le decodage de l'assembleur litteral en hexadecimal.
//Entrée : (char*) une Instruction asm litteral
//         (int32_t*) pointeur vers espace memoire contenant l'instruction
//Sortie : (Int), 0 = succes, 1 = echec
char decode(char *instruction_buffer, uint32_t *binary_instruction_code);

//lit et supprime les espaces d'une ligne en entrée
//Sortie : 0 si succes, 1 sinon
int read_asm_line(char* buffer,char *instruction_for_user_ui, int buffer_size, FILE *input);
