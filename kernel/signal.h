/*
 * THIS FILE IS A PART OF THE ETSSOS PROJECT
 * AND IS LICENSED UNDER THE MIT LICENSE
 * 
 * SEE (LICENSE)[/LICENSE] FOR MORE INFORMATION
 *
 *
 * NAME       : kernel/signal.h
 * DESCRIPTION: Interprocess signalling
 */

#ifndef _ETSSOS_KERNEL_SIGNAL_H_
#define _ETSSOS_KERNEL_SIGNAL_H_

#include "../drivers/common.h"
#include "task.h"

typedef enum backing(uint64_t) Kernel_Signal {
    Kernel_Signal_Segfault = 0,
    Kernel_Signal_Abort,
    Kernel_Signal_Trap,
    Kernel_Signal_Fault,
    /* Reserved */
    Kernel_Signal_User = 32
    /* User Defined */
} Kernel_Signal;


typedef struct Kernel_Signal_Entry {
    uint8_t active;
    uint8_t sender;
    uint8_t subscribers[32];
} Kernel_Signal_Entry;

extern Kernel_Signal_Entry Kernel_Signal_Vector[64];

void    Kernel_Signal_Subscribe(Kernel_Signal const);
void    Kernel_Signal_Unsubscribe(Kernel_Signal const);
void    Kernel_Signal_Send(Kernel_Signal const);
void    Kernel_Signal_Unsend(Kernel_Signal const);
uint8_t Kernel_Signal_Await(Kernel_Signal const);
uint8_t Kernel_Signal_Up(Kernel_Signal const);

#endif /* _ETSSOS_KERNEL_SIGNAL_H_ */
