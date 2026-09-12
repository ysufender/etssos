/*
 * THIS FILE IS A PART OF THE ETSSOS PROJECT
 * AND IS LICENSED UNDER THE MIT LICENSE
 * 
 * SEE (LICENSE)[/LICENSE] FOR MORE INFORMATION
 *
 *
 * NAME       : kernel/scheduler.h
 * DESCRIPTION: Scheduler scheduling utilities
 */

#ifndef _ETSSOS_KERNEL_SCHEDULER_H_
#define _ETSSOS_KERNEL_SCHEDULER_H_

#include "task.h"

void                           Kernel_Scheduler_Init(void);
void                           Kernel_Scheduler_Tick(void);
void __attribute__((noreturn)) Kernel_Scheduler_Start(void);

extern volatile Kernel_Task* Kernel_Scheduler_Current;
extern volatile uint8_t      Kernel_Scheduler_Switched;

#endif /* _ETSSOS_KERNEL_SCHEDULER_H_ */
