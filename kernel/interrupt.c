#include "interrupt.h"

#include "timer.h"
#include "io.h"

Kernel_Interrupt_Handler Kernel_Interrupt_RegistrationVector[KERNEL_INTERRUPT_COUNT] = { 0 };

void Kernel_Interrupt_Dispatch(void) {
    uint32_t const ps = Kernel_Interrupt_Disable();

    uint32_t const interrupts = Kernel_Interrupt_Read();

    for (uint32_t i = 0; i < KERNEL_INTERRUPT_COUNT; i++) {
        if (interrupts & (1 << i)) {
            Kernel_Interrupt_Clear(i);

            if (Kernel_Interrupt_RegistrationVector[i]) {
                Kernel_Interrupt_RegistrationVector[i]();
            }
        }
    }

    Kernel_Interrupt_Restore(ps);
}

void Kernel_Interrupt_Software_Dispatch(void) {
    uint32_t interruptMode, parameter;
    __asm__ volatile (
        "mov %0, a2\n"
        "mov %1, a3"
        : "=a" (interruptMode),
          "=a" (parameter));

    switch (interruptMode) {
        case 0: /* Error */
            Kernel_IO_PrintFormat("Error: %u", parameter);
            __asm__ volatile ( "ill" );
            while (1);
    }
}

void Kernel_Interrupt_Init(void) {
    Kernel_Interrupt_Register(KERNEL_INTERRUPT_SOURCE_TIMER_FRC1, Kernel_Timer_FRC1_Interrupt_Handler);
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

    /* NonosSDK had this */
    DPORT0_EDGE_INT_ENA |= (1 << 1);

    __asm__ volatile (
        "rsil a2, 0"
        :
        :
        : "a2");
}
