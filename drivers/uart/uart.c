#include <stdarg.h>

#include "uart.h"
#include "../../config/etssos_config.h"
#include "../timer/timer.h"

void Drivers_UART_Init(void) {
    Drivers_UART_SetBaud(ETSSOS_BAUD);

    DRIVERS_UART0_CONF0 = (3 << 2) /* 8-bit bit num */
                  | (1 << 4) /* 1-bit stop */;

    DRIVERS_UART0_CONF0 |= (1 << 17) /* Reset RX FIFO */
                  | (1 << 18); /* Reset TX FIFO */

    DRIVERS_UART0_CONF0 &= ~(1 << 17) /* Reset RX FIFO */
                  & ~(1 << 18); /* Reset TX FIFO */
}

void Drivers_UART_SetBaud(uint32_t const baud) {
    Drivers_UART_ExhaustOutput();
    DRIVERS_UART0_CLKDIV = DRIVERS_TIMER_CLK_FREQ / baud;
}

void Drivers_UART_ExhaustOutput(void) {
    while (((DRIVERS_UART0_STATUS & DRIVERS_UART0_STATUS_TX_FIFO_CNT) >> 16) != 0);
}

void Drivers_UART_PutChar(uint8_t const ch) {
    while (((DRIVERS_UART0_STATUS & DRIVERS_UART0_STATUS_TX_FIFO_CNT) >> 16) >= DRIVERS_UART0_DATAC);
    DRIVERS_UART0_FIFO = ch;
}
