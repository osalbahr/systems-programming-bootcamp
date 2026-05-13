#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

typedef struct PMD {
    char filename[128];
    int split_count;
    int block_size;
    int last_block_size;
} PMD;

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Usage: %s <filename> <count>\n", argv[0]);
        exit(1);
    }

    int split_count = atoi(argv[2]);
    if (split_count <= 1 || split_count > 16) {
        printf("Invalid count %d\n", split_count);
        exit(1);
    }

    char *filename = argv[1];

    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Cannot open '%s'\n", filename);
        exit(1);
    }

    struct stat fileInfo;
    fstat(fileno(fp), &fileInfo);
    int block_size = (fileInfo.st_size + split_count - 1) / split_count;

    char *buffer = (char *)malloc(block_size);
    
    for(int i = 0; i < split_count; i++){
        size_t bytes_read = fread(buffer, 1, block_size, fp);

        char output_filename[1024];
        sprintf(output_filename, "%s.%d", filename, i);

        FILE *output = fopen(output_filename, "wb");
        fwrite(buffer, 1, bytes_read, output);
        fclose(output);
    }

    free(buffer);
}
