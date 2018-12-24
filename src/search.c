#include "includes/search.h"
#include "includes/uninstall.h"
#include "includes/request.h"
#include "includes/parse_tools.h"
#include "includes/dstr.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>


typedef struct DATA_STRUCT {
    int pages;
    dstr* dstr_plugins;
} data;

/**
 * TODO: make this prettier
 */
data* get_data(char* result) {
    data* x = calloc(1, sizeof(data));
    x->dstr_plugins = init_dstr();
    x->pages = 0;

    int index = 0;
    char current_char = result[index];

    char* current_lookup_key = calloc(2, sizeof(char));
    dstr* dstr_str;

    while (current_char != '\0') {
        while(current_char == ' ')
            advance(&index, &current_char, result);

        // String parsing
        if (current_char == '"') {
            dstr_str = init_dstr();

            advance(&index, &current_char, result);

            while(current_char != '"' && current_char != '\0') {
                dstr_cat_c(dstr_str, current_char);
                advance(&index, &current_char, result);
            }

            if (
               strcmp(dstr_str->value, "total_pages") == 0 ||
               strcmp(dstr_str->value, "github_url") == 0
            ) {
                current_lookup_key = realloc(
                    current_lookup_key,
                    (strlen(dstr_str->value) + 1) * sizeof(char)
                );
                strcpy(current_lookup_key, dstr_str->value);
            } else if (strcmp(current_lookup_key, "github_url") == 0) {
                dstr_cat(x->dstr_plugins, dstr_str->value);
                dstr_cat(x->dstr_plugins, "\n");
                strcpy(current_lookup_key, "\0");
            }

            free_dstr(dstr_str);
        } 

        // Digit parsing
        else if (isdigit(current_char)) {
            dstr* dstr_digit = init_dstr();

            while (isdigit(current_char)) {
                dstr_cat_c(dstr_digit, current_char);
                advance(&index, &current_char, result);
            }

            if (strcmp(current_lookup_key, "total_pages") == 0) {
                x->pages = atoi(dstr_digit->value);
                strcpy(current_lookup_key, "\0");
            }

            free_dstr(dstr_digit);
        }

        advance(&index, &current_char, result);
    }

    return x;
};

void search(char* query) {
    char* url_template = "https://vimawesome.com/api/plugins?query=%s&page=%d";
    
    char* querybuffer = calloc(strlen(url_template) + strlen(query) + 1, sizeof(char));
    dstr* dstr_plugins = init_dstr();

    int page = 0;
    char* result;
    data* data;
    
    do {
        page += 1;

        sprintf(querybuffer, url_template, query, page);
        result = request(querybuffer);
        data = get_data(result);

        dstr_cat(dstr_plugins, data->dstr_plugins->value);
    } while (page < data->pages);
    
    free(querybuffer);
    free(result);
    free_dstr(data->dstr_plugins);
    free(data);

    printf(dstr_plugins->value);
    free_dstr(dstr_plugins);
}
