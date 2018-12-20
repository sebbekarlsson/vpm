#include "includes/list_plugins.h"
#include "includes/init.h"
#include "includes/io.h"

/**
 * List installed plugins
 */
void list_plugins(char* plugname) {
    char* directory = get_directory();
    char* plugins_file = get_plugins_file(directory);
    char* plugins_file_contents = read_file(plugins_file);

    printf("%s", plugins_file_contents);

    free(plugins_file);
    free(plugins_file_contents);
};
