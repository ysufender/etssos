#include "interrupt.h"

#include "../drivers/uart/uart.h"
#include "../drivers/timer/timer.h"
#include "../drivers/gpio/gpio.h"

Kernel_Interrupt_Handler Kernel_Interrupt_RegistrationVector[KERNEL_INTERRUPT_COUNT] = { 0 };

void Kernel_Interrupt_Dispatch(void) {
    uint32_t const interrupts = Kernel_Interrupt_Read();

    for (uint32_t i = 0; i < KERNEL_INTERRUPT_COUNT; i++) {
        if (interrupts & (1 << i)) {
            Kernel_Interrupt_Clear(i);

            if (Kernel_Interrupt_RegistrationVector[i]) {
                Kernel_Interrupt_RegistrationVector[i]();
            }
        }
    }
}

void Kernel_Interrupt_Software_Dispatch(void) {
    Kernel_Interrupt_Clear(KERNEL_INTERRUPT_SOURCE_SOFT);
}

void Kernel_Interrupt_Init(void) {
    Kernel_Interrupt_Register(KERNEL_INTERRUPT_SOURCE_TIMER_FRC1, Drivers_Timer_FRC1_Interrupt_Handler);
    Kernel_Interrupt_Register(KERNEL_INTERRUPT_SOURCE_TIMER_FRC2, Drivers_Timer_FRC2_Interrupt_Handler);
    Kernel_Interrupt_Register(KERNEL_INTERRUPT_SOURCE_SOFT, Kernel_Interrupt_Software_Dispatch);

    Kernel_Interrupt_Activate(
        /* ( 1 << KERNEL_INTERRUPT_SOURCE_WDEV_FIQ) */
        /* | ( 1 << KERNEL_INTERRUPT_SOURCE_SLC) */
        /* | ( 1 << KERNEL_INTERRUPT_SOURCE_SPI) Causes Hang */
        /* | ( 1 << KERNEL_INTERRUPT_SOURCE_RTC) */
        /* | ( 1 << KERNEL_INTERRUPT_SOURCE_GPIO) */
        /* | ( 1 << KERNEL_INTERRUPT_SOURCE_UART) */
        /* | ( 1 << KERNEL_INTERRUPT_SOURCE_TICK) Causes Hang */
        ( 1 << KERNEL_INTERRUPT_SOURCE_SOFT)
        /* | ( 1 << KERNEL_INTERRUPT_SOURCE_WDT) */
        | ( 1 << KERNEL_INTERRUPT_SOURCE_TIMER_FRC1)
        | ( 1 << KERNEL_INTERRUPT_SOURCE_TIMER_FRC2)
    );

    __asm__ volatile (
        "rsil a2, 0"
        :
        :
        : "a2");
}
