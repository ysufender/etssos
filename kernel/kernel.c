#include "../drivers/uart/uart.h"

void kernel_main(void) {
    while (1) {
        UART_PutString("Hello World");
    }
}
