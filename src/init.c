#include "includes/init.h"
#include "includes/io.h"
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>


/**
 * Initialize everything... main directory etc...
 */
void init() {
    init_dirs();
}

/**
 * Create the `vpm` directory inside the $HOME/.vim directory if it does
 * not already exist.
 */
void init_dirs() {

    char* main_dir = get_directory();
    char* plugins_file = get_plugins_file(main_dir);

    // create ~/.vim/vpm if it does not exist
    struct stat st = {0};
    if (stat(main_dir, &st) == -1)
        mkdir(main_dir, 0700);

    // create sources.vim if it does not exist
    if (access(plugins_file, F_OK) == -1)
        write_file(plugins_file, "\" AUTO GENERATED (DO NOT EDIT)\n");

    free(plugins_file);
}

char* get_directory() {
    struct passwd *pw = getpwuid(getuid());

    char* directory = calloc(256, sizeof(char));
    strcat(directory, pw->pw_dir);
    strcat(directory, "/.vim/vpm");

    return directory; 
}

char* get_plugins_file(char* main_dir) {
    char* plugins_file = malloc(sizeof(char) * 256);
    strcpy(plugins_file, main_dir);
    strcat(plugins_file, "/sources.vim");

    return plugins_file;
}
