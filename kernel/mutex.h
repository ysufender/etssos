/*
 * THIS FILE IS A PART OF THE ETSSOS PROJECT
 * AND IS LICENSED UNDER THE MIT LICENSE
 * 
 * SEE (LICENSE)[/LICENSE] FOR MORE INFORMATION
 *
 *
 * NAME       : kernel/mutex.h
 * DESCRIPTION: Mutex synchronization utilities
 */

#ifndef _ETSSOS_KERNEL_MUTEX_H_
#define _ETSSOS_KERNEL_MUTEX_H_

#include "task.h"

typedef struct Kernel_Mutex_TaskQueue {
    Kernel_Task*                   head;
    struct Kernel_Mutex_TaskQueue* tail;
} Kernel_Mutex_TaskQueue;

typedef struct Kernel_Mutex {
    Kernel_Task*            owner;
    Kernel_Mutex_TaskQueue* waiters;
    uint32_t                count;
} Kernel_Mutex;

#define Kernel_Mutex_TaskQueue_Empty (Kernel_Mutex_TaskQueue){ 0, 0 }
#define Kernel_Mutex_Default (Kernel_Mutex){ 0, 0, 0 }

void Kernel_Mutex_Lock(Kernel_Mutex* const);
void Kernel_Mutex_Unlock(Kernel_Mutex* const);

#endif /*  _ETSSOS_KERNEL_MUTEX_H_ */
