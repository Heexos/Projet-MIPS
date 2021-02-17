#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>

#include "emulateur.h"

#include "../Vregistre_VRAM/ram_emul.h"
#include "../Vregistre_VRAM/registre_emul.h"
#include "../decoder/decoder.h"
#include "../register_define.h"
#include "../opcode_define.h"

int loader(FILE* inputFile, uint32_t base_offset, const char* nom_fichier){

  //On se re aligne avec les blocs de ram
  base_offset -= base_offset%4;
  uint32_t program_counter = base_offset;

  //lecture
  char instruction_buffer[LEN_INSTRUCT_MAX];
  char instruction_for_user_ui[LEN_INSTRUCT_MAX];

  while(! feof(inputFile)){
    //get asm instruction one line by one line
    if(read_asm_line(instruction_buffer, instruction_for_user_ui, LEN_INSTRUCT_MAX, inputFile)){
      printf("Read error : %d of file %s\n", errno, nom_fichier);
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
      else{
        printf("Invalid instuction, exiting\n");
        return 1;
      }
    }
  }
  printf("\n");

  return 0;
}


int emulateur(uint32_t base_offset, char pas_a_pas){

  uint32_t pc_local = base_offset;
  pc_local -= base_offset % 4;

  int succes_VRAM_load = 0;

  if(write_register(pc_local, REGISTER_PC_ADDR) != 0){
    printf("Erreur interne\n");
    return 1;
  }

  uint32_t current_instruction;

  succes_VRAM_load = VRAM_load(pc_local, 0, &current_instruction);
  
  if(succes_VRAM_load != 0)
    printf("Aucune instruction présente à base_offset\n");

  while(succes_VRAM_load == 0){

    //incremente le registre program_counter de 4
    inc_pc_4();

    printf("Execution de l'instruction : 0x%X\n", current_instruction);

    if(emulateur_pas_a_pas(current_instruction) != 0){

      printf("Echec, Arret du programme\n");
      return 1;
    }

    if(pas_a_pas){
      //affichage
      afficher_registres();
      afficher_memoire();
      printf("Appuyez sur Entree pour continuer.\n");
      while(getchar() != '\n');
      getchar();
    }

    if(read_register(&pc_local, REGISTER_PC_ADDR) != 0){
      printf("Erreur interne\n");
      return 1;
    }

    succes_VRAM_load = VRAM_load(pc_local, 0, &current_instruction);
  }

  if(pas_a_pas == 0){
    afficher_registres();
    afficher_memoire();
  }
  return 0;
}

// 1 Echec
// 0 succes
int ouvrir_fichier(FILE** file, const char* nom) {
  *file = fopen(nom, "r" );
  if ( *file == NULL ) {
      printf( "Ouverture du ficher %s impossible\n", nom);
      return 1;
  } else return 0;
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

    if(fction == ADD){
      int32_t temp1; int32_t temp2;
      read_register((uint32_t*)&temp1, rs);
      read_register((uint32_t*)&temp2, rt);

      write_register(temp1+temp2, rd);
    }
    else if(fction == SUB){
      int32_t temp1; int32_t temp2;
      read_register((uint32_t*)&temp1, rs);
      read_register((uint32_t*)&temp2, rt);

      write_register(temp1-temp2, rd);
    }
    else if(fction == MULT){
      int32_t temp1; int32_t temp2;
      read_register((uint32_t*)&temp1, rs);
      read_register((uint32_t*)&temp2, rt);

      int64_t temp_mult = (int64_t)temp1 * (int64_t)temp2;

      uint32_t reg_hi = (temp_mult& 0xffffffff00000000)>>32;
      uint32_t reg_lo = temp_mult & 0xffffffff;
      write_register(reg_hi, REGISTER_HI_ADDR);
      write_register(reg_lo, REGISTER_LO_ADDR);
    }
    else if(fction == DIV) {

      int32_t temp1; int32_t temp2;
      read_register((uint32_t*)&temp1, rs);
      read_register((uint32_t*)&temp2, rt);

      int32_t reg_hi = temp1 % temp2;
      int32_t reg_lo = temp1 / temp2;

      write_register(reg_hi, REGISTER_HI_ADDR);
      write_register(reg_lo, REGISTER_LO_ADDR);
    }
    else if(fction == AND){
      uint32_t temp1; uint32_t temp2;
      read_register((uint32_t*)&temp1, rs);
      read_register((uint32_t*)&temp2, rt);

      write_register(temp1&temp2, rd);
    }
    else if(fction == OR){
      uint32_t temp1; uint32_t temp2;
      read_register((uint32_t*)&temp1, rs);
      read_register((uint32_t*)&temp2, rt);

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
      r_shifted |= (temp1<<(32-temp2));

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
      read_register((uint32_t*)&temp, rs);

      temp += int16_to_int32(immediat_value);

      write_register(temp, rt);
    }
    else if (opcode == LW ) {
      uint32_t temp1; uint32_t temp2;

      read_register(&temp1, rs);

      VRAM_load(temp1, immediat_value, &temp2);
      write_register(temp2, rt);
    }
    else if (opcode == SW ) {
      uint32_t temp1; uint32_t temp2;
      read_register(&temp1, rs);
      read_register(&temp2, rt);
      //printf("%d\n", temp2);
      VRAM_store(temp1, immediat_value, temp2);

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
        temp3 += int16_to_int32(immediat_value)<<2;
        write_register(temp3, REGISTER_PC_ADDR);
      }
    }
    else if (opcode == BGTZ ) {
      int32_t temp1;
      read_register((uint32_t*)&temp1, rs);
      if (temp1 > 0) {
        uint32_t temp2;
        read_register(&temp2, REGISTER_PC_ADDR);
        temp2 += int16_to_int32(immediat_value)<<2;
        write_register(temp2, REGISTER_PC_ADDR);
      }
    }
    else if (opcode == BLEZ ) {
      int32_t temp1;
      read_register((uint32_t*)&temp1, rs);
      if (temp1 <= 0) {
        uint32_t temp2;
        read_register(&temp2, REGISTER_PC_ADDR);
        temp2 += int16_to_int32(immediat_value)<<2;
        write_register(temp2, REGISTER_PC_ADDR);
      }
    }
    else if (opcode == J){

      immediat_value = instruction & 0x3FFFFF;
      immediat_value = immediat_value << 2;

      write_register(immediat_value, REGISTER_PC_ADDR);

    }
    else if(opcode == JAL){

      uint32_t temp2;
      read_register(&temp2, REGISTER_PC_ADDR);
      write_register(temp2, REGISTER_RA_ADDR);

      immediat_value = instruction & 0x3FFFFF;
      immediat_value = immediat_value << 2;
      write_register(immediat_value, REGISTER_PC_ADDR);
    }
  }

  return 0;
}

int32_t int16_to_int32(uint32_t int16_var){

  int16_var &= 0xFFFF;

  int32_t return_value = 0;

  if((int16_var&0x8000) != 0){

    int16_var &= 0x7fff;

    return_value = int16_var-32768;
  }
  else return_value = int16_var;

  return return_value;
}

void afficher_memoire(){

  uint32_t pc;
  read_register(&pc, REGISTER_PC_ADDR);
  VRAM_display(pc);
}

void afficher_registres(){

  Register_display();
}

void Initialisation_RAM(){

  init_VRAM();
}

void Nettoyage_RAM(){

  free_VRAM();
}

char decode_instruct(char *instruction_buffer, uint32_t *binary_instruction_code){

  return decode(instruction_buffer, binary_instruction_code);

}

int format_asm_line(char* buffer,char *instruction_for_user_ui, int buffer_size, FILE *input){

  return read_asm_line(buffer, instruction_for_user_ui, buffer_size, input);
}




















//
