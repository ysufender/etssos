#include "shell.h"

#include "../kernel/io.h"
#include "../kernel/task.h"
#include "../kernel/signal.h"

#include "../libc/string.h"
#include "../libc/memory.h"

#define if_str(__str__) if (strcmp(__str__, buffer) == 0)

static uint32_t _parse(char* const cmdline) {
    uint8_t inString = 0;
    uint32_t count = cmdline[0] != '\0';
    for (uint32_t i = 0; cmdline[i]; i++) {
        if (cmdline[i] == ' ' && !inString) {
            cmdline[i] = '\0';
            count++;
        }
        else if (cmdline[i] == '"') {
            inString = !inString;
        }
    }

    return count;
}

static char const* _next(char const** const args, uint32_t* const argc) {
    if (!*argc) return *args;
    char const* const res = *args;
    for (; **args; (*args)++);
    (*args)++;
    (*argc)--;
    return res;
}

void OS_Shell(void) {
    char buffer[128];
    char const* args = buffer;
    char const* cmd;
    char const* errmsg;

    while (1) {
        Kernel_IO_PutString("shell@etssos $ ");
        Kernel_IO_GetString(buffer, 128);
        args = buffer;

        uint32_t argc = _parse(buffer);
        cmd = _next(&args, &argc);

        if_str ("help") {
            if (argc == 0) {
                Kernel_IO_PutStringLine("Available commands:");
                Kernel_IO_PutStringLine("\thelp [cmd]");
                Kernel_IO_PutStringLine("\tps");
                Kernel_IO_PutStringLine("\tkill <pid>");
                Kernel_IO_PutStringLine("\treboot");
                Kernel_IO_PutStringLine("\tchmod <pid> <new>");
                Kernel_IO_PutStringLine("\tsignal <sign>");
                Kernel_IO_PutStringLine("\tunsign <sign>");
                Kernel_IO_PutStringLine("\tsstat");
                Kernel_IO_PutStringLine("\ttick");
            }
            else if (argc > 1) {
                errmsg = "Too manu arguments.";
                goto error;
            }
            else {
                errmsg = "Not implemented.";
                goto error;
            }
        }
        else if_str ("tick") {
            Kernel_IO_PrintFormat("%u%u\n", (uint32_t)(Kernel_Timer_Ticks >> 32), (uint32_t)Kernel_Timer_Ticks);
        }
        else if_str ("unsign") {
            if (!argc) {
                errmsg = "Expected signal number.";
                goto error;
            }
            uint32_t const sign = strtoul(_next(&args, &argc), 0, 0);
            Kernel_Signal_Unsend(sign);
        }
        else if_str ("sstat") {
            for (int8_t i = 63; i >= 0; i--) {
                Kernel_IO_PutChar('0' + (Kernel_Signal_Vector[i].active & 1));
            }
            Kernel_IO_PutChar('\n');
        }
        else if_str ("signal") {
            if (!argc) {
                errmsg = "Expected signal number.";
                goto error;
            }
            uint32_t const sign = strtoul(_next(&args, &argc), 0, 0);
            Kernel_Signal_Send(sign);
        }
        else if_str ("ps") {
            for (uint8_t i = 0; i < Kernel_Task_Count; i++) {
                Kernel_Task const* const task = &Kernel_Task_Pool[i];
                if (task->state == KERNEL_TASK_TERMINATED) {
                    continue;
                }
                Kernel_IO_PrintFormat("%s %s %d (%d)\n", task->name, Kernel_Task_Status_String[task->state], task->priority, i);
            }
        }
        else if_str ("kill") {
            if (!argc) {
                errmsg = "Expected pid.";
                goto error;
            }

            uint32_t const pid = strtoul(_next(&args, &argc), 0, 0);
            Kernel_Task_Kill(pid);
        }
        else if_str ("reboot") {
            errmsg = "Not implemented";
            goto error;
        }
        else if_str ("chmod") {
            if (argc != 2) {
                errmsg = "Wrong arguments.";
                goto error;
            }

            uint32_t const pid = strtoul(_next(&args, &argc), 0, 0),
                           new = strtoul(_next(&args, &argc), 0, 0);

            Kernel_Task_Pool[pid].priority = new;
        }
        else {
            errmsg = "Unknown command.";
            goto error;
        }

        continue;
error:
        Kernel_IO_PrintFormat("error: %s (%s)\n", errmsg, cmd);
    }
};
