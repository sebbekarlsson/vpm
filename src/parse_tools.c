#include "includes/parse_tools.h"
#include <string.h>


void advance(int* index, char* current_char, char* buffer) {
    if (*index < strlen(buffer)) {
        *index += 1;
        *current_char = buffer[*index];
    }
}
