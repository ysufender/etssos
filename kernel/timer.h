/*
 * THIS FILE IS A PART OF THE ETSSOS PROJECT AND IS LICENSED UNDER THE MIT LICENSE
 * 
 * SEE (LICENSE)[/LICENSE] FOR MORE INFORMATION
 *
 *
 * NAME       : kernel/timer.h
 * DESCRIPTION: Software timer
 */

#ifndef _ETSSOS_KERNEL_TIMER_H_
#define _ETSSOS_KERNEL_TIMER_H_

#include <stdint.h>

#include "../drivers/common.h"

typedef void (*Kernel_Timer_Callback)();

typedef enum backing(uint8_t) KERNEL_TIMER_FLAGS {
    KERNEL_TIMER_FLAGS_ACTIVE = (1 << 0),
    KERNEL_TIMER_FLAGS_RELOAD = (1 << 1),
} KERNEL_TIMER_FLAGS;

typedef struct Kernel_Timer {
    uint32_t                    counter;
    uint16_t                    divider;
    uint8_t                     flags;
    uint32_t                    tick;
    uint32_t                    alarm;
    Kernel_Timer_Callback       callback;
} Kernel_Timer;

typedef enum backing(uint8_t) Kernel_Timer_Mode {
    Kernel_Timer_Mode_Milliseconds,
    Kernel_Timer_Mode_Seconds,
} Kernel_Timer_Mode;

void          Kernel_Timer_Init(void);
Kernel_Timer* Kernel_Timer_Create(Kernel_Timer_Mode     const,
                                  uint32_t              const,
                                  Kernel_Timer_Callback const);

void Kernel_Timer_FRC1_Interrupt_Handler(void);
void Kernel_Timer_FRC2_Interrupt_Handler(void);

#endif /* _ETSSOS_KERNEL_TIMER_H_ */
