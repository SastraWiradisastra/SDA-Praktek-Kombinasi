#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include "length.h"

void getStringInput(char* buffer, size_t size);
void getUnsignedInput(unsigned int* value);
void getIntegerInput(int* value);

#endif
