// Note: this program assumes ARM64

#include <stdio.h>
#include <stdlib.h>

int values = 0x3b9dff;

int sum(int a, int b)
{
    return a + b + values;
}

int main()
{
    // 4-byte ARM64 instructions
    unsigned int *sum_code = (unsigned int *)sum;
    unsigned int code_size = 0;

    for (;;) {
        printf("%p -> 0x%02x\n", sum_code, *sum_code);
        code_size++;

        // ret
        if(*sum_code == 0xd65f03c0) break;

        sum_code++;
    }

    // Write the sum()'s raw bytes
    FILE *fp = fopen("sum.code", "wb");
    if (!fp) {
        printf("Could not open 'sum.code'\n");
        exit(1);
    }

    sum_code = (unsigned int *)sum;
    // 4-byte ARM64 instructions
    fwrite(sum_code, 4, code_size, fp);
    fclose(fp);

    printf("code size: %u\n", code_size);
}
