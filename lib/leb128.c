#include "leb128.h"

uint64_t readULEB128FromFile(FILE *fptr) {
  uint8_t byte = fgetc(fptr);
  uint64_t acc = 0;
  int i = 0;
  if (byte < 128) {
    return byte;
  }
  else {
    acc += byte - 128;
    while (!feof(fptr)) {
      if ((byte = fgetc(fptr)) > 128) {
        acc += (byte - 128) << (7+i);
        ++i;
      } else {
        acc += byte << (7+i);
        break;
      }
    }
  }
  return acc;
}
