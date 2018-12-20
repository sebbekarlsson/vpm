#include "includes/install.h"
#include "includes/init.h"
#include "includes/io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * Install a vim plugin
 * 
 * @param char* plugname
 * 
 * @return int
 */
int install(char* plugname) {
    printf("Installing plugin %s ...\n", plugname); 
    
    char* directory = get_directory();
    char* plugins_file = get_plugins_file(directory);

    char* plugins_file_contents = read_file(plugins_file);
    char* plug_line = malloc(sizeof(char) * 128);
    sprintf(plug_line, "Plugin '%s'\n", plugname);
    strcat(plugins_file_contents, plug_line);

    write_file(plugins_file, plugins_file_contents);

    int vim_response = system("vim +PluginInstall +qall");
    printf("Vim responded with %d\n", vim_response);

    return 0;
};
