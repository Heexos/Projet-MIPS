#include <stdio.h>
#include "ram_emul.h"
#include "registre_emul.h"

int main(int argc, char const *argv[]) {

  write_register(666,0);
  int32_t test;
  read_register(&test,0);
  printf("Contenue du registre 0 : %d\n",test);

  init_VRAM();

  VRAM_store(8,1, 14);
  VRAM_load(0,8, &test);
  printf("Contenue de la Vram au bloc 8: %d\n", test);

  return 0;
}
