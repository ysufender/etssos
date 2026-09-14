#include "../kernel/task.h"
#include "../kernel/scheduler.h"
#include "../kernel/io.h"

void Kernel_User_Main(void) {
    char buf[64];
    while (1) {
        Kernel_IO_GetString(buf, 64);
        Kernel_IO_PrintFormat("You said %s\n", buf);
    }

    Kernel_Task_Terminate(Kernel_Scheduler_Current);
}
