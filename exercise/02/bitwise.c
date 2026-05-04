#include <stdio.h>

int main()
{
    unsigned char byte = 0x4e;
    unsigned short word = 0x3cfa;
    unsigned int dword = 0; // target = 0x04 3c af e0

    // 0x04 00 00 00
    dword |= (byte & 0xF0) << 20;

    // 0x04 00 00 e0
    dword |= (byte & 0xF) << 4;

    // 0x04 3c 00 e0
    dword |= (word & 0xFF00) << 8;

    // 0x04 3c a0 e0
    dword |= (word & 0xF) << 12;

    // 0x04 3c af e0
    dword |= (word & 0xF0) << 4;
}
