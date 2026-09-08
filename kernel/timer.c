#include "timer.h"

#include "../drivers/timer/timer.h"

static Kernel_Timer_Timer Kernel_Timer_SoftwareTimers[] = {
};
#define Kernel_Timer_SoftwareTimers_Count (sizeof(Kernel_Timer_SoftwareTimers) / sizeof(Kernel_Timer_Timer))

void Kernel_Timer_FRC1_Interrupt_Handler(void) {
    for (uint32_t i = 0; i < Kernel_Timer_SoftwareTimers_Count; i++) {
        Kernel_Timer_Timer* const timer = &Kernel_Timer_SoftwareTimers[i];
        timer->tick++;
        if (timer->active) {
            uint32_t const div = timer->tick / timer->divider;
            timer->counter += div;
            timer->tick &= ~(div);
        }
    }
}

void Kernel_Timer_FRC2_Interrupt_Handler(void) {
}

void Kernel_Timer_Init(void) {
    Drivers_Timer_Init();
}
