#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define PARTITION_RANDOM_ARG_COUNT 6
#define PARTITION_ARG_COUNT 4
#define MERGE_ARG_COUNT 3
#define MERGE_WITH_ROTATE_ARG_COUNT 6
#define MERGE_RANDOM_ARG_COUNT 5

typedef struct PMD {
    char filename[128];
    int split_count;
    int block_size;
    int last_block_size;
    // 0 means original, 1 means random
    unsigned short rand_positions;
    int rand_count;
} PMD;

unsigned short randomize_positions(int zero_count, int one_count)
{
    int total_count = zero_count + one_count;

    unsigned char *before_rand = malloc(sizeof(int) * total_count);
    unsigned char *after_rand = malloc(sizeof(int) * total_count);

    int idx = 0;
    for (int i = 0; i < zero_count; i++) {
        before_rand[idx++] = 0;
    }

    for (int i = 0; i < one_count; i++) {
        before_rand[idx++] = 1;
    }

    srand(time(NULL));
    bool *has_been_picked = calloc(total_count, sizeof(bool));
    for (int after_idx = 0; after_idx < total_count; after_idx++) {
        for (;;) {
            int before_idx = rand() % total_count;
            if (!has_been_picked[before_idx]) {
                after_rand[after_idx] = before_rand[before_idx];
                has_been_picked[before_idx] = true;
                break;
            }
        }
    }

    unsigned short result = 0x0;
    for (int i = 0; i < total_count; i++) {
        result |= after_rand[i] * (1 << i);
    }

    free(before_rand);
    free(after_rand);

    return result;
}

void partition(int argc , char *argv[])
{
    unsigned short rand_positions = 0x0;

    int split_count = atoi(argv[3]);
    if (split_count <= 1 || split_count > 16) {
        printf("Invalid count %d\n", split_count);
        exit(1);
    }

    int total_count = split_count;

    int rand_count = 0;
    if (argc == PARTITION_RANDOM_ARG_COUNT) {
        rand_count = atoi(argv[5]);
        if (rand_count <= 0) {
            printf("Invalid random count %d\n", rand_count);
            exit(1);
        }

        total_count = split_count + rand_count;
        if (total_count > 16) {
            printf("Invalid total count %d\n", total_count);
            exit(1);
        }

        rand_positions = randomize_positions(split_count, rand_count);
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

    for (int i = 0; i < total_count; i++) {
        char output_filename[1024];
        sprintf(output_filename, "%s.%d", filename, i);
        FILE *output = fopen(output_filename, "wb");

        // 0 means original, 1 means random
        bool current_parity = rand_positions & (1 << i);
        if (current_parity) {
            for (int i = 0; i < block_size; i++) {
                unsigned char random_byte = rand() & 0xFF;
                fwrite(&random_byte, 1, 1, output);
            }
        } else {
            size_t bytes_read = fread(buffer, 1, block_size, fp);
            fwrite(buffer, 1, bytes_read, output);
        }

        fclose(output);
    }

    fclose(fp);
    free(buffer);

    PMD pmd;
    strcpy(pmd.filename, filename);
    pmd.split_count = split_count;
    pmd.block_size = block_size;
    pmd.last_block_size = fileInfo.st_size - (block_size * (split_count - 1));
    pmd.rand_positions = rand_positions;
    pmd.rand_count = rand_count;

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

void merge(int argc,char *argv[])
{
    char *filename = argv[2];

    PMD pmd;
    FILE *pmd_fp = fopen(filename, "rb");

    if (pmd_fp == NULL) {
        printf("Cannot open '%s'\n", filename);
        exit(1);
    }

    fread(&pmd, sizeof(PMD), 1, pmd_fp);
    fclose(pmd_fp);

    int total_count = pmd.split_count + pmd.rand_count;

    char *new_filename = pmd.filename;
    int rotation = 0;
    if (argc == MERGE_WITH_ROTATE_ARG_COUNT) {
        rotation = atoi(argv[4]);
        new_filename = argv[5];
    }

    bool print_random = false;
    if (argc == MERGE_RANDOM_ARG_COUNT) {
        new_filename = argv[4];
        print_random = true;
    }

    // Validate files exist and of the right size
    int valid_count = 0;
    for (int i = 0; i < total_count; i++) {
        char block_filename[256];
        sprintf(block_filename, "%s.%d", pmd.filename, i);
        FILE *block_fp = fopen(block_filename,"rb");

        if (block_fp == NULL) {
            printf("Cannot open '%s'\n", block_filename);
            exit(1);
        }

        struct stat fileInfo;
        fstat(fileno(block_fp), &fileInfo);

        fclose(block_fp);

        bool is_random = pmd.rand_positions & (1 << i);
        
        if (!is_random) {
            if (valid_count == pmd.split_count - 1) {
                if (fileInfo.st_size != pmd.last_block_size) {
                    printf("File '%s' is of incorrect size\n", block_filename);
                    exit(1);
                }
            } else {
                if (fileInfo.st_size != pmd.block_size) {
                    printf("File '%s' is of incorrect size\n", block_filename);
                    exit(1);
                }
            }

            valid_count++;
        } else {
            if (fileInfo.st_size != pmd.block_size) {
                printf("File '%s' is of incorrect size\n", block_filename);
                exit(1);
            }
        }
    }

    FILE *output_fp = fopen(new_filename,"wb");
    char *buffer = (char *)malloc(pmd.block_size);

    valid_count = 0;
    for (int i = 0; i < total_count; i++) {
        char block_filename[256];

        sprintf(block_filename, "%s.%d", pmd.filename, (i + rotation) % total_count);
        FILE *block_fp = fopen(block_filename,"rb");

        bool is_random = pmd.rand_positions & (1 << i);

        if (!is_random) {
            if (valid_count == pmd.split_count - 1) {
                fread(buffer, 1, pmd.last_block_size, block_fp);
                fwrite(buffer, 1, pmd.last_block_size, output_fp);
            } else {
                fread(buffer, 1, pmd.block_size, block_fp);
                fwrite(buffer, 1, pmd.block_size, output_fp);
            }

            valid_count++;
        } else if (is_random && print_random) {
            fread(buffer, 1, pmd.block_size, block_fp);
            fwrite(buffer, 1, pmd.block_size, output_fp);
        }

        fclose(block_fp);
    }

    fclose(output_fp);
    free(buffer);
}

int main(int argc, char *argv[])
{
    if (argc == PARTITION_RANDOM_ARG_COUNT && strcmp(argv[1], "-p") == 0 && strcmp(argv[4], "-R") == 0) {
        partition(argc, argv);
    } else if (argc == PARTITION_ARG_COUNT && strcmp(argv[1], "-p") == 0){
        partition(argc, argv);
    } else if (argc == MERGE_ARG_COUNT && strcmp(argv[1], "-m") == 0) {
        merge(argc, argv);
    } else if (argc == MERGE_WITH_ROTATE_ARG_COUNT && strcmp(argv[1], "-m") == 0 && strcmp(argv[3], "-r") == 0) {
        merge(argc, argv);
    } else if (argc == MERGE_RANDOM_ARG_COUNT && strcmp(argv[1], "-m") == 0 && strcmp(argv[3], "-R") == 0) {
        merge(argc, argv);
    } else {
        printf("Usage: %s -p <filename> <count>\n", argv[0]);
        printf("Usage: %s -p <filename> <count> -R <rand_count>\n", argv[0]);
        printf("Usage: %s -m <filename>\n", argv[0]);
        printf("Usage: %s -m <filename> -r <rotate_count> <new_filename>\n", argv[0]);
        printf("Usage: %s -m <filename> -R <new_filename>\n", argv[0]);
        exit(1);
    }
}
