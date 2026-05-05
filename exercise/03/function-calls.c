#include <stdio.h>

unsigned int byte_pack( unsigned char a,
                        unsigned char b,
                        unsigned char c,
                        unsigned char d)
{
    unsigned int result = 0;
    result |= a;
    result |= b << 8;
    result |= c << (8 * 2);
    result |= d << (8 * 3);

    return result;
}

int compare_nybble(unsigned char value)
{
    /*
        low nybble == high nybble -> 0
        low nybble > high nybble -> 1
        low nybble < high nybble -> -1
    */

    unsigned char low_nybble = value & 0xF;
    unsigned char high_nybble = (value & 0xF0) >> 4;

    if (low_nybble == high_nybble) {
        return 0;
    } else if (low_nybble > high_nybble) {
        return 1;
    } else { // low_nybble < high_nybble
        return -1;
    }
}

int is_odd(unsigned char value)
{
    return value & 1;
}

int main()
{
    unsigned char value = 99;
    int result = is_odd(value);
    if (result) {
        puts("ODD");
    } else {
        puts("EVEN");
    }

    /* compare nybble */
    printf("0xFF -> %d\n", compare_nybble(0xFF));
    printf("0x1C -> %d\n", compare_nybble(0x1C));
    printf("0xE2 -> %d\n", compare_nybble(0xE2));

    /* pack */
    unsigned int packed = byte_pack(0x12, 0x34, 0x56, 0x78);
    printf("Packed = 0x%x\n", packed);
}
