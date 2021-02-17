#include "emulateur.h"

int loader(FILE* inputFile, uint32_t base_offset){

  //On se re aligne avec les blocs de ram
  base_offset -= base_offset%4;
  uint32_t program_counter = base_offset;

  //lecture
  char instruction_buffer[LEN_INSTRUCT_MAX];
  char instruction_for_user_ui[LEN_INSTRUCT_MAX];

  while(! feof(inputFile)){
    //get asm instruction one line by one line
    if(read_asm_line(instruction_buffer, instruction_for_user_ui, LEN_INSTRUCT_MAX, inputFile)){
      printf("Read error : %d of file %s\n", errno, argv[1]);
      return 1;
    }
    else if(strlen(instruction_buffer) > 1){
      uint32_t binary_code;
      printf("\n");
      printf("Computing : '%s'\n", instruction_for_user_ui);
      if(decode(instruction_buffer, &binary_code) == 0){
        printf("hex value : %x\n", binary_code);

        if(VRAM_store(program_counter, 0, binary_code) == 0){
          program_counter += 4;
        }
        else{

          printf("echec du dump du programme dans la ram\nArret\n");
          return 1;
        }
      }
    }
  }

  return 0;
}


int emulateur(uint32_t base_offset){

  base_offset -= base_offset % 4;

  if(write_register(base_offset, REGISTER_PC_ADDR) != 0){
    printf("Erreur interne\n");
    return 1;
  }


  uint32_t current_instruction;

  if(VRAM_load(base_offset, 0, &current_instruction) != 0)
    printf("Aucune instruction présente à base_offset\n");

  while(current_instruction != 0){

    //incremente le registre program_counter de 4
    inc_pc_4();

    if(emulateur_pas_a_pas(current_instruction) != 0){

      printf("Echec, Arret du programme\n");
      return 1;
    }

    //affichage

    VRAM_load(base_offset, 0, &current_instruction)
  }

  return 0;
}

// 1 Echec
// 0 succes
int ouvrir_fichier(FILE* file, char* nom) {
  FILE* inputFile;

  file = fopen(argv[1], "r" );
  if ( inputFile == NULL ) {
      printf( "Ouverture du ficher %s impossible\n", argv[1]);
      return 0;
  } else return 1;
}

int emulateur_pas_a_pas(int32_t instruction) {

  char opcode = (instruction>>26)&0x3F;

  if(opcode == 0){
    //instruction de type R
    char rs = (instruction>>21)&0x1F;
    char rt = (instruction>>16)&0x1F;
    char rd = (instruction>>11)&0x1F;
    char sa = (instruction>>6)&0x1F;
    char fction = instruction&0x3F;

    if(fction == NOP){
      ;
    }
    else if(fction == ADD){
      int32_t temp1; int32_t temp2;
      read_register(&temp1, rs);
      read_register(&temp2, rt);

      write_register(temp1+temp2, rd);
    }
    else if(fction == SUB){
      int32_t temp1; int32_t temp2;
      read_register(&temp1, rs);
      read_register(&temp2, rt);

      write_register(temp1-temp2, rd);
    }
    else if(fction == MULT){
      int32_t temp1; int32_t temp2;
      read_register(&temp1, rs);
      read_register(&temp2, rt);

      int temp_mult = temp1 * temp2;

      uint32_t reg_hi = temp_mult & 0xffffffff00000000;
      uint32_t reg_lo = temp_mult & 0xffffffff;
      write_register(reg_hi, REGISTER_HI_ADDR);
      write_register(reg_lo, REGISTER_LO_ADDR);
    }
    else if(fction == DIV){

      int32_t temp1; int32_t temp2;
      read_register(&temp1, rs);
      read_register(&temp2, rt);

      int32_t reg_hi = temp1 % temp2;
      int32_t reg_lo = temp1 / temp2;

      write_register(reg_hi, REGISTER_HI_ADDR);
      write_register(reg_lo, REGISTER_LO_ADDR);
    }
    else if(fction == AND){
      uint32_t temp1; uint32_t temp2;
      read_register(&temp1, rs);
      read_register(&temp2, rt);

      write_register(temp1&temp2, rd);
    }
    else if(fction == OR){
      uint32_t temp1; uint32_t temp2;
      read_register(&temp1, rs);
      read_register(&temp2, rt);

      write_register(temp1|temp2, rd);
    }
    else if(fction == XOR){
      uint32_t temp1; uint32_t temp2;
      read_register(&temp1, rs);
      read_register(&temp2, rt);

      write_register(temp1^temp2, rd);
    }
    else if(fction == SLL){
      uint32_t temp1; uint32_t temp2;
      read_register(&temp1, rt);
      read_register(&temp2, sa);

      write_register(temp1<<temp2, rd);
    }
    else if(fction == SRL){
      uint32_t temp1; uint32_t temp2;
      read_register(&temp1, rt);
      read_register(&temp2, sa);

      uint32_t r_shifted = temp1>>temp2;
      if(rs == 1){
      r_shifted |= temp1<<(32-sa);

      }
      write_register(r_shifted, rd);
    }
    else if(fction == SLT){
      uint32_t temp1; uint32_t temp2;
      read_register(&temp1, rs);
      read_register(&temp2, rt);

      write_register((temp1<temp2)?1:0, rd);
    }
    else if(fction == MFHI){
      uint32_t temp;
      read_register(&temp, REGISTER_HI_ADDR);

      write_register(temp, rd);
    }
    else if(fction == MFLO){
      uint32_t temp;
      read_register(&temp, REGISTER_LO_ADDR);

      write_register(temp, rd);
    }
    else if(fction == JR){
      uint32_t temp;
      read_register(&temp, rs);

      write_register(temp, REGISTER_PC_ADDR);
    }
  }
  else{
    char rs = (instruction>>21)&0x1F;
    char rt = (instruction>>16)&0x1F;
    uint32_t immediat_value = instruction&0xFFFF;

    if(opcode == ADDI) {
      int32_t temp;
      read_register(&temp, rs);

      temp += int16_to_int32(immediat_value);

      write_register(temp, rt);
    }
    else if (opcode == LW ) {
      unint32_t temp1; uint32_t temp2;

      read_register(&temp1, rs);

      VRAM_load(&temp1, immediat_value, &temp2);
      write_register(temp2, rt);
    }
    else if (opcode == SW ) {
      unint32_t temp;

      read_register(&temp1, rs);
      read_register(&temp2, rt);
      VRAM_store(&temp1, immediat_value, temp2);

    }
    else if (opcode == LUI ) {
      uint32_t temp;
      temp = immediat_value << 16;
      write_register(temp, rt);
    }
    else if (opcode == BEQ ) {
      uint32_t temp1; uint32_t temp2;
      read_register(&temp1, rs);
      read_register(&temp2, rt);
      if (temp1 == temp2) {
        uint32_t temp3;
        read_register(&temp3, REGISTER_PC_ADDR);
        temp3 += (immediat_value<<2);
        write_register(temp3, REGISTER_PC_ADDR);
      }
    }
    else if (opcode == BNE ) {
      uint32_t temp1; uint32_t temp2;
      read_register(&temp1, rs);
      read_register(&temp2, rt);
      if (temp1 != temp2) {
        uint32_t temp3;
        read_register(&temp3, REGISTER_PC_ADDR);
        temp3 += (int16_to_int32(immediat_value)<<2);
        write_register(temp3, REGISTER_PC_ADDR);
      }
    }
    else if (opcode == BGTZ ) {
      uint32_t temp1;
      read_register(&temp1, rs);
      if (temp1 > 0) {
        uint32_t temp2;
        read_register(&temp2, REGISTER_PC_ADDR);
        temp2 += int16_to_int32(immediat_value)<<2);
        write_register(temp2, REGISTER_PC_ADDR);
      }
    }
    else if (opcode == BLEZ ) {
      uint32_t temp1;
      read_register(&temp1, rs);
      if (temp1 <= 0) {
        uint32_t temp2;
        read_register(&temp2, REGISTER_PC_ADDR);
        temp2 += int16_to_int32(immediat_value)<<2);
        write_register(temp2, REGISTER_PC_ADDR);
      }
    }
  }


  return 0;
}

int32_t int16_to_int32(uint32_t int16_var){

  int16_var &= 0xFFFF;

  int32_t return_value = 0;

  if(int16_var&0x8000 != 0){

    int16_var &= 0x7fff;

    return_value = int16_var-32768;
  }
  else return_value = int16_var;

  return return_value;
}






















//
