#include "signal.h"
#include "scheduler.h"

void Kernel_Signal_Subscribe(Kernel_Signal const sign) {
    Kernel_Signal_Entry entry = Kernel_Signal_Vector[sign];

    for (uint8_t i = 0; i < sizeof(entry.subscribers); i++) {
        if (entry.subscribers[i] == Kernel_Scheduler_Current->pid) {
            return;
        }
    }
}

void Kernel_Signal_Unsubscribe(Kernel_Signal const sign) {
}

void Kernel_Signal_Send(Kernel_Signal const sign) {
}

void Kernel_Signal_Unsend(Kernel_Signal const sign) {
}
