#include "protector.h"

#include "../kernel/task.h"
#include "../kernel/signal.h"

void OS_Protector(void) {
    static void* handlers[] = {
        &&segfault,
        &&abort,
        &&trap,
        &&fault
    };

    for (uint8_t sign = 0; sign < Kernel_Signal_User; sign++) {
        Kernel_Signal_Subscribe(sign);
    }

    while (1) {
        for (uint8_t sign = 0; sign < Kernel_Signal_User; sign++) {
            if (Kernel_Signal_Up(sign)) {
                goto *handlers[sign];
            }
            continue;

segfault:
            Kernel_IO_PrintFormat("SIGSEGV in %s\n", Kernel_Task_Pool[Kernel_Signal_Vector[sign].sender].name);
            goto common;
abort:
            Kernel_IO_PrintFormat("SIGABRT in %s\n", Kernel_Task_Pool[Kernel_Signal_Vector[sign].sender].name);
            goto common;
trap:
            Kernel_IO_PrintFormat("SIGTRAP in %s\n", Kernel_Task_Pool[Kernel_Signal_Vector[sign].sender].name);
            goto common;
fault:
            Kernel_IO_PrintFormat("General fault in %s\n", Kernel_Task_Pool[Kernel_Signal_Vector[sign].sender].name);
            goto common;
common:
            Kernel_Task_Kill(Kernel_Signal_Vector[sign].sender);
            Kernel_Signal_Unsend(sign);
        }
    }
}
