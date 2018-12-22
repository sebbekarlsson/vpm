#include "includes/uninstall.h"
#include "includes/parse_tools.h"
#include "includes/init.h"
#include "includes/io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* charstring(char c) {
    char str[2] = {};
    str[0] = c;
    str[1] = '\0';
    char *s_ptr = calloc(2, sizeof(char));
    strcpy(s_ptr, str);

    return s_ptr;
}

char* format(char* buffer0, char* buffer1) {
    char* str = calloc(strlen(buffer0) + strlen(buffer1), sizeof(char));
    sprintf(str, buffer0, buffer1);

    return str;
}

/**
 * Uninstall a vim plugin
 * 
 * @param char* plugname
 * 
 * @return int
 */
int uninstall(char* plugname) {
    printf("Uninstalling plugin %s ...\n", plugname);
    
    int removed = 0;

    char* directory = get_directory();
    char* plugins_file = get_plugins_file(directory);

    char* plugins_file_contents = read_file(plugins_file);
    char* new_contents = calloc(strlen(plugins_file_contents), sizeof(char));

    // for lexing
    int index = 0;
    char current_char = plugins_file_contents[index];
    char* current_char_str;
    
    char* line;
    char* expected;

    // parsing line by line
    while (current_char != '\0') {
        line = calloc(256, sizeof(char));
        current_char_str = charstring(current_char);
        strcat(line, current_char_str);
        advance(&index, &current_char, plugins_file_contents);

        while (current_char != '\n' && current_char != '\0') {
            current_char_str = charstring(current_char);
            strcat(line, current_char_str);
            advance(&index, &current_char, plugins_file_contents);
        }

        expected = format("Plugin '%s'", plugname);

        if (strstr(line, expected) == NULL) {
            strcat(new_contents, line);
        } else {
            removed += 1;
        }
    }

    free(expected);
    free(line);
    free(current_char_str);

    if (removed) {
        write_file(plugins_file, new_contents);

        if (system("vim +PluginInstall +qall")) {
            printf("Vim responded with an error.\n");
        } else {
            printf("Vim responded with OK.\n");
        }
    } 

    printf("Removed %d plugins.\n", removed);

    free(new_contents);
    free(plugins_file_contents);
    free(plugins_file);
    free(directory);

    return 0;
};
