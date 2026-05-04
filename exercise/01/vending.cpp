#include <cstdio>

typedef unsigned char byte;

int main()
{
    int order;
    printf("order = ");
    scanf("%d", &order);

    byte D = order & 0b11;
    bool C = order & 0b100;
    bool S1 = order & 0b1000;
    byte S2 = (order & 0b110000) >> 4;
    bool M = order & 0b1000000;
    bool I = order & 0b10000000;

    switch (D) {
        case 0b00:
            puts("Tea");
            break;
        case 0b01:
            puts("Coffee");
            break;
        case 0b10:
            puts("Water");
            break;
        case 0b11:
            puts("Mint");
            break;
    }

    switch (C) {
        case false:
            puts("Cold");
            break;
        case true:
            puts("Hot");
            break;
    }

    switch (S1) {
        case false:
            puts("Small");
            break;
        case true:
            puts("Large");
            break;
    }

    switch (S2) {
        case 0b00:
            puts("No sugar");
            break;
        case 0b01:
            puts("Low sugar");
            break;
        case 0b10:
            puts("Medium sugar");
            break;
        case 0b11:
            puts("High sugar");
            break;
    }

    switch (M) {
        case false:
            puts("No milk");
            break;
        case true:
            puts("With milk");
            break;
    }

    switch (M) {
        case false:
            puts("With ice");
            break;
        case true:
            puts("No ice");
            break;
    }

    puts("I M S2 S1 C D");
    printf("%d %d %02d %d  %d %02d\n", I, M, S2, S1, C, D);
}
