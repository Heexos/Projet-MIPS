//------------------------
//------- PRIVATE --------
//------------------------
typedef struct {
  char nb_field;
  char* opcode;
  char* arg1;
  char* arg2;
  char* arg3;
} Parsed_str;

#define R_VALUE_ERROR 0xF0000000
#define J_VALUE_ERROR 0xF0000000
#define I_VALUE_ERROR 0xF0000000

//_parse
//Permet de parse une ligne assembleur en champ dans
//la structure Parsed_str
//Entrée : (char*) str de la ligne assembleur
//         (Parsed_str*), structure pré-alloué
//Sortie : (Int), Nb de champs remplie dans la struct (Parsed_str)
int _parse(char * instruction_buffer, Parsed_str * parsed_instruct);

//_find_type
//Entrée : (char*) str de l'instruction insensible à la casse
//Sortie : (Instruction*) pointeur vers structure Instruction,
//          NULL si le str de l'instruction n'est pas valide
Instruction* _find_type(char* str_opcode);

//_find_type
//Entrée : (char*) str de l'identifieur de registre insensible à la casse
//Sortie : (Register*) pointeur vers structure Register,
//          NULL si le str du registre n'est pas valide
char _find_register(char* str_register, char* register_addr);

//decode_r
//Entrée : (Parsed_str *),
//(Instruction*) pointeur vers structure Instruction
//Sortie : (uint32_t)
uint32_t _decode_r(Parsed_str *parsed_instruct, Instruction *instruction_type);

//decode_j
//Entrée : (Parsed_str *)
           // (Instruction*)
//Sortie : (uint32_t)
uint32_t _decode_j(Parsed_str *parsed_instruct, Instruction *instruction_type);

//decode_i
//Entrée : (Parsed_str *)
           // (Instruction*)
//Sortie : (uint32_t)
uint32_t _decode_i(Parsed_str *parsed_instruct, Instruction *instruction_type);

//convertit en casse haute un string
char* _strup(char* str);

//convertit un string au format d'un entier signé en entier signé
int _str2int(char* str);
