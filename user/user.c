#include "../kernel/task.h"

#include "../kernel/signal.h"

#include "../os/shell.h"
#include "../os/protector.h"

void Kernel_User_Main(void) {
    Kernel_Task_Create("shellt", OS_Shell, 254, Kernel_IO_Uart);
    Kernel_Task_Create("protectt", OS_Protector, 254, Kernel_IO_Uart);

    Kernel_Task_Sleep(Kernel_Timer_Mode_Seconds, 5);
    Kernel_Signal_Send(Kernel_Signal_Trap);

    Kernel_Task_Exit();
}
