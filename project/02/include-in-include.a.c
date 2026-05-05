#ifdef RUN_A
for (int y = 0; y < 3; y++) {
    printf("y: %d\n", y);
#ifdef RUN_B
    #include "include-in-include.b.c"
#endif
}
#else
#include "include-in-include.b.c"
#endif
