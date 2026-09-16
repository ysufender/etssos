#include "signal.h"

#include "scheduler.h"
#include "task.h"

Kernel_Signal_Entry Kernel_Signal_Vector[64] = {0};

void Kernel_Signal_Subscribe(Kernel_Signal const sign) {
    Kernel_Signal_Entry* entry = &Kernel_Signal_Vector[sign];

    for (uint8_t i = 0; i < sizeof(entry->subscribers); i++) {
        if (entry->subscribers[i] == Kernel_Scheduler_Current->pid) {
            return;
        }
    }

    uint8_t index = 0;
    for (; entry->subscribers[index] && index < sizeof(entry->subscribers); index++);

    entry->subscribers[index] = Kernel_Scheduler_Current->pid;
}

void Kernel_Signal_Unsubscribe(Kernel_Signal const sign) {
    Kernel_Signal_Entry* entry = &Kernel_Signal_Vector[sign];

    for (uint8_t i = 0; i < sizeof(entry->subscribers); i++) {
        if (entry->subscribers[i] == Kernel_Scheduler_Current->pid) {
            entry->subscribers[i] = 0;
            return;
        }
    }
}

void Kernel_Signal_Send(Kernel_Signal const sign) {
    Kernel_Signal_Vector[sign].active = 1;
}

void Kernel_Signal_Unsend(Kernel_Signal const sign) {
    Kernel_Signal_Vector[sign].active = 0;
}

uint8_t Kernel_Signal_Await(Kernel_Signal const sign) {
    Kernel_Signal_Entry* entry = &Kernel_Signal_Vector[sign];
    uint8_t subscribed = 0;

    for (uint8_t i = 0; i < sizeof(entry->subscribers); i++) {
        if (entry->subscribers[i] == Kernel_Scheduler_Current->pid) {
            subscribed = 1;
            break;
        }
    }

    while (subscribed && !Kernel_Signal_Vector[sign].active) Kernel_Task_Yield();

    return subscribed;
}
