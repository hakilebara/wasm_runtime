#ifndef LEB128_H
#define LEB128_H

#include <inttypes.h>
#include <stdio.h>

uint64_t readULEB128FromFile(FILE *fptr);

#endif
