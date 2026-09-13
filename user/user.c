#include "../kernel/task.h"
#include "../kernel/scheduler.h"

void Kernel_User_Main(void) {
    Kernel_Task_Terminate(Kernel_Scheduler_Current);
}
