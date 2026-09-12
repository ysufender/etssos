/*
 * THIS FILE IS A PART OF THE ETSSOS PROJECT
 * AND IS LICENSED UNDER THE MIT LICENSE
 * 
 * SEE (LICENSE)[/LICENSE] FOR MORE INFORMATION
 *
 *
 * NAME       : kernel/task.h
 * DESCRIPTION: Task managing utilities
 */

#ifndef _ETSSOS_KERNEL_TASK_H_
#define _ETSSOS_KERNEL_TASK_H_

#include "../drivers/common.h"
#include "timer.h"

typedef enum backing(uint8_t) KERNEL_TASK_STATUS {
    KERNEL_TASK_READY,
    KERNEL_TASK_RUNNING,
    KERNEL_TASK_BLOCKED,
    KERNEL_TASK_SLEEPING,
    KERNEL_TASK_TERMINATED,
} KERNEL_TASK_STATUS;

typedef struct Kernel_Task {
    uint32_t*          sp;
    uint32_t*          bp;
    uint32_t           stackSize;
    uint64_t           wakeTick;
    uint8_t            priority;
    KERNEL_TASK_STATUS state;
    char               name[16];
} Kernel_Task;

typedef void (*Kernel_Task_Entry)(void);

#define KERNEL_TASK_MAX_COUNT  16
#define KERNEL_TASK_STACK_SIZE 1024

extern Kernel_Task Kernel_Task_Pool[KERNEL_TASK_MAX_COUNT];
extern uint8_t     Kernel_Task_Count;

Kernel_Task*                   Kernel_Task_Create(char const* const,
                                                  Kernel_Task_Entry const,
                                                  uint8_t const);
void __attribute__((noreturn)) Kernel_Task_Terminate(volatile Kernel_Task* const);
void                           Kernel_Task_Sleep(Kernel_Timer_Mode const, uint32_t const);
void __attribute__((noreturn)) Kernel_Task_Idle(void);

#endif /* _ETSSOS_KERNEL_TASK_H_ */
