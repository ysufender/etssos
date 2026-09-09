#include "timer.h"

#include "interrupt.h"

#include "../drivers/timer/timer.h"

static Kernel_Timer Kernel_Timer_SoftwareTimers[128]  = {0};
static uint32_t     Kernel_Timer_SoftwareTimers_Index = 0;
#define Kernel_Timer_SoftwareTimers_Count (sizeof(Kernel_Timer_SoftwareTimers) / sizeof(Kernel_Timer))

void Kernel_Timer_FRC1_Interrupt_Handler(void) {
    for (uint32_t i = 0; i < Kernel_Timer_SoftwareTimers_Count; i++) {
        Kernel_Timer* const timer = &Kernel_Timer_SoftwareTimers[i];
        if (timer->flags & KERNEL_TIMER_FLAGS_ACTIVE) {
            uint32_t const div = ++timer->tick / timer->divider;
            timer->counter += div;
            timer->tick &= ~(div);

            if (timer->counter >= timer->alarm && timer->callback) {
                if (!(timer->flags & KERNEL_TIMER_FLAGS_RELOAD)) {
                    timer->flags &= ~(KERNEL_TIMER_FLAGS_ACTIVE);
                }
                else {
                    timer->counter = 0;
                    timer->tick = 0;
                }
                timer->callback();
            }
        }
    }
}

void Kernel_Timer_Init(void) {
    Drivers_Timer_Init();

    Kernel_Timer* scheduler = Kernel_Timer_Create(Kernel_Timer_Mode_Milliseconds, 10, Kernel_Interrupt_Scheduled);
    scheduler->flags |= KERNEL_TIMER_FLAGS_RELOAD
                     |  KERNEL_TIMER_FLAGS_ACTIVE;
}

Kernel_Timer* Kernel_Timer_Create(Kernel_Timer_Mode     const mode,
                                  uint32_t              const alarm,
                                  Kernel_Timer_Callback const callback) {
    uint32_t index = 0;
    for (; index <= Kernel_Timer_SoftwareTimers_Index; index++) {
        if (Kernel_Timer_SoftwareTimers[index].flags & KERNEL_TIMER_FLAGS_ACTIVE) {
            continue;
        }

        if (index >= Kernel_Timer_SoftwareTimers_Count) {
            __asm__ volatile ( "ill" );
        }

        break;
    }

    Kernel_Timer_SoftwareTimers[index] = (Kernel_Timer){
        .counter  = 0,
        .divider  = (mode == Kernel_Timer_Mode_Milliseconds)
                  ? 1
                  : 1000,
        .flags    = 0,
        .tick     = 0,
        .alarm    = alarm,
        .callback = callback,
    };

    if (index == Kernel_Timer_SoftwareTimers_Index) {
        Kernel_Timer_SoftwareTimers_Index++;
    }

    return &Kernel_Timer_SoftwareTimers[index];
}
