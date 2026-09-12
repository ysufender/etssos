#include "timer.h"

#include "../drivers/timer/timer.h"

static Kernel_Timer Kernel_Timer_SoftwareTimers[KERNEL_TIMER_COUNT]  = {0};

void Kernel_Timer_FRC1_Interrupt_Handler(void) {
    for (uint32_t i = 0; i < KERNEL_TIMER_COUNT; i++) {
        Kernel_Timer* const timer = &Kernel_Timer_SoftwareTimers[i];
        if (!(timer->flags & KERNEL_TIMER_FLAGS_ACTIVE)) continue;

        timer->tick++;
        if (timer->tick < timer->divider) {
            continue;
        }

        timer->tick = 0;
        timer->counter++;

        if (timer->counter >= timer->alarm && timer->callback) {
            timer->counter = 0;
            timer->tick = 0;
            if (!(timer->flags & KERNEL_TIMER_FLAGS_RELOAD)) {
                timer->flags &= ~KERNEL_TIMER_FLAGS_ACTIVE;
            }
            timer->callback();
        }
    }
}

void Kernel_Timer_Init(void) {
    Drivers_Timer_Init();
}

Kernel_Timer* Kernel_Timer_Create(Kernel_Timer_Mode     const mode,
                                  uint32_t              const alarm,
                                  Kernel_Timer_Callback const callback) {
    uint32_t index = 0;
    for (; index < KERNEL_TIMER_COUNT; index++) {
        if (Kernel_Timer_SoftwareTimers[index].flags & KERNEL_TIMER_FLAGS_ENABLED) {
            continue;
        }
        break;
    }

    if (index >= KERNEL_TIMER_COUNT) {
        __asm__ volatile ( "ill" );
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

    Kernel_Timer* const timer = &Kernel_Timer_SoftwareTimers[index];
    timer->flags |= KERNEL_TIMER_FLAGS_ENABLED;
    return timer;
}
