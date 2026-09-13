#include "mutex.h"

#include "interrupt.h"
#include "scheduler.h"
#include "task.h"

void Kernel_Mutex_Lock(Kernel_Mutex* const mutex) {
    uint32_t const ps = Kernel_Interrupt_Disable();

    if (mutex->owner == 0) {
        mutex->owner = Kernel_Scheduler_Current;

        Kernel_Interrupt_Restore(ps);
        return;
    }

    Kernel_Mutex_TaskQueue node = {
        .head = Kernel_Scheduler_Current,
        .tail = 0
    };

    if (mutex->waiters == 0) {
        mutex->waiters = &node;
    }
    else {
        Kernel_Mutex_TaskQueue* tail = mutex->waiters;

        while (tail->tail != 0) {
            tail = tail->tail;
        }

        tail->tail = &node;
    }

    Kernel_Interrupt_Restore(ps);

    while (mutex->owner != Kernel_Scheduler_Current) Kernel_Task_Yield();
}

void Kernel_Mutex_Unlock(Kernel_Mutex* const mutex) {
    uint32_t const ps = Kernel_Interrupt_Disable();

    Kernel_Task* const current = Kernel_Scheduler_Current;

    if (mutex->owner != current) {
        Kernel_Interrupt_Restore(ps);
        return;
    }

    if (mutex->waiters == 0) {
        mutex->owner = 0;

        Kernel_Interrupt_Restore(ps);
        return;
    }

    Kernel_Mutex_TaskQueue* const node = mutex->waiters;
    mutex->waiters = node->tail;
    mutex->owner = node->head;

    Kernel_Interrupt_Restore(ps);
}
