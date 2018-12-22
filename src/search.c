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
    char* plugins;
} data;

/**
 * TODO: make this prettier
 */
data* get_data(char* result) {
    data* x = calloc(1, sizeof(data));
    x->plugins = calloc(1024, sizeof(char));
    x->pages = 0;

    int index = 0;
    char current_char = result[index];

    int next_is_pages = 0;
    int next_is_github_url = 0;
    dstr* dstr_str;

    while (current_char != '\0') {
        while(current_char == ' ')
            advance(&index, &current_char, result);

        // String parsing
        if (current_char == '"') {
            dstr_str = init_dstr();
            next_is_pages = 0;

            advance(&index, &current_char, result);

            while(current_char != '"' && current_char != '\0') {
                dstr_cat_c(dstr_str, current_char);
                advance(&index, &current_char, result);
            }

            if (strcmp(dstr_str->value, "total_pages") == 0) {
                next_is_pages = 1;
            } else if (strcmp(dstr_str->value, "github_url") == 0) {
                next_is_github_url = 1;
            } else if (next_is_github_url) {
                strcat(x->plugins, dstr_str->value);
                strcat(x->plugins, "\n");
                next_is_github_url = 0;
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

            if (next_is_pages) {
                x->pages = atoi(dstr_digit->value);
                next_is_pages = 0;
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

        dstr_cat(dstr_plugins, data->plugins);
    } while (page < data->pages);
    
    free(querybuffer);
    free(result);
    free(data->plugins);
    free(data);

    printf(dstr_plugins->value);
    free_dstr(dstr_plugins);
}
