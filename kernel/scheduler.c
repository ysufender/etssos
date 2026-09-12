#include "scheduler.h"

#include "task.h"
#include "timer.h"

volatile Kernel_Task* Kernel_Scheduler_Current;
volatile uint8_t      Kernel_Scheduler_Switched = 0;

static Kernel_Timer* Kernel_Scheduler_Timer;

void Kernel_Scheduler_Init(void) {
    Kernel_Scheduler_Timer = Kernel_Timer_Create(Kernel_Timer_Mode_Milliseconds, 10, Kernel_Scheduler_Tick);
    Kernel_Scheduler_Timer->flags = KERNEL_TIMER_FLAGS_RELOAD
                                  | KERNEL_TIMER_FLAGS_ACTIVE;
    Kernel_Scheduler_Current = 0;
}

void Kernel_Scheduler_Tick(void) {
    Kernel_Task* next     = 0;
    uint8_t      priority = 0;

    for (uint8_t i = 0; i < Kernel_Task_Count; i++) {
        Kernel_Task* const task = &Kernel_Task_Pool[i];
        if (task->state == KERNEL_TASK_READY && task->priority >= priority) {
            priority = task->priority;
            next = task;
        }
    }

    if (next) {
        if (Kernel_Scheduler_Current) {
            Kernel_Scheduler_Current->state = KERNEL_TASK_READY;
        }

        if (next != Kernel_Scheduler_Current) {
            Kernel_Scheduler_Switched = 1;
            next->state = KERNEL_TASK_RUNNING;
            Kernel_Scheduler_Current = next;
        }
    }
}
