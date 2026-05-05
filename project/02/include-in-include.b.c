for (int i = 0; i < 3; i++) {
#ifdef RUN_A
    printf("result = %d\n", (i * y));
#else
    printf("result = %d\n", i);
#endif
}
