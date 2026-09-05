#include "uart.h"

#include "../../config/etssos_config.h"

void UART_Init() {
    UART0_CLKDIV_REG = (UART_CLK_FREQ / ETSSOS_BAUD);

    UART0_CONF0 = (3 << 2) /* 8-bit bit num */
                  | (1 << 4) /* 1-bit stop */;

    UART0_CONF0 |= (1 << 17) /* Reset RX FIFO */
                  | (1 << 18); /* Reset TX FIFO */

    UART0_CONF0 &= ~(1 << 17) /* Reset RX FIFO */
                  & ~(1 << 18); /* Reset TX FIFO */
}

void UART_PutChar(uint8_t const ch) {
    while (((UART0_STATUS & UART0_STATUS_TX_FIFO_CNT) >> 16) >= UART0_DATAC);
    UART0_FIFO = ch;
}

void UART_PutString(char const* const str) {
    for (int i = 0; str[i] != '\0'; i++) {
        UART_PutChar(str[i]);
    }
}
