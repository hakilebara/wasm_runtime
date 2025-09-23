#include <stdio.h>
#include <stdlib.h>


typedef struct __attribute__((packed)) {
  uint32_t wasm_magic;
  uint32_t wasm_version;
} Wasm;

int main(int argc, char **argv) {
  
  if (argc < 2) {
    printf("Usage: runtime <wasm module>");
  }

  char *filename = *++argv;

  FILE *fptr = fopen(filename, "r");
  Wasm wasm_struct;
  
  fread(&wasm_struct, sizeof(Wasm), 1, fptr);

  printf("%x\n", wasm_struct.wasm_magic);

  return EXIT_SUCCESS;
}
