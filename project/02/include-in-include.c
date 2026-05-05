#include <stdio.h>

#define RUN_A
#define RUN_B

int main()
{
    #include "include-in-include.a.c"
    return 0;
}
