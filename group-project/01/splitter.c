#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

#define PARTITION_ARG_COUNT 4
#define MERGE_ARG_COUNT 3

typedef struct PMD {
    char filename[128];
    int split_count;
    int block_size;
    int last_block_size;
} PMD;

void partition(char *argv[])
{
    int split_count = atoi(argv[3]);
    if (split_count <= 1 || split_count > 16) {
        printf("Invalid count %d\n", split_count);
        exit(1);
    }

    char *filename = argv[2];

    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Cannot open '%s'\n", filename);
        exit(1);
    }

    struct stat fileInfo;
    fstat(fileno(fp), &fileInfo);
    int block_size = (fileInfo.st_size + split_count - 1) / split_count;

    char *buffer = (char *)malloc(block_size);

    for (int i = 0; i < split_count; i++) {
        size_t bytes_read = fread(buffer, 1, block_size, fp);

        char output_filename[1024];
        sprintf(output_filename, "%s.%d", filename, i);

        FILE *output = fopen(output_filename, "wb");
        fwrite(buffer, 1, bytes_read, output);
        fclose(output);
    }

    free(buffer);

    PMD pmd;
    strcpy(pmd.filename, filename);
    pmd.split_count = split_count;
    pmd.block_size = block_size;
    pmd.last_block_size = fileInfo.st_size - (block_size * (split_count - 1));

    char metadata_filename[1024];
    sprintf(metadata_filename, "%s.pmd", filename);
    FILE *metadata_fp = fopen(metadata_filename, "wb");

    if (metadata_fp == NULL) {
        printf("Cannot open '%s'.\n", metadata_filename);
        exit(1);
    }

    fwrite(&pmd, sizeof(PMD), 1, metadata_fp);
    fclose(metadata_fp);
}

void merge(char *filename)
{
    PMD *pmd = (PMD *)malloc(sizeof(PMD));
    FILE *pmd_fp = fopen(filename, "rb");
    fread(pmd, sizeof(PMD), 1, pmd_fp);
    fclose(pmd_fp);

    FILE *output_fp = fopen(pmd->filename,"wb");
    char *buffer = (char *)malloc(pmd->block_size);
    for (int i = 0; i < pmd->split_count; i++) {
        char par_files[256];

        sprintf(par_files,"%s.%d",pmd->filename,i);
        FILE *block_fp = fopen(par_files,"rb");

        if (i == pmd->split_count - 1) {
            fread(buffer, 1, pmd->last_block_size, block_fp);
            fwrite(buffer, 1, pmd->last_block_size, output_fp);
        } else {
            fread(buffer, 1, pmd->block_size, block_fp);
            fwrite(buffer, 1, pmd->block_size, output_fp);
        }

        fclose(block_fp);
    }

    fclose(output_fp);
    free(buffer);
}

int main(int argc, char *argv[])
{
    if (argc != PARTITION_ARG_COUNT && argc != MERGE_ARG_COUNT) {
        printf("Usage: %s -p <filename> <count>\n", argv[0]);
        printf("Usage: %s -m <filename>\n", argv[0]);
        exit(1);
    }

    if (argc == PARTITION_ARG_COUNT && strcmp(argv[1], "-p") == 0) {
        partition(argv);
    } else if (argc == MERGE_ARG_COUNT && strcmp(argv[1], "-m") == 0) {
        merge(argv[2]);
    } else {
        printf("Usage: %s -p <filename> <count>\n", argv[0]);
        printf("Usage: %s -m <filename>\n", argv[0]);
        exit(1);
    }
}
