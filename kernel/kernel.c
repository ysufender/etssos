#include "kernel.h"

#include "../drivers/gpio/gpio.h"
#include "../drivers/uart/uart.h"
#include "../drivers/timer/timer.h"
#include "../config/etssos_config.h"

void Kernel_Main(void) {
    GPIO_Init();
    Timer_Init();
    UART_Init();
    UART_PutStringLine("UART Initialization successful.");
    Kernel_DumpInfo();

    GPIO_Enable(2, 1);
    GPIO_SetMode(2, GPIO_Mode_Output);

    while (1) {
        GPIO_Write(2, 1);
        Timer_Delay(1000);
        GPIO_Write(2, 0);
        Timer_Delay(1000);
    }
}

void Kernel_DumpInfo(void) {
    UART_PutStringLine("Kernel Info:");
    UART_PrintFormat("Name     : %s\n", ETSSOS_NAME);
    UART_PrintFormat("Version  : %s\n", ETSSOS_VERSION);
    UART_PrintFormat("Compiler : %s\n", ETSSOS_CC);
    UART_PrintFormat("CFLAGS   : %s\n", ETSSOS_CFLAGS);
    UART_PrintFormat("Linker   : %s\n", ETSSOS_LD);
    UART_PrintFormat("LDFLAGS  : %s\n", ETSSOS_LDFLAGS);
    UART_PrintFormat("Assembler: %s\n", ETSSOS_AS);
    UART_PrintFormat("ASFLAGS  : %s\n", ETSSOS_ASFLAGS);
    UART_PrintFormat("Burner   : %s\n", ETSSOS_BURNER);
    UART_PrintFormat("BAUD     : %u\n", ETSSOS_BAUD);
    UART_PrintFormat("Board    : %s\n", ETSSOS_BOARD);
    UART_PrintFormat("UART CLK : %u\n", UART0_CLK_FREQ);
}

void Kernel_Panic_Unreachable(uintptr_t const addr) {
    UART_PutStringLine("Kernel reached unreachable code.");
    UART_PutStringLine("Entering fault loop.");
    while (1);
}
