#include "interrupt.h"

static Kernel_Interrupt_Handler Kernel_Interrupt_Handler_Table[KERNEL_INTERRUPT_COUNT + 1] = { 0 };

#define Kernel_Interrupt_Count (sizeof(Kernel_Interrupt_Handler_Table) / sizeof(Kernel_Interrupt_Handler)) 

void Kernel_Interrupt_Register(KERNEL_INTERRUPT_SOURCE const src, Kernel_Interrupt_Handler const handler) {
    if (src >= Kernel_Interrupt_Count) {
        return;
    }

    Kernel_Interrupt_Handler_Table[src] = handler;
}

void Kernel_Interrupt_Dispatch(void) {
    uint16_t pending;
    __asm__ volatile (
            "rsr.interrupt %0"
            : "=a" (pending));

    for (uint8_t i = 0; i < Kernel_Interrupt_Count; i++) {
        if (pending & (1 << i)) {
            Kernel_Interrupt_Handler_Table[i]();
        }
    }
}
