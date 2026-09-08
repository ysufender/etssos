#include "interrupt.h"

#include "../drivers/uart/uart.h"

Kernel_Interrupt_Handler Kernel_Interrupt_RegistrationVector[KERNEL_INTERRUPT_COUNT] = { 0 };

void Kernel_Interrupt_Dispatch_Software(void) {
    Drivers_UART_PutStringLine("YAY!");
}

void Kernel_Interrupt_Dispatch(void) {
    Kernel_Interrupt_Clear(0xFFFFFFFF);
    Drivers_UART_PutStringLine("WAYY!");
}

void Kernel_Interrupt_Init(void) {
    Kernel_Interrupt_Register(KERNEL_INTERRUPT_SOURCE_SOFT, Kernel_Interrupt_Dispatch_Software);
    Kernel_Interrupt_Activate(
        ( 1 << KERNEL_INTERRUPT_SOURCE_WDEV_FIQ)
        | ( 1 << KERNEL_INTERRUPT_SOURCE_SLC)
        | ( 1 << KERNEL_INTERRUPT_SOURCE_SPI)
        | ( 1 << KERNEL_INTERRUPT_SOURCE_RTC)
        | ( 1 << KERNEL_INTERRUPT_SOURCE_GPIO)
        | ( 1 << KERNEL_INTERRUPT_SOURCE_UART)
        | ( 1 << KERNEL_INTERRUPT_SOURCE_TICK)
        | ( 1 << KERNEL_INTERRUPT_SOURCE_SOFT)
        | ( 1 << KERNEL_INTERRUPT_SOURCE_WDT)
        | ( 1 << KERNEL_INTERRUPT_SOURCE_TIMER_FRC1)
        | ( 1 << KERNEL_INTERRUPT_SOURCE_TIMER_FRC2)
    );

    __asm__ volatile (
        "rsil a2, 0"
        :
        :
        : "a2");
}
