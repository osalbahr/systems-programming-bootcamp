#include <stdio.h>

int main()
{
    int value = 10;
    int *ptr = &value;

    // value -> &value
    // ptr -> *ptr

    printf("value: %d, address: %p\n", value, ptr);
    printf("value: %d, address: %p\n", *ptr, &value);
}
