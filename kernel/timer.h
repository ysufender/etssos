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

typedef struct Kernel_Timer_Timer {
    uint32_t       counter = 0;
    uint16_t const divider = 1;
    uint8_t        active  = 0;
    uint32_t       tick    = 0;
} Kernel_Timer_Timer;

void Kernel_Timer_Init(void);

void Kernel_Timer_FRC1_Interrupt_Handler(void);
void Kernel_Timer_FRC2_Interrupt_Handler(void);

#endif /* _ETSSOS_KERNEL_TIMER_H_ */
