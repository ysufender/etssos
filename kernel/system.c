#include "system.h"

#include "task.h"
#include "pin.h"
#include "io.h"

void Kernel_System_Task(void) {
    Kernel_IO_Init();
    Kernel_Pin_Init();

    Kernel_Task_Create("user", Kernel_User_Main, 254, Kernel_IO_Uart);

    Kernel_Task_Exit();
}

void Kernel_System_Idle(void) {
    Kernel_Task_Idle();
}
