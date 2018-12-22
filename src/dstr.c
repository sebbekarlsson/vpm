#include "includes/dstr.h"
#include <stdlib.h>
#include <string.h>


/**
 * Initialize a new dynamic string
 *
 * @return dstr*
 */
dstr* init_dstr() {
    dstr* str = calloc(1, sizeof(dstr));
    str->value = calloc(1, sizeof(char));

    return str;
}

/**
 * Concat a dynamic string with a regular string
 *
 * @param dstr* str
 * @param char* value
 */
void dstr_cat(dstr* str, char* value) {
    str->value = realloc(
        str->value,
        (strlen(str->value) + strlen(value) + 1) * sizeof(char)
    );
    strcat(str->value, value);
}

/**
 * Concat a dynamic string with a regular char
 *
 * @param dstr* str
 * @param char c
 */
void dstr_cat_c(dstr* str, char c) {
    char s[2] = {};
    s[0] = c;
    s[1] = '\0';
    dstr_cat(str, s);
}

/**
 * Free the memory of a dynamic string
 *
 * @param dstr* str
 */
void free_dstr(dstr* str) {
    free(str->value);
    free(str);
}
