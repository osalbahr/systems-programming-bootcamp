#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

#define HASH_ARGC 3
#define UNHASH_ARGC 3
#define UNHASH_FILE_ARGC 5

void hash(char *filename)
{
    FILE *input = fopen(filename, "rb");
    if (input == NULL) {
        printf("Error: Cannot open file '%s'\n", filename);
        exit(1);
    }

    unsigned char hash[32] = {0};
    for (int i = 0;; i++) {
        unsigned char ch = (unsigned char)getc(input);
        if (feof(input)) {
            break;
        }

        hash[i % 32] ^= ch;
    }

    char dirname[2 + 1];
    sprintf(dirname, "%02x", hash[0]);

    if (mkdir(dirname, 0777) == -1 && errno != EEXIST) {
        printf("Error: Cannot create directory '%s'\n", dirname);
        exit(1);
    }

    char output_filename[2 + 1 + 31 * 2 + 1];
    sprintf(output_filename, "%02x/", hash[0]);
    for (int i = 1; i < 32; i++) {
        char hex[2 + 1];
        sprintf(hex, "%02x", hash[i]);
        strcat(output_filename, hex);
    }

    FILE *output = fopen(output_filename, "wb");
    if (output == NULL) {
        printf("Error: Cannot open file '%s'\n", output_filename);
        exit(1);
    }

    rewind(input);
    for (int i = 0;; i++) {
        unsigned char ch = (unsigned char)getc(input);
        if (feof(input)) {
            break;
        }

        ch ^= hash[i % 32];
        fwrite(&ch, 1, 1, output);
    }

    fclose(input);
    fclose(output);
}

void unhash(int argc, char *argv[])
{
    printf("unhash() not implemented\n");
    exit(1);
}

int main(int argc, char *argv[])
{
    if (argc == HASH_ARGC && strcmp(argv[1], "-h") == 0) {
        hash(argv[2]);
    } else if (argc == UNHASH_ARGC && strcmp(argv[1], "-u") == 0) {
        unhash(argc, argv);
    } else if (argc == UNHASH_FILE_ARGC && strcmp(argv[1], "-u") == 0 && strcmp(argv[3], "-f") == 0) {
        unhash(argc, argv);
    } else {
        printf("Usage: %s -h <filename>\n", argv[0]);
        printf("Usage: %s -u <hash>\n", argv[0]);
        printf("Usage: %s -u <hash> -f <new_filename>\n", argv[0]);
        exit(1);
    }
}
