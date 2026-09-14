#include "shell.h"

#include "../kernel/io.h"
#include "../kernel/task.h"

#include "../libc/string.h"

void OS_Shell(void) {
    char buffer[128];

    Kernel_Task_Sleep(Kernel_Timer_Mode_Milliseconds, 100);

    while (1) {
        Kernel_IO_PutString("\nshell@etssos $ ");
        uint32_t const rs = Kernel_IO_GetString(buffer, 128);
        (void)rs;
    }
}
