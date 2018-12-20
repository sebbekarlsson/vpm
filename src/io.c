#include "includes/io.h"


/**
 * Reads the content of a file
 *
 * @param char* filename
 *
 * @return char*
 */
char* read_file(char* filename) {
    char * buffer = 0;
    long length;
    FILE * f = fopen (filename, "rb");

    if (f) {
        fseek (f, 0, SEEK_END);
        length = ftell (f);
        fseek (f, 0, SEEK_SET);
        buffer = calloc (length, length);
        if (buffer)
            fread (buffer, 1, length, f);

        fclose (f);
    }

    return buffer;
}

/**
 * Writes contents to a file
 *
 * @param char* filename
 *
 * @return char*
 */
char* write_file(char* filename, char* contents) {
    FILE *f = fopen(filename, "w+");

    if (f == NULL) {
        printf("Cannot read file %s!\n", filename);
        exit(1);
    }

    fprintf(f, "%s", contents);
    fclose(f);

    return contents;
}
