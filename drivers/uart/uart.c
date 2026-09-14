#include <stdarg.h>

#include "uart.h"

#include "../../libc/ringbuffer.h"

#include "../../config/etssos_config.h"
#include "../timer/timer.h"

static LibC_RingBuffer Drivers_UART0_TXBuf = LibC_RingBuffer_Default;
static LibC_RingBuffer Drivers_UART0_RXBuf = LibC_RingBuffer_Default;

void Drivers_UART_Init(void) {
    Drivers_UART_SetBaud(ETSSOS_BAUD);

    DRIVERS_UART0_CONF0 = (3 << 2) /* 8-bit bit num */
                        | (1 << 4) /* 1-bit stop */;

    DRIVERS_UART0_CONF1 = (20  << 8) /* TX FIFO empty threshold */
                        | (1   << 0) /* RX FIFO Full treshold */
                        | (119 << 24) /* RX Timeout */ ;

    DRIVERS_UART0_CONF0 |= (1 << 17) /* Reset RX FIFO */
                        |  (1 << 18); /* Reset TX FIFO */

    DRIVERS_UART0_CONF0 &= ~(1 << 17) /* Reset RX FIFO */
                        &  ~(1 << 18); /* Reset TX FIFO */


    Drivers_UART0_TXBuf = LibC_RingBuffer_Create(256);
    Drivers_UART0_RXBuf = LibC_RingBuffer_Create(256);
}

void Drivers_UART_SetBaud(uint32_t const baud) {
    Drivers_UART_ExhaustOutput();
    DRIVERS_UART0_CLKDIV = DRIVERS_TIMER_CLK_FREQ / baud;
}

void Drivers_UART_ExhaustOutput(void) {
    while (!LibC_RingBuffer_Empty(&Drivers_UART0_TXBuf));
    while (((DRIVERS_UART0_STATUS & DRIVERS_UART0_STATUS_TX_FIFO_CNT) >> 16)
            != 0);
}

void Drivers_UART_PutChar(uint8_t const ch) {
    while (!LibC_RingBuffer_Push(&Drivers_UART0_TXBuf, ch));
    DRIVERS_UART0_INT_ENA |= DRIVERS_UART0_INT_ENA_TX_FIFO_EMPTY;
}

uint8_t Drivers_UART_GetChar(uint8_t* const ch) {
    return LibC_RingBuffer_Pop(&Drivers_UART0_RXBuf, ch);
}

void Drivers_UART_TXInterrupt(void) {
    uint8_t byte;
    while (!LibC_RingBuffer_Empty(&Drivers_UART0_TXBuf)) {
        if (((DRIVERS_UART0_STATUS & DRIVERS_UART0_STATUS_TX_FIFO_CNT) >> 16) >= 127) break;
        LibC_RingBuffer_Pop(&Drivers_UART0_TXBuf, &byte);
        DRIVERS_UART0_FIFO = byte;
    }

    if (LibC_RingBuffer_Empty(&Drivers_UART0_TXBuf)) {
        DRIVERS_UART0_INT_ENA &= ~DRIVERS_UART0_INT_ENA_TX_FIFO_EMPTY;
    }

    DRIVERS_UART0_INT_CLR = DRIVERS_UART0_INT_CLR_TX_FIFO_EMPTY; }

void Drivers_UART_RXInterrupt(void) {
    while (((DRIVERS_UART0_STATUS & DRIVERS_UART0_STATUS_RX_FIFO_CNT) & 0xFF) > 0) {
        uint8_t const byte = DRIVERS_UART0_FIFO & 0xFF;
        LibC_RingBuffer_Push(&Drivers_UART0_RXBuf, byte);
    }

    DRIVERS_UART0_INT_CLR = DRIVERS_UART0_INT_CLR_RX_FIFO_FULL
                          | DRIVERS_UART0_INT_CLR_RX_FIFO_TOUT;
}

void Drivers_UART_Interrupt(void) {
    uint32_t const status = DRIVERS_UART0_INT_STA;

    if (status & DRIVERS_UART0_INT_ST_TX_FIFO_EMPTY) {
        Drivers_UART_TXInterrupt();
    }
    else if (status & (DRIVERS_UART0_INT_ST_RX_FIFO_FULL
                       | DRIVERS_UART0_INT_ST_RX_FIFO_TOUT)) {
        Drivers_UART_RXInterrupt();
    }
}
