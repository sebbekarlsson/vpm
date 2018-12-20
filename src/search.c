#include "includes/search.h"
#include "includes/uninstall.h"
#include "includes/request.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>


typedef struct DATA_STRUCT {
    int pages;
    char* plugins;
} data;


/**
 * !!!!! EXTREMELY UGLY HACK !!!!!!
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
    char* str;

    while (current_char != '\0') {
        while(current_char == ' ') {
            index += 1;
            current_char = result[index];
        }

        if (current_char == '"') {
            next_is_pages = 0;
            str = calloc(512, sizeof(char));

            index += 1;
            current_char = result[index];

            while(current_char != '"' && current_char != '\0') {
                char char_str[2] = {};
                char_str[0] = current_char;
                char_str[1] = '\0';
                strcat(str, char_str);
                index += 1;
                current_char = result[index];
            }

            if (strcmp(str, "total_pages") == 0) {
                next_is_pages = 1;
            } else if (strcmp(str, "github_url") == 0) {
                next_is_github_url = 1;
            } else if (next_is_github_url) {
                strcat(x->plugins, str);
                strcat(x->plugins, "\n");
                next_is_github_url = 0;
            }

            free(str);
           
        } else if (isdigit(current_char)) {
            char* digit = calloc(512, sizeof(char));

            while (isdigit(current_char)) {
                char char_str[2] = {};
                char_str[0] = current_char;
                char_str[1] = '\0';
                strcat(digit, char_str);

                index += 1;
                current_char = result[index];
            }

            if (next_is_pages) {
                x->pages = atoi(digit);
                next_is_pages = 0;
            }

            free(digit);
        }

        index += 1;
        current_char = result[index];
    }

    return x;
};

void search(char* query) {
    char* url_template = "https://vimawesome.com/api/plugins?query=%s&page=%d";
    char* querybuffer = calloc(256, sizeof(char));

    int page = 1;

    sprintf(querybuffer, url_template, query, page);

    char* plugins = calloc(1024, sizeof(char));
    int count = 0;

    char* result = request(querybuffer);
    data* data = get_data(result);
    strcat(plugins, data->plugins);

    while (count < data->pages) {
        result = request(querybuffer);
        data = get_data(result);

        plugins = realloc(
            plugins,
            (strlen(plugins) + strlen(data->plugins) + 1) * sizeof(char)
        );

        strcat(plugins, data->plugins);
        count += 1;
    }

    printf(plugins);

    free(plugins);
    free(data->plugins);
    free(result);
    free(querybuffer);
    free(data);
}
