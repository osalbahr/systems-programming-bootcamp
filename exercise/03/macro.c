#include <stdio.h>

#define BEGIN_FOR(first, second, third) for(first; second; third) {

#define END_FOR }

#define BEGIN_DO_WHILE do {
#define END_DO_WHILE(cond) } while(cond);

int main()
{
    BEGIN_FOR(int i = 0, i < 10, i++)
        printf("i = %d\n", i);
    END_FOR

    int j = 0;
    BEGIN_DO_WHILE
        printf("j = %d\n", j);
        j++;
    END_DO_WHILE(j < 10)
}
