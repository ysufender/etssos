#include "../kernel/io.h"
#include "../kernel/timer.h"
#include "../kernel/task.h"
#include "../kernel/scheduler.h"

void Kernel_User_Main(void) {
    while (1) {
        Kernel_IO_PutStringLine("Hello User");
    }

    Kernel_Task_Terminate(Kernel_Scheduler_Current);
}
