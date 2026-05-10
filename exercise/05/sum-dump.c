#include <stdio.h>
#include <stdlib.h>

int values = 0x3b9dff;

int sum(int a, int b)
{
    return a + b + values;
}

int main()
{
    unsigned char *sum_code = (unsigned char *)sum;
    unsigned int code_size = 0;

    // raw function
    FILE *fp = fopen("sum.code", "wb");

    if (!fp) {
        printf("Could not open 'sum.code'\n");
        exit(1);
    }

    for (;;) {
        printf("%p -> %02x\n", sum_code, *sum_code);
        code_size++;
        
        fwrite(sum_code, 1, 1, fp);

        if(*sum_code == 0xc3) break;
        sum_code++;
    }

    fclose(fp);

    printf("code size: %u\n", code_size);
}
