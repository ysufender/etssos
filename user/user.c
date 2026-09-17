#include "../kernel/task.h"

#include "../os/shell.h"

#include "../kernel/signal.h"

void Kernel_User_Main(void) {
    Kernel_Signal_Subscribe(Kernel_Signal_Segfault);
    Kernel_Task_Create("shellt", OS_Shell, 254, Kernel_IO_Uart);

    while(Kernel_Signal_Await(Kernel_Signal_Segfault)) Kernel_Task_Yield();
    Kernel_IO_PutStringLine("Segfault");

    Kernel_Task_Exit();
}
