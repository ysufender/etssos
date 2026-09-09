/*
 * THIS FILE IS A PART OF THE ETSSOS PROJECT
 * AND IS LICENSED UNDER THE MIT LICENSE
 * 
 * SEE (LICENSE)[/LICENSE] FOR MORE INFORMATION
 *
 *
 * NAME       : kernel/interrupt.h
 * DESCRIPTION: Interrupt handling utilities
 */

#ifndef _ETSSOS_KERNEL_INTERRUPT_H_
#define _ETSSOS_KERNEL_INTERRUPT_H_

#include "../drivers/common.h"

#define DPORT0_EDGE_INT_ENA (*(volatile uint32_t*)(0x3FF00004))

typedef enum backing(uint8_t) KERNEL_INTERRUPT_TYPE {
    KERNEL_INTERRUPT_ILLEGALINSTRUCTION,
    KERNEL_INTERRUPT_SYSCALL,
    KERNEL_INTERRUPT_INSTRUCTIONFETCHERROR,
    KERNEL_INTERRUPT_LOADSTOREERROR,
    KERNEL_INTERRUPT_LEVEL1INTERRUPT,
    KERNEL_INTERRUPT_ALLOCA,
    KERNEL_INTERRUPT_DIVIDEBYZERO,
    RESERVED_1,
    KERNEL_INTERRUPT_PRIVILEGEMISMATCH,
    KERNEL_INTERRUPT_LOADSTOREALIGNMENT,
    RESERVED_2,
    RESERVED_3,
    KERNEL_INTERRUPT_INSTRPIFDATAERROR,
    KERNEL_INTERRUPT_LOADSTOREPIFDATAERROR,
    KERNEL_INTERRUPT_INSTRPIFADDRERROR,
    KERNEL_INTERRUPT_LOADSTOREPIFADDRERROR,
    KERNEL_INTERRUPT_INSTTLBMISS,
    KERNEL_INTERRUPT_INSTTLBMULTIHIT,
    KERNEL_INTERRUPT_INSTFETCHPRIVILEGEMISMATCH,
    RESERVED_4,
    KERNEL_INTERRUPT_INSTFETCHPROHIBITED,
    RESERVED_5,
    RESERVED_6,
    RESERVED_7,
    KERNEL_INTERRUPT_LOADSTORETLBMISS,
    KERNEL_INTERRUPT_LOADSTORETLBMULTIHIT,
    KERNEL_INTERRUPT_LOADSTOREPRIVILEGEMISMATCH,
    RESERVED_9,
    KERNEL_INTERRUPT_LOADPROHIBITED,
    KERNEL_INTERRUPT_STOREPROHIBITED,
    RESERVED_A,
    RESERVED_B,
    KERNEL_INTERRUPT_COPROCESSOR0DISABLED,
    KERNEL_INTERRUPT_COPROCESSOR1DISABLED,
    KERNEL_INTERRUPT_COPROCESSOR2DISABLED,
    KERNEL_INTERRUPT_COPROCESSOR3DISABLED,
    KERNEL_INTERRUPT_COPROCESSOR4DISABLED,
    KERNEL_INTERRUPT_COPROCESSOR5DISABLED,
    KERNEL_INTERRUPT_COPROCESSOR6DISABLED,
    KERNEL_INTERRUPT_COPROCESSOR7DISABLED,
} KERNEL_INTERRUPT_TYPE;

#define KERNEL_INTERRUPT_COUNT 11

typedef enum backing(uint8_t) KERNEL_INTERRUPT_SOURCE {
    KERNEL_INTERRUPT_SOURCE_WDEV_FIQ    = 0,
    KERNEL_INTERRUPT_SOURCE_SLC         = 1,
    KERNEL_INTERRUPT_SOURCE_SPI         = 2,
    KERNEL_INTERRUPT_SOURCE_RTC         = 3,
    KERNEL_INTERRUPT_SOURCE_GPIO        = 4,
    KERNEL_INTERRUPT_SOURCE_UART        = 5,
    KERNEL_INTERRUPT_SOURCE_TICK        = 6,
    KERNEL_INTERRUPT_SOURCE_SOFT        = 7,
    KERNEL_INTERRUPT_SOURCE_WDT         = 8,
    KERNEL_INTERRUPT_SOURCE_TIMER_FRC1  = 9,
    KERNEL_INTERRUPT_SOURCE_TIMER_FRC2  = 10,
} KERNEL_INTERRUPT_SOURCE;

typedef void (*Kernel_Interrupt_Handler)();

void Kernel_Interrupt_Init(void);
void Kernel_Interrupt_Dispatch(void);
void Kernel_Interrupt_Scheduled(void);

extern Kernel_Interrupt_Handler Kernel_Interrupt_RegistrationVector[KERNEL_INTERRUPT_COUNT];
#define Kernel_Interrupt_Register(__src__, __handler__) Kernel_Interrupt_RegistrationVector[__src__] = __handler__

#define Kernel_Interrupt_Trigger(__src__) do {\
    __asm__ volatile ( \
        "wsr.intset %0\n" \
        "rsync\n" \
        : \
        : "a" (1 << __src__) \
    ); \
} while (0)

static inline uint32_t Kernel_Interrupt_Disable(void) {
    uint32_t old;
    __asm__ volatile (
        "rsil %0, 2"
        : "=a" (old));
    return old;
}

#define Kernel_Interrupt_Restore(__old__) \
    __asm__ volatile ( \
        "wsr.ps %0\n" \
        "rsync" \
        : \
        : "a" (__old__))

static inline uint32_t Kernel_Interrupt_Activate(uint32_t const mask) {
    uint32_t const old = Kernel_Interrupt_Disable();
    uint32_t intenable;
    __asm__ volatile (
        "rsr.intenable %0\n"
        : "=a" (intenable));
    __asm__ volatile (
        "wsr.intenable %0\n"
        "rsync"
        :
        : "a" (intenable | mask));
    Kernel_Interrupt_Restore(old);
    return intenable;
}

static inline uint32_t Kernel_Interrupt_Deactivate(uint32_t const mask) {
    uint32_t const old = Kernel_Interrupt_Disable();
    uint32_t intenable;
    __asm__ volatile (
        "rsr.intenable %0\n"
        : "=a" (intenable));
    __asm__ volatile (
        "wsr.intenable %0\n"
        "rsync"
        :
        : "a" (intenable & ~mask));
    Kernel_Interrupt_Restore(old);
    return intenable;
}

static inline uint32_t Kernel_Interrupt_Read(void) {
    uint32_t interrupts;
    __asm__ volatile (
        "rsr.interrupt %0"
        : "=a" (interrupts));
    return interrupts;
}

#define Kernel_Interrupt_Clear(__src__) do { \
    __asm__ volatile ( \
        "wsr.intclear %0\n" \
        "rsync" \
        : \
        : "a" (1 << __src__)); \
} while (0)

#endif /* _ETSSOS_KERNEL_INTERRUPT_H_ */
