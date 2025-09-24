#include <stdio.h>
#include <stdlib.h>


typedef struct __attribute__((packed)) {
  uint8_t wasm_magic[4];
  uint32_t wasm_version;
} WasmHeader;

bool is_wasm_header_valid(WasmHeader *wasm_header) {
  return 
    wasm_header->wasm_magic[0] == '\0' &&
    wasm_header->wasm_magic[1] == 'a' &&
    wasm_header->wasm_magic[2] == 's' &&
    wasm_header->wasm_magic[3] == 'm';
}

int main(int argc, char **argv) {
  
  if (argc < 2) {
    printf("Usage: runtime <wasm module>");
  }

  char *filename = *++argv;

  FILE *fptr = fopen(filename, "r");
  WasmHeader wasm_header;
  
  fread(&wasm_header, sizeof(WasmHeader), 1, fptr);

  if (!is_wasm_header_valid(&wasm_header)) {
    printf("This is not a valid WASM file\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
