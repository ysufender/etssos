#include "system.h"

#include "scheduler.h"
#include "task.h"

void Kernel_System_Task(void) {
    Kernel_User_Main();
    Kernel_Task_Terminate(Kernel_Scheduler_Current);
}
