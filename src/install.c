#include "includes/install.h"
#include "includes/uninstall.h"
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

    if(system("vim +PluginInstall +qall")) {
        printf("Vim responded with an error.\n");
        char c;
        do {
            printf("Revert and uninstall the plugin? (y/n)");
            scanf(" %c", &c);
        } while(c != 'n' && c != 'y'); 

        if (c == 'y')
            uninstall(plugname);
        else
            printf("Will keep broken plugin.\n");
    } else {
        printf("Vim responded with OK.\n");
    }

    free(plugins_file_contents);
    free(plug_line);
    free(plugins_file);
    free(directory);

    return 0;
};
