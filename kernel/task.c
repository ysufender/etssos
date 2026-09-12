#include "task.h"

#include "error.h"
#include "scheduler.h"

Kernel_Task Kernel_Task_Pool[KERNEL_TASK_MAX_COUNT] = { 0 };
uint8_t     Kernel_Task_Count                       = 0;

static uint32_t Kernel_Task_Stacks[KERNEL_TASK_MAX_COUNT][KERNEL_TASK_STACK_SIZE / 4] = {0};

Kernel_Task* Kernel_Task_Create(char const*       const name,
                                Kernel_Task_Entry const callback,
                                uint8_t           const priority) {
    if (Kernel_Task_Count >= KERNEL_TASK_MAX_COUNT) {
        THROW(Kernel_Error_StackOverflow); 
    }

    uint32_t *const stop  = &Kernel_Task_Stacks[Kernel_Task_Count - 1][KERNEL_TASK_STACK_SIZE / 4],
             *const frame = stop - 15;

    frame[0]  = (uint32_t)(uintptr_t)callback;
    for (uint8_t i = 1; i <= 12; i++) frame[i] = 0;
    frame[13] = (uint32_t)(uintptr_t)callback;
    frame[14] = 0;

    Kernel_Task* const task = &Kernel_Task_Pool[Kernel_Task_Count];
    task->sp        = frame;
    task->bp        = Kernel_Task_Stacks[Kernel_Task_Count++];
    task->stackSize = KERNEL_TASK_STACK_SIZE;
    task->wakeTick  = 0;
    task->priority  = priority;
    task->state     = KERNEL_TASK_READY;
    task->name[15]  = '\0';
    for (uint8_t i = 0; name[i] && i < 15; i++) {
        task->name[i] = name[i];
    }

    return task;
}

void __attribute__((noreturn)) Kernel_Task_Terminate(volatile Kernel_Task* const task) {
    task->state = KERNEL_TASK_TERMINATED;
    Kernel_Scheduler_Tick();
    Kernel_Task_Idle();
}

void __attribute__((noreturn)) Kernel_Task_Idle(void) {
    while (1) {
        __asm__ volatile ( "waiti 0" );;
    }
}
