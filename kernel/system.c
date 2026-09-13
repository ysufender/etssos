#include "system.h"

#include "scheduler.h"
#include "task.h"
#include "pin.h"
#include "io.h"
#include "timer.h"

void Kernel_System_Task(void) {
    Kernel_IO_Init();
    Kernel_Pin_Init();

    Kernel_Task_Create("user", Kernel_User_Main, 254);
    Kernel_Task_Terminate(Kernel_Scheduler_Current);
}

void Kernel_System_Idle(void) {
    Kernel_Task_Sleep(Kernel_Timer_Mode_Milliseconds, 100);
    Kernel_IO_PutStringLine("Going idle...");
    Kernel_Task_Idle();
}
