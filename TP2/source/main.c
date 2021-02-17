#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "decoder.h"

int main(int argc, char const *argv[]){

	if(argc < 2)
		printf("Veuillez passer en absolue: [fichier source] [fichier cible]\n");

	else{
		//Open files
	  FILE* inputFile; FILE* outputFile;

	  inputFile = fopen(argv[1], "r" );
	  if ( inputFile == NULL ) {
	      printf( "Cannot open file %s\n", argv[1]);
	      return 1;
	  }

	  outputFile = fopen(argv[2], "w" );
	  if ( outputFile == NULL ) {
	      printf( "Unable to create/write file %s\n", argv[2]);
	      return 1;
	  }

		//reading
		char instruction_buffer[LEN_INSTRUCT_MAX];
		char instruction_for_user_ui[LEN_INSTRUCT_MAX];

		while(! feof(inputFile)){
	    //get asm instruction one line by one line
	    if(read_asm_line(instruction_buffer, instruction_for_user_ui, LEN_INSTRUCT_MAX, inputFile)){
	      printf("Read error : %d of file %s\n", errno, argv[1]);
	      return 1;
	    }
			else if(strlen(instruction_buffer) > 1){
				int32_t binary_code;
				printf("\n");
				printf("Computing : '%s'\n", instruction_for_user_ui);
				if(decode(instruction_buffer, &binary_code) == 0){
					printf("hex value : %x\n", binary_code);
					fprintf(outputFile, "%x\n", binary_code);
				}
			}
		}

	  fclose(outputFile);
	  fclose(inputFile);
	}

	return 0;
}
