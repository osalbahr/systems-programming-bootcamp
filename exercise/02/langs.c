#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Usage: %s lang1 lang2\n", argv[0]);
        return 1;
    }

    printf("Languages: %s %s\n", argv[1], argv[2]);
}
