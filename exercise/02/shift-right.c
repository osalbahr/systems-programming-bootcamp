#include <stdio.h>

int main()
{
    unsigned int x = 0x4D6A3FE2;

    for (int i = 0; i < 2; i++) {
        unsigned int temp = x >> 8;
        temp |= (x & 0xFF) << (32 - 8);
        x = temp;
    }

    printf("Value = %d\n", x);
}
