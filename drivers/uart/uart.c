#include <stdarg.h>

#include "uart.h"
#include "../timer/timer.h"
#include "../../config/etssos_config.h"

volatile uint32_t DRIVERS_UART0_CLK_FREQ;

void Drivers_UART_DetectClock(void) {
    uint32_t const div = DRIVERS_UART0_CLKDIV & 0x000FFFFF;
    *(uint32_t*)(&DRIVERS_UART0_CLK_FREQ) = 74880 * div;
}

void Drivers_UART_Init(void) {
    Drivers_UART_DetectClock();
    Drivers_Timer_Delay(1000);
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
    DRIVERS_UART0_CLKDIV = DRIVERS_UART0_CLK_FREQ / baud;
}

void Drivers_UART_ExhaustOutput(void) {
    while (((DRIVERS_UART0_STATUS & DRIVERS_UART0_STATUS_TX_FIFO_CNT) >> 16) != 0);
}

void Drivers_UART_PutChar(uint8_t const ch) {
    while (((DRIVERS_UART0_STATUS & DRIVERS_UART0_STATUS_TX_FIFO_CNT) >> 16) >= DRIVERS_UART0_DATAC);
    DRIVERS_UART0_FIFO = ch;
}

void Drivers_UART_PutString(char const* const str) {
    for (int i = 0; str[i] != '\0'; i++) {
        Drivers_UART_PutChar(str[i]);
    }
}

void Drivers_UART_PutStringLine(char const* const str) {
    Drivers_UART_PutString(str);
    Drivers_UART_PutChar('\n');
}

void Drivers_UART_printInt(uint32_t const num) {
    uint32_t tmp = num;
    uint32_t digitCount = 0;
    while (tmp != 0) {
        tmp = tmp / 10;
        digitCount = digitCount + 1;
    }

    char result[11];

    tmp = num;
    uint32_t index = digitCount;
    while (index > 0) {
        result[index - 1] = '0' + tmp % 10;
        tmp = tmp / 10;
        index = index - 1;
    }
    result[digitCount] = '\0';

    Drivers_UART_PutString(result);
}

void Drivers_UART_PrintFormat(char const* const fmt, ...) {
    va_list args;

    va_start(args, fmt);
    uint8_t escaping = 0;
    for (int i = 0; fmt[i] != '\0'; i++) {
        switch (fmt[i]) {
            case '%':
                if (escaping) {
                    Drivers_UART_PutChar('%');
                    escaping = 0;
                }
                else { escaping = 1; }
                break;

            case 'u':
                if (escaping) {
                    uint32_t const unsign = va_arg(args, uint32_t);
                    Drivers_UART_printInt(unsign);
                    escaping = 0;
                    break;
                }
            
            case 'd':
                if (escaping) {
                    int32_t const sign = va_arg(args, int32_t);
                    if (sign < 0) { Drivers_UART_PutChar('-'); }
                    Drivers_UART_printInt(sign < 0 ? -sign : sign);
                    escaping = 0;
                    break;
                }

            case 's':
                if (escaping) {
                    char const* const str = va_arg(args, char const*);
                    Drivers_UART_PutString(str);
                    escaping = 0;
                    break;
                }

            default:
                Drivers_UART_PutChar(fmt[i]);
                break;
        }
    }

    va_end(args);
}
