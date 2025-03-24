#include "input.h"

void getStringInput(char* buffer, size_t size) {
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}

void getUnsignedInput(unsigned int* value) {
    scanf("%u", value);
    while (getchar() != '\n'); // Clear buffer
}

void getIntegerInput(int* value) {
    scanf("%d", value);
    while (getchar() != '\n');
}
