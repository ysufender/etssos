#include "system.h"

#include "io.h"
#include "scheduler.h"
#include "task.h"
#include "pin.h"

void Kernel_System_Task(void) {
    Kernel_IO_Init();
    Kernel_Pin_Init();

    Kernel_Task_Sleep(Kernel_Timer_Mode_Milliseconds, 100);
    Kernel_IO_PutStringLine("System Setup Successful.");

    Kernel_Task* const user = Kernel_Task_Create("user", Kernel_User_Main, 1);
    while (user->state != KERNEL_TASK_TERMINATED);

    Kernel_Task_Terminate(Kernel_Scheduler_Current);
}
