#include <stdio.h>
#include <stdlib.h>
#include "../lib/leb128.h"


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

  uint8_t id = 0;
  uint64_t section_size = 0;
  while(!feof(fptr)) {
    id = fgetc(fptr);

    switch (id) {
      case 0:
        section_size = readULEB128FromFile(fptr);
        printf("0: Custom Section - size : %llu - pos: %ld\n", section_size, ftell(fptr));
        fseek(fptr, section_size, SEEK_CUR);
        break;
      case 1:
        section_size = readULEB128FromFile(fptr);
        printf("1: Type Section - size : %llu - pos: %ld\n", section_size, ftell(fptr));
        fseek(fptr, section_size, SEEK_CUR);
        break;
      case 2:
        section_size = readULEB128FromFile(fptr);
        printf("2: Import Section - size : %llu - pos: %ld\n", section_size, ftell(fptr));
        fseek(fptr, section_size, SEEK_CUR);
        break;
      case 3:
        section_size = readULEB128FromFile(fptr);
        printf("3: Function Section - size : %llu - pos: %ld\n", section_size, ftell(fptr));
        fseek(fptr, section_size, SEEK_CUR);
        break;
      case 4:
        section_size = readULEB128FromFile(fptr);
        printf("4: Table Section - size : %llu - pos: %ld\n", section_size, ftell(fptr));
        fseek(fptr, section_size, SEEK_CUR);
        break;
      case 5:
        section_size = readULEB128FromFile(fptr);
        printf("5: Memory Section - size : %llu - pos: %ld\n", section_size, ftell(fptr));
        fseek(fptr, section_size, SEEK_CUR);
        break;
      case 6:
        section_size = readULEB128FromFile(fptr);
        printf("6: Global Section - size : %llu - pos: %ld\n", section_size, ftell(fptr));
        fseek(fptr, section_size, SEEK_CUR);
        break;
      case 7:
        section_size = readULEB128FromFile(fptr);
        printf("7: Export Section - size : %llu - pos: %ld\n", section_size, ftell(fptr));
        fseek(fptr, section_size, SEEK_CUR);
        break;
      case 8:
        section_size = readULEB128FromFile(fptr);
        printf("8: Start Section - size : %llu - pos: %ld\n", section_size, ftell(fptr));
        fseek(fptr, section_size, SEEK_CUR);
        break;
      case 9:
        section_size = readULEB128FromFile(fptr);
        printf("9: Element Section - size : %llu - pos: %ld\n", section_size, ftell(fptr));
        fseek(fptr, section_size, SEEK_CUR);
        break;
      case 10:
        section_size = readULEB128FromFile(fptr);
        printf("10: Code Section - size : %llu - pos: %ld\n", section_size, ftell(fptr));
        fseek(fptr, section_size, SEEK_CUR);
        break;
      case 11:
        section_size = readULEB128FromFile(fptr);
        printf("11: Data Section - size : %llu - pos: %ld\n", section_size, ftell(fptr));
        fseek(fptr, section_size, SEEK_CUR);
        break;
      case 12:
        section_size = readULEB128FromFile(fptr);
        printf("12: Data Count Section - size : %llu - pos: %ld\n", section_size, ftell(fptr));
        fseek(fptr, section_size, SEEK_CUR);
        break;
      case 13:
        section_size = readULEB128FromFile(fptr);
        printf("13: Tag Section - size : %llu - pos: %ld\n", section_size, ftell(fptr));
        fseek(fptr, section_size, SEEK_CUR);
        break;
      default:
        break;
    }
  }

  return EXIT_SUCCESS;
}
