#include "../kernel/task.h"

#include "../os/shell.h"

#include "../kernel/signal.h"

void Kernel_User_Main(void) {
    Kernel_Task_Create("shellt", OS_Shell, 254, Kernel_IO_Uart);

    while (1) {
        Kernel_IO_PutStringLine("Hello World!");
        Kernel_Task_Sleep(Kernel_Timer_Mode_Seconds, 1);
    }

    Kernel_Task_Exit();
}
