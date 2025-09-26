#include <stdio.h>
#include <stdlib.h>


typedef struct __attribute__((packed)) {
  uint8_t magic[4];
  uint32_t version;
} WasmHeader;

typedef struct __attribute__((packed)) {
  WasmHeader header;
} WasmModule;

bool is_wasm_header_valid(WasmHeader *wasm_header) {
  return 
    wasm_header->magic[0] == '\0' &&
    wasm_header->magic[1] == 'a' &&
    wasm_header->magic[2] == 's' &&
    wasm_header->magic[3] == 'm';
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
  if (wasm_header.version != 1) {
    printf("This WASM version is not supported\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
