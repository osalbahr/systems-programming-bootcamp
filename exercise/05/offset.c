#include <stdio.h>

int main()
{
    unsigned short values[5] = {
        0x22ff, 0xabcd, 0xeefb,
        0xcef3, 0x8b8d
    };

    unsigned char *ptr = (unsigned char *)values;
    for (int i = 0; i < 5; i++) {
        printf("%x\n", *(ptr + 1));
        ptr += 2;
    }

    puts("--");

    ptr = (unsigned char *)values;
    for (int i = 0; i < 5; i++) {
        printf("%x\n", *ptr);
        ptr += 2;
    }
}
