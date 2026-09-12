/*
 * THIS FILE IS A PART OF THE ETSSOS PROJECT
 * AND IS LICENSED UNDER THE MIT LICENSE
 * 
 * SEE (LICENSE)[/LICENSE] FOR MORE INFORMATION
 *
 *
 * NAME       : kernel/error.h
 * DESCRIPTION: Error handling utilities
 */


#ifndef _ETSSOS_KERNEL_ERROR_H_
#define _ETSSOS_KERNEL_ERROR_H_

#include "../drivers/common.h"
#include "interrupt.h"

typedef enum backing(uint8_t) Kernel_Error {
    Kernel_Error_Unreachable,
    Kernel_Error_NotImplemented,
    Kernel_Error_StackOverflow,
} Kernel_Error;

#define THROW(__err__) do { \
    __asm__ volatile ( \
        "movi a2, 0\n" \
        "movi a3, %0" \
        : \
        : "i" (__err__) \
        : "a2", "a3") ; \
    Kernel_Interrupt_Trigger(KERNEL_INTERRUPT_SOURCE_SOFT); \
    while (1); \
} while(0)

#endif /* _ETSSOS_KERNEL_ERROR_H_ */
