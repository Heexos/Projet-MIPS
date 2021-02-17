#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <math.h>

#include "decoder.h"
#include "register_decoder_struct.h"
#include "opcode_decoder_struct.h"
#include "decoder_private.h"



char decode(char *instruction_buffer, uint32_t *binary_instruction_code){

  //Reading file
  Parsed_str *parsed_instruct = malloc(sizeof(Parsed_str));
  parsed_instruct->nb_field = 0;
  parsed_instruct->opcode = NULL;
  parsed_instruct->arg1 = NULL;
  parsed_instruct->arg2 = NULL;
  parsed_instruct->arg3 = NULL;

  char return_value = 0;

      //parse current asm instruction
  if(_parse(instruction_buffer, parsed_instruct) != 0){
    //if one or more fields were parsed
    //then extract the instuction type
    Instruction *current_instruction = _find_type(parsed_instruct->opcode);
    if(current_instruction == NULL){
      printf("Unknown instruction : %s\n", parsed_instruct->opcode);
      return_value = 1;
    }
    else{
      //Instruction is known, data can be extracted and prepared
      switch (current_instruction->type) {
        case 'R':
            *binary_instruction_code = _decode_r(parsed_instruct, current_instruction);
            if(*binary_instruction_code == R_VALUE_ERROR){
              return_value = 1;//erreur
            }
          break;
        case 'I':
            *binary_instruction_code = _decode_i(parsed_instruct, current_instruction);
            if(*binary_instruction_code == I_VALUE_ERROR){
              return_value = 1;;//erreur
            }
          break;
        case 'J':
            *binary_instruction_code = _decode_j(parsed_instruct, current_instruction);
            if(*binary_instruction_code == J_VALUE_ERROR){
              return_value = 1;;//erreur
            }
          break;
        default:
          printf("Internal error\n");
      }
    }
  }
  else
    return_value = 1;


  if(parsed_instruct->opcode != NULL) free(parsed_instruct->opcode);
  if(parsed_instruct->arg1 != NULL) free(parsed_instruct->arg1);
  if(parsed_instruct->arg2 != NULL) free(parsed_instruct->arg2);
  if(parsed_instruct->arg3 != NULL) free(parsed_instruct->arg3);

  if (parsed_instruct != NULL) free(parsed_instruct);
  return return_value;
}

int read_asm_line(char* buffer, char *instruction_for_user_ui, int buffer_size, FILE* input){

  char c = fgetc(input);
  int i = 0;
  char comment = 0;

  int j = 0;

  while(c != '\n' && c != EOF){
    if(i < buffer_size-1 && comment == 0 && c != '\r'){
      if(c == '#') comment = 1;
      else{
        if(c != ' '){
          buffer[i] = c;
          i++;
        }

        if(j < buffer_size-1){
          instruction_for_user_ui[j] = c;
          j++;
        }
      }
    }

    c = fgetc(input);
  }

  if(ferror(input)){
    return 1;
  }
  buffer[i] = '\0';
  instruction_for_user_ui[j] = '\0';

  return 0;
}

//------------------------
//------- PRIVATE --------
//------------------------


int _parse(char * instruction_buffer, Parsed_str * parsed_instruct) {
  int cnt = 0;
	int start_index = 0;
	for (int i = 1; i <= strlen(instruction_buffer); i++) {
		switch (cnt) {
			case 0:
				if (instruction_buffer[i] == '$' || instruction_buffer[i] == '\0' || isdigit(instruction_buffer[i]) || instruction_buffer[i] == '-') {
					//printf("case 0 : start_i = %d, i = %d\n", start_index, i);
					parsed_instruct->opcode = malloc((i-start_index+1)*sizeof(char));
					memcpy(parsed_instruct->opcode, instruction_buffer+start_index, (i-start_index)*sizeof(char));
          parsed_instruct->opcode[i-start_index] = '\0';

					cnt++;
					start_index = i;
				}
				break;

			case 1:
				if (instruction_buffer[i] == ',' || instruction_buffer[i] == '\0') {
					//printf("case 1 : start_i = %d, i = %d\n", start_index, i);
					parsed_instruct->arg1 = malloc((i-start_index+1)*sizeof(char));
					memcpy(parsed_instruct->arg1, instruction_buffer+start_index, (i-start_index)*sizeof(char));
          parsed_instruct->arg1[i-start_index] = '\0';
					cnt++;
					start_index = i+1;
				}
				break;

			case 2:
				if (instruction_buffer[i] == ',' || instruction_buffer[i] == '(' || instruction_buffer[i] == '\0') {
					//printf("case 2 : start_i = %d, i = %d\n", start_index, i);
					parsed_instruct->arg2 = malloc((i-start_index+1)*sizeof(char));
					memcpy(parsed_instruct->arg2, instruction_buffer+start_index, (i-start_index)*sizeof(char));
          parsed_instruct->arg2[i-start_index] = '\0';
					cnt++;
					start_index = i+1;
				}
				break;
			case 3:
				if (instruction_buffer[i] == ',' || instruction_buffer[i] == '(' || instruction_buffer[i] == ')' || instruction_buffer[i] == '\0') {
					//printf("case 3 : start_i = %d, i = %d\n", start_index, i);
					parsed_instruct->arg3 = malloc((i-start_index+1)*sizeof(char));
					memcpy(parsed_instruct->arg3, instruction_buffer+start_index, (i-start_index)*sizeof(char));
          parsed_instruct->arg3[i-start_index] = '\0';
					cnt++;
					start_index = i+1;
				}
				break;
			default:
				break;
		}
	}

  parsed_instruct->nb_field = cnt;
	return cnt;
}


Instruction* _find_type(char* str_opcode){

  Instruction* temp_Instruction = head_lst_instruction;

  _strup(str_opcode); //conversion vers casse haute

  char find = 0;

  while((temp_Instruction != NULL) && (find != 1)){

    if(strcmp(str_opcode, temp_Instruction->str) == 0)
      find = 1;
    else{
      temp_Instruction = temp_Instruction->suivant;
    }
  }
  return temp_Instruction;
}

char _find_register(char* str_register, char* register_addr){

  Register* temp_Register = head_lst_register;

  _strup(str_register); //conversion vers casse haute

  char find = 0;

  while((temp_Register != NULL) && (find != 1)){

    if(strcmp(str_register, temp_Register->name1) == 0 || strcmp(str_register, temp_Register->name2) == 0){
      find = 1;
      *register_addr = temp_Register->address_value;
    }
    else
      temp_Register = temp_Register->suivant;
  }

  return find;
}


uint32_t _decode_r(Parsed_str *parsed_instruct, Instruction *instruction_type){

  char opcode;
  char rs;
  char rt;
  char rd;
  char sa;
  char function;

  // add, sub, and, or, xor, slt
  if(strcmp(instruction_type->str, STR_ADD) == 0 || strcmp(instruction_type->str, STR_SUB) == 0 || strcmp(instruction_type->str, STR_AND) == 0 || strcmp(instruction_type->str, STR_OR) == 0 || strcmp(instruction_type->str, STR_XOR) == 0 || strcmp(instruction_type->str, STR_SLT) == 0){

    opcode = 0;
    if(parsed_instruct->nb_field != 4){
      printf("Invalid instruction : Wrong number of operand\n");
      return R_VALUE_ERROR;
    }
    if(_find_register(parsed_instruct->arg1, &rd) == 0){
      printf("Unknown register : %s\n", parsed_instruct->arg1);
      return R_VALUE_ERROR;
    }
    if(_find_register(parsed_instruct->arg2, &rs) == 0){
      printf("Unknown register : %s\n", parsed_instruct->arg2);
      return R_VALUE_ERROR;
    }
    if(_find_register(parsed_instruct->arg3, &rt) == 0){
      printf("Unknown register : %s\n", parsed_instruct->arg3);
      return R_VALUE_ERROR;
    }
    sa = 0;
    function = instruction_type->opcode;
  }

  //mult, div
  else if(strcmp(instruction_type->str, STR_MULT) == 0 || strcmp(instruction_type->str, STR_DIV) == 0){
    opcode = 0;
    if(parsed_instruct->nb_field != 3){
      printf("Invalid instruction : Wrong number of operand\n");
      return R_VALUE_ERROR;
    }
    if(_find_register(parsed_instruct->arg1, &rs) == 0){
      printf("Unknown register : %s\n", parsed_instruct->arg1);
      return R_VALUE_ERROR;
    }
    if(_find_register(parsed_instruct->arg2, &rt) == 0){
      printf("Unknown register : %s\n", parsed_instruct->arg2);
      return R_VALUE_ERROR;
    }
    rd = 0;
    sa = 0;
    function = instruction_type->opcode;
  }

  //rotr
  else if(strcmp(instruction_type->str, STR_ROTR) == 0){

    opcode =0;
    rs = 1;
    if(parsed_instruct->nb_field != 4){
      printf("Invalid instruction : Wrong number of operand\n");
      return R_VALUE_ERROR;
    }
    if(_find_register(parsed_instruct->arg1, &rd) == 0){
      printf("Unknown register : %s\n", parsed_instruct->arg1);
      return R_VALUE_ERROR;
    }
    if(_find_register(parsed_instruct->arg2, &rt) == 0){
      printf("Unknown register : %s\n", parsed_instruct->arg2);
      return R_VALUE_ERROR;
    }
    if(_find_register(parsed_instruct->arg3, &sa) == 0){
      printf("Unknown register : %s\n", parsed_instruct->arg3);
      return R_VALUE_ERROR;
    }
    function = instruction_type->opcode;
  }

  //sll, srl
  else if(strcmp(instruction_type->str, STR_SLL) == 0 || strcmp(instruction_type->str, STR_SRL) == 0){

    opcode =0;
    rs = 0;
    if(parsed_instruct->nb_field != 4){
      printf("Invalid instruction : Wrong number of operand\n");
      return R_VALUE_ERROR;
    }
    if(_find_register(parsed_instruct->arg1, &rd) == 0){
      printf("Unknown register : %s\n", parsed_instruct->arg1);
      return R_VALUE_ERROR;
    }
    if(_find_register(parsed_instruct->arg2, &rt) == 0){
      printf("Unknown register : %s\n", parsed_instruct->arg2);
      return R_VALUE_ERROR;
    }
    if(_find_register(parsed_instruct->arg3, &sa) == 0){
      printf("Unknown register : %s\n", parsed_instruct->arg3);
      return R_VALUE_ERROR;
    }
    function = instruction_type->opcode;
  }

  //mfhi, mflo
  else if(strcmp(instruction_type->str, STR_MFHI) == 0 || strcmp(instruction_type->str, STR_MFLO) == 0){

    opcode = 0;
    rs = 0;
    rt = 0;
    if(parsed_instruct->nb_field != 2){
      printf("Invalid instruction : Wrong number of operand\n");
      return R_VALUE_ERROR;
    }
    if(_find_register(parsed_instruct->arg1, &rd) == 0){
      printf("Unknown register : %s\n", parsed_instruct->arg1);
      return R_VALUE_ERROR;
    }
    sa = 0;
    function = instruction_type->opcode;
  }

  //jr
  else if(strcmp(instruction_type->str, STR_JR) == 0){

    opcode = 0;
    if(parsed_instruct->nb_field != 2){
      printf("Invalid instruction : Wrong number of operand\n");
      return R_VALUE_ERROR;
    }
    if(_find_register(parsed_instruct->arg1, &rs) == 0){
      printf("Unknown register : %s\n", parsed_instruct->arg1);
      return R_VALUE_ERROR;
    }
    rt = 0;
    rd = 0;
    sa = 0;
    function = instruction_type->opcode;
  }

  //nop
  else{
    opcode = 0;
    rs = 0;
    rt = 0;
    rd = 0;
    sa = 0;
    function = 0;
  }

  //formation du resultat :
  int32_t result = function;

  result |= sa << 6;
  result |= rd << 11;
  result |= rt << 16;
  result |= rs << 21;
  result |= opcode << 26;

  return result;
}


uint32_t _decode_i(Parsed_str *parsed_instruct, Instruction *instruction_type){

  char opcode = instruction_type->opcode;
  char rs;
  char rt;
  int immediate;
  int32_t result;

  // addi
  if (strcmp(instruction_type->str, STR_ADDI) == 0 || strcmp(instruction_type->str, STR_BEQ) == 0 || strcmp(instruction_type->str, STR_BNE) == 0) {

    if(parsed_instruct->nb_field != 4){
      printf("Invalid instruction : Wrong number of operand\n");
      return I_VALUE_ERROR;
    }
    if(_find_register(parsed_instruct->arg1, &rt) == 0){
      printf("Unknown register : %s\n", parsed_instruct->arg1);
      return I_VALUE_ERROR;
    }
    if(_find_register(parsed_instruct->arg2, &rs) == 0){
      printf("Unknown register : %s\n", parsed_instruct->arg2);
      return I_VALUE_ERROR;
    }

    immediate = _str2int(parsed_instruct->arg3);
  }

  //sw, lw
  else if(strcmp(instruction_type->str, STR_LW) == 0 || strcmp(instruction_type->str, STR_SW) == 0){

    if(parsed_instruct->nb_field != 4){
      printf("Invalid instruction : Wrong number of operand\n");
      return I_VALUE_ERROR;
    }
    if(_find_register(parsed_instruct->arg1, &rt) == 0){
      printf("Unknown register : %s\n", parsed_instruct->arg1);
      return I_VALUE_ERROR;
    }

    immediate = _str2int(parsed_instruct->arg2);

    if(_find_register(parsed_instruct->arg3, &rs) == 0){
      printf("Unknown register : %s\n", parsed_instruct->arg3);
      return I_VALUE_ERROR;
    }


  }

  //lui
  else if(strcmp(instruction_type->str, STR_LUI) == 0){

    if(parsed_instruct->nb_field != 3){
      printf("Invalid instruction : Wrong number of operand\n");
      return I_VALUE_ERROR;
    }
    if(_find_register(parsed_instruct->arg1, &rt) == 0){
      printf("Unknown register : %s\n", parsed_instruct->arg1);
      return I_VALUE_ERROR;
    }

    immediate = _str2int(parsed_instruct->arg2);
    rs = 0;

  }

  //bgtz, blez
  else if(strcmp(instruction_type->str, STR_BGTZ) == 0 || strcmp(instruction_type->str, STR_BLEZ) == 0){

    if(parsed_instruct->nb_field != 3){
      printf("Invalid instruction : Wrong number of operand\n");
      return I_VALUE_ERROR;
    }
    if(_find_register(parsed_instruct->arg1, &rs) == 0){
      printf("Unknown register : %s\n", parsed_instruct->arg1);
      return I_VALUE_ERROR;
    }

    immediate = _str2int(parsed_instruct->arg2);
    rt = 0;

  }

  //beq, bne
  else if(strcmp(instruction_type->str, STR_BEQ) == 0 || strcmp(instruction_type->str, STR_BNE) == 0){

    if(parsed_instruct->nb_field != 4){
      printf("Invalid instruction : Wrong number of operand\n");
      return I_VALUE_ERROR;
    }
    if(_find_register(parsed_instruct->arg1, &rs) == 0){
      printf("Unknown register : %s\n", parsed_instruct->arg1);
      return I_VALUE_ERROR;
    }
    if(_find_register(parsed_instruct->arg2, &rt) == 0){
      printf("Unknown register : %s\n", parsed_instruct->arg2);
      return I_VALUE_ERROR;
    }

    immediate = _str2int(parsed_instruct->arg3);
  }

  //formation du resultat :
  if(immediate < -32768 || immediate > 32767) {
    printf("Out of bound immediate value : %d\n", immediate);
    return J_VALUE_ERROR;
  }

  if(immediate < 0){

    result = 0x8000;
    result += 0x8000 + immediate;
  }
  else
    result = immediate;


  result |= rt << 16;
  result |= rs << 21;
  result |= opcode << 26;

  return result;

}


uint32_t _decode_j(Parsed_str *parsed_instruct, Instruction *instruction_type){

  char opcode = instruction_type->opcode;
  int32_t result = 0;

  if(parsed_instruct->nb_field != 2){
    printf("Invalid instruction : Wrong number of operand\n");
    return J_VALUE_ERROR;
  }

  int target = _str2int(parsed_instruct->arg1);
  if(target < -33554432 || target > 33554431){
    printf("Out of bound target value : %d\n", target);
    return J_VALUE_ERROR;
  }

  if(target < 0){

    result = 0x2000000;
    result += 0x2000000 + target;
  }
  else
    result = target;

  result |= opcode << 26;

  return result;
}


char* _strup(char* str){

  int i = 0;

  while(str[i] != '\0'){

    if(str[i] >= 'a' && str[i] <= 'z'){
      str[i] += 'A'-'a';
    }
    i++;
  }
  return str;
}


int _str2int(char* str){

	size_t str_len = strlen(str);

	int return_value = 0;

	int valeur_limite = (str[0] == '-')? 1 : 0; //si le chiffre est negatif on modifie la valeur limite du for

	for(int i = valeur_limite; i < str_len; i++){

		return_value += pow(10,(str_len-1-i))*(str[i]-'0');
	}

	//Si valeur_limite alors on retoune -return_valeur, sinon on retourne return_valeur
	return(valeur_limite ? (-return_value) : return_value);
}






















//
