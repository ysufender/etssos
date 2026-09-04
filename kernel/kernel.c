volatile unsigned int testValue;

void kernel_main(void) {
    for (;;) {
        (void)testValue;
    }
}
