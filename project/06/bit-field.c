#include <stdio.h>

typedef struct Match {
    // 00 -> tie
    // 01 -> team A
    // 10 -> team B
    unsigned char winner:2;
    // 01 -> team A
    // 10 -> team B
    unsigned char home:2;
} Match;

void print_match(Match *m)
{
    switch (m->winner) {
        case 0b00:
            printf("The game tied. ");
            break;
        case 0b01:
            printf("Team A won. ");
            break;
        case 0b10:
            printf("Team B won. ");
            break;
    }

    switch (m->home) {
        case 0b01:
            printf("On Team A's home.\n");
            break;
        case 0b10:
            printf("On Team B's home.\n");
            break;
    }
}

int main()
{
    unsigned char match_char = 0b0101;
    Match *m = (Match *)&match_char;

    print_match(m);
}
