#include <stdio.h>

#define BYTE_SHL(value, o) ((value) << (o))
#define BYTE_SHR(value, o) ((value) >> (o))

#define BYTE_SWAP_NYBBLE(value) \
{ \
    unsigned char low_nybble = value & 0xF; \
    unsigned char high_nybble = BYTE_SHR(value & 0xF0, 4); \
    v = high_nybble | BYTE_SHL(low_nybble, 4); \
}

int main()
{
    unsigned char v = 0xC8;
    BYTE_SWAP_NYBBLE(v);
    printf("%X\n", v);
    BYTE_SWAP_NYBBLE(v);
    printf("%X\n", v);
}
