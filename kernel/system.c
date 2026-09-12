#include "system.h"

#include "io.h"
#include "scheduler.h"
#include "task.h"
#include "pin.h"

void Kernel_System_Task(void) {
    Kernel_IO_Init();
    Kernel_Pin_Init();
    Kernel_User_Main();
    Kernel_Task_Terminate(Kernel_Scheduler_Current);
}
