#include <stdio.h>

int main()
{
    unsigned char byte = 0x7e;
    unsigned short word = 0x54f2;
    
    int word_bit_count = 0;

    for (int i = 0; i < 16; i++) {
        if (word & (1 << i)) {
            word_bit_count++;
        }
    }

    printf("Count = %d\n", word_bit_count);
}
