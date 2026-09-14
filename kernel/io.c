#include <stdarg.h>

#include "io.h"
#include "mutex.h"
#include "interrupt.h"

#include "../drivers/uart/uart.h"
#include "task.h"

static Kernel_Mutex    Kernel_IO_Mutex = Kernel_Mutex_Default;

void Kernel_IO_printInt(uint32_t const num) {
    uint32_t tmp = num;
    uint32_t digitCount = 0;
    while (tmp != 0) {
        tmp = tmp / 10;
        digitCount = digitCount + 1;
    }

    if (digitCount == 0) {
        Kernel_IO_PutChar('0');
        return;
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

    Kernel_IO_PutString(result);
}

void Kernel_IO_printHexDigit(uint8_t const hex) {
    uint8_t const low  = hex & 0x0F,
                  high = (hex & 0xF0) >> 4;

    char const hchar = (high >= 10)
                     ? 'A' + (high - 10)
                     : '0' + high,
               lchar = (low>= 10)
                     ? 'A' + (low- 10)
                     : '0' + low;
    
    Kernel_IO_PutChar(hchar);
    Kernel_IO_PutChar(lchar);
}

void Kernel_IO_printHex(uint32_t const num) {
    Kernel_IO_PutString("0x");

    uint8_t const* const bytes = (uint8_t*)&num;

    Kernel_IO_printHexDigit(bytes[0]);
    Kernel_IO_printHexDigit(bytes[1]);
    Kernel_IO_printHexDigit(bytes[2]);
    Kernel_IO_printHexDigit(bytes[3]);
}

void Kernel_IO_PrintFormat(char const* const fmt, ...) {
    Kernel_Mutex_Lock(&Kernel_IO_Mutex);

    va_list args;

    va_start(args, fmt);
    uint8_t escaping = 0;
    for (int i = 0; fmt[i] != '\0'; i++) {
        switch (fmt[i]) {
            case '%':
                if (escaping) {
                    Kernel_IO_PutChar('%');
                    escaping = 0;
                }
                else { escaping = 1; }
                break;

            case 'u':
                if (escaping) {
                    uint32_t const unsign = va_arg(args, uint32_t);
                    Kernel_IO_printInt(unsign);
                    escaping = 0;
                    break;
                }
                __attribute__((fallthrough));
            
            case 'd':
                if (escaping) {
                    int32_t const sign = va_arg(args, int32_t);
                    if (sign < 0) { Kernel_IO_PutChar('-'); }
                    Kernel_IO_printInt(sign < 0 ? -sign : sign);
                    escaping = 0;
                    break;
                }
                __attribute__((fallthrough));

            case 's':
                if (escaping) {
                    char const* const str = va_arg(args, char const*);
                    Kernel_IO_PutString(str);
                    escaping = 0;
                    break;
                }
                __attribute__((fallthrough));

            case 'x':
                if (escaping) {
                    uint32_t const integer = va_arg(args, uint32_t);
                    Kernel_IO_printHex(integer);
                    escaping = 0;
                    break;
                }
                __attribute__((fallthrough));

            default:
                Kernel_IO_PutChar(fmt[i]);
                break;
        }
    }

    va_end(args);

    Kernel_Mutex_Unlock(&Kernel_IO_Mutex);
}

void Kernel_IO_PutString(char const* const str) {
    Kernel_Mutex_Lock(&Kernel_IO_Mutex);
    for (uint32_t i = 0; str[i] != '\0'; i++) {
        Kernel_IO_PutChar(str[i]);
    }
    Kernel_Mutex_Unlock(&Kernel_IO_Mutex);
}

void Kernel_IO_PutStringLine(char const* const str) {
    Kernel_Mutex_Lock(&Kernel_IO_Mutex);
    for (uint32_t i = 0; str[i] != '\0'; i++) {
        Kernel_IO_PutChar(str[i]);
    }
    Kernel_IO_PutChar('\n');
    Kernel_Mutex_Unlock(&Kernel_IO_Mutex);
}

void Kernel_IO_PutChar(char const ch) {
    Drivers_UART_PutChar(ch);
}

uint8_t Kernel_IO_GetChar(void) {
    uint8_t ch;
    while (!Drivers_UART_GetChar(&ch)) Kernel_Task_Yield();
    return ch;
}

void Kernel_IO_GetString(char* const buf, uint32_t const max) {
    uint32_t i = 0;
    for (; i < max - 1; i++) {
        char const ch = Kernel_IO_GetChar();
        if (ch == '\n' || ch == '\r') break;
        buf[i] = ch;
    }
    buf[i] = '\0';
}

void Kernel_IO_Flush(void) {
    Drivers_UART_ExhaustOutput();
}

void Kernel_IO_Init(void) {
    Drivers_UART_Init();
    Kernel_Interrupt_Register(KERNEL_INTERRUPT_SOURCE_UART, Drivers_UART_Interrupt);
}
