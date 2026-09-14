#include "../kernel/task.h"

#include "../os/shell.h"

void Kernel_User_Main(void) {
    Kernel_Task_Join(Kernel_Task_Create("shellt", OS_Shell, 254));
    Kernel_Task_Exit();
}
