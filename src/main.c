#include "includes/init.h"
#include "includes/install.h"
#include "includes/uninstall.h"
#include "includes/list_plugins.h"
#include "includes/search.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char* argv[]) {
    init();

    int print_help = 0;

    // look for help flag
    for (int i = 1; i < argc; i++)
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0)
            print_help = 1;

    if (argc <= 2 || print_help) {
        printf("Usage: vpm <command>\n");
        printf("Available commands:\n* install\n* uninstall\n* list\n* search\n");
        exit(print_help ? 0 : 1);
    }

    char* cmd = argv[1];

    if (strcmp(cmd, "install") == 0) {
        install(argv[2]);
    } else if (strcmp(cmd, "uninstall") == 0) {
        uninstall(argv[2]);
    } else if (strcmp(cmd, "list") == 0) {
        list_plugins();
    } else if (strcmp(cmd, "search") == 0) {
        search(argv[2]);
    }

    return 0;
};
