#include "includes/init.h"
#include "includes/install.h"
#include "includes/uninstall.h"
#include <stdio.h>
#include <string.h>


int main (int argc, char* argv[]) {
    init();

    char* cmd = argv[1];
    char* plugname = argv[2];

    if (strcmp(cmd, "install") == 0)
        install(plugname);
    else if (strcmp(cmd, "uninstall") == 0)
        uninstall(plugname);
    else
        printf("Unknown command %s\n", cmd);

    return 0;
};
