#include <assert.h>
#include <stdio.h>
#include "../lib/leb128.h"

void test_readULEB128FromFile() {
  FILE *fptr = fopen("test/hello_world.wasm", "r");
  fseek(fptr, 9, SEEK_SET);
  uint64_t size = readULEB128FromFile(fptr);
  assert(size == 146);
  fseek(fptr, 158, SEEK_SET);
  size = readULEB128FromFile(fptr);
  assert(size == 137);
}

int main() {
  test_readULEB128FromFile();
  return 0;
}
