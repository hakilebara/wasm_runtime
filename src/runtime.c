#include <stdio.h>
#include <stdlib.h>
#include "../lib/leb128.h"

#define CUSTOM_SECTION      0
#define TYPE_SECTION        1
#define IMPORT_SECTION      2
#define FUNCTION_SECTION    3
#define TABLE_SECTION       4
#define MEMORY_SECTION      5
#define GLOBAL_SECTION      6
#define EXPORT_SECTION      7
#define START_SECTION       8
#define ELEMENT_SECTION     9
#define CODE_SECTION        10
#define DATA_SECTION        11
#define DATA_COUNT_SECTION  12
#define TAG_SECTION         13

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
    section_size = readULEB128FromFile(fptr);

    switch (id) {
      case CUSTOM_SECTION:
        printf("0: Custom Section - size : %llu - pos: %ld\n", section_size, ftell(fptr));
        fseek(fptr, section_size, SEEK_CUR);
        break;
      case TYPE_SECTION:
        printf("1: Type Section - size : %llu - pos: %ld\n", section_size, ftell(fptr));
        fseek(fptr, section_size, SEEK_CUR);
        break;
      case IMPORT_SECTION:
        printf("2: Import Section - size : %llu - pos: %ld\n", section_size, ftell(fptr));
        fseek(fptr, section_size, SEEK_CUR);
        break;
      case FUNCTION_SECTION:
        printf("3: Function Section - size : %llu - pos: %ld\n", section_size, ftell(fptr));
        fseek(fptr, section_size, SEEK_CUR);
        break;
      case TABLE_SECTION:
        printf("4: Table Section - size : %llu - pos: %ld\n", section_size, ftell(fptr));
        fseek(fptr, section_size, SEEK_CUR);
        break;
      case MEMORY_SECTION:
        printf("5: Memory Section - size : %llu - pos: %ld\n", section_size, ftell(fptr));
        fseek(fptr, section_size, SEEK_CUR);
        break;
      case GLOBAL_SECTION:
        printf("6: Global Section - size : %llu - pos: %ld\n", section_size, ftell(fptr));
        fseek(fptr, section_size, SEEK_CUR);
        break;
      case EXPORT_SECTION:
        printf("7: Export Section - size : %llu - pos: %ld\n", section_size, ftell(fptr));
        fseek(fptr, section_size, SEEK_CUR);
        break;
      case START_SECTION:
        printf("8: Start Section - size : %llu - pos: %ld\n", section_size, ftell(fptr));
        fseek(fptr, section_size, SEEK_CUR);
        break;
      case ELEMENT_SECTION:
        printf("9: Element Section - size : %llu - pos: %ld\n", section_size, ftell(fptr));
        fseek(fptr, section_size, SEEK_CUR);
        break;
      case CODE_SECTION:
        printf("10: Code Section - size : %llu - pos: %ld\n", section_size, ftell(fptr));
        fseek(fptr, section_size, SEEK_CUR);
        break;
      case DATA_SECTION:
        printf("11: Data Section - size : %llu - pos: %ld\n", section_size, ftell(fptr));
        fseek(fptr, section_size, SEEK_CUR);
        break;
      case DATA_COUNT_SECTION:
        printf("12: Data Count Section - size : %llu - pos: %ld\n", section_size, ftell(fptr));
        fseek(fptr, section_size, SEEK_CUR);
        break;
      case TAG_SECTION:
        printf("13: Tag Section - size : %llu - pos: %ld\n", section_size, ftell(fptr));
        fseek(fptr, section_size, SEEK_CUR);
        break;
      default:
        break;
    }
  }

  return EXIT_SUCCESS;
}
