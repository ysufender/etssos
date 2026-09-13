#include "../kernel/io.h"
#include "../kernel/timer.h"
#include "../kernel/task.h"
#include "../kernel/scheduler.h"

void Kernel_User_Main(void) {
    Kernel_Task_Sleep(Kernel_Timer_Mode_Seconds, 1);
    Kernel_IO_PrintFormat("Hello World at %u.\n", Kernel_Timer_Ticks);
    Kernel_Task_Terminate(Kernel_Scheduler_Current);
}
