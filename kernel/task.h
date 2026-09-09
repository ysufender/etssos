/*
 * THIS FILE IS A PART OF THE ETSSOS PROJECT
 * AND IS LICENSED UNDER THE MIT LICENSE
 * 
 * SEE (LICENSE)[/LICENSE] FOR MORE INFORMATION
 *
 *
 * NAME       : kernel/task.h
 * DESCRIPTION: Task scheduling utilities
 */

#ifndef _ETSSOS_KERNEL_TASK_H_
#define _ETSSOS_KERNEL_TASK_H_

#include "../drivers/common.h"

typedef enum backing(uint8_t) KERNEL_TASK_STATUS {
    KERNEL_TASK_READY,
    KERNEL_TASK_RUNNING,
    KERNEL_TASK_BLOCKED,
    KERNEL_TASK_SLEEPING,
    KERNEL_TASK_TERMINATED,
} KERNEL_TASK_STATUS;

typedef struct Kernel_Task_Info {
    uint32_t*          sp;
    uint32_t*          bp;
    uint32_t           stackSize;
    uint32_t           priority;
    uint64_t           wakeTick;
    char               name[16];
    KERNEL_TASK_STATUS state;
} Kernel_Task_Info;

typedef void (*Kernel_Task)(void);

#endif /* _ETSSOS_KERNEL_TASK_H_ */
