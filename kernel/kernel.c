#include <stdarg.h>

#include "kernel.h"

#include "interrupt.h"
#include "timer.h"
#include "../config/etssos_config.h"

#define noreturn __attribute__((noreturn))

void Kernel_Kernel_Main(void) {
    Kernel_Timer_Init();
    while (1);
}

void Kernel_Kernel_DumpInfo(void) {
    Drivers_UART_PutStringLine("Kernel Info:");
    Drivers_UART_PrintFormat("Name     : %s\n", ETSSOS_NAME);
    Drivers_UART_PrintFormat("Version  : %s\n", ETSSOS_VERSION);
    Drivers_UART_PrintFormat("Compiler : %s\n", ETSSOS_CC);
    Drivers_UART_PrintFormat("CFLAGS   : %s\n", ETSSOS_CFLAGS);
    Drivers_UART_PrintFormat("Linker   : %s\n", ETSSOS_LD);
    Drivers_UART_PrintFormat("LDFLAGS  : %s\n", ETSSOS_LDFLAGS);
    Drivers_UART_PrintFormat("Assembler: %s\n", ETSSOS_AS);
    Drivers_UART_PrintFormat("ASFLAGS  : %s\n", ETSSOS_ASFLAGS);
    Drivers_UART_PrintFormat("Burner   : %s\n", ETSSOS_BURNER);
    Drivers_UART_PrintFormat("BAUD     : %u\n", ETSSOS_BAUD);
    Drivers_UART_PrintFormat("Board    : %s\n", ETSSOS_BOARD);
    Drivers_UART_PrintFormat("UART CLK : %u\n", DRIVERS_TIMER_CLK_FREQ);
}

void noreturn Kernel_Kernel_Panic_Dump() {
    uint8_t  cause;
    uint32_t addr;

    __asm__ volatile (
        "rsr.exccause %0\n"
        "rsr.epc1 %1"
        : "=a" (cause), "=a" (addr));

    Drivers_UART_PrintFormat("Address: %x\n", addr);
    Drivers_UART_PrintFormat("Cause: %s\n", cause < 30
                                            ? Kernel_Kernel_Panic_CauseStrings[cause]
                                            : "RESERVED");
    Drivers_UART_PutStringLine("Entering fault loop.");

    while (1);
}

void Kernel_Kernel_Panic(void) {
    uint32_t cause;
    __asm__ volatile (
        "rsr.exccause %0"
        : "=a" (cause));

    if (cause == KERNEL_INTERRUPT_LEVEL1INTERRUPT) {
        Kernel_Interrupt_Dispatch();
    }
    else {
        Kernel_Kernel_Panic_Dump();
    }
}

void noreturn Kernel_Kernel_Panic_Unreachable(void) {
    Drivers_UART_PutStringLine("Kernel reached unreachable code.");
    while (1);
}

void noreturn Kernel_Kernel_Panic_Debug(void) {
    Drivers_UART_PutStringLine("Kernel reached debug exception.");
    Kernel_Kernel_Panic_Dump();
}

void noreturn Kernel_Kernel_Panic_NonMaskable(void) {
    Drivers_UART_PutStringLine("Kernel reached a non-maskable interrupt.");
    Kernel_Kernel_Panic_Dump();
}

void Kernel_Kernel_Panic_UserError(void) {
    uint32_t cause;
    __asm__ volatile (
        "rsr.exccause %0"
        : "=a" (cause));

    if (cause == KERNEL_INTERRUPT_LEVEL1INTERRUPT) {
        Kernel_Interrupt_Dispatch();
    }
    else {
        Drivers_UART_PutStringLine("Panic in userspace code.");
        Kernel_Kernel_Panic_Dump();
    }
}

void noreturn Kernel_Kernel_Panic_Double(void) {
    Drivers_UART_PutStringLine("Double panic.");

    uint32_t addr;

    __asm__ volatile (
        "rsr.epc2 %0"
        : "=a" (addr));

    Drivers_UART_PrintFormat("Most Recent Addr: %x\n", addr);
    Kernel_Kernel_Panic_Dump();
}

static char const _reserved_[] = "RESERVED";
char const* const Kernel_Kernel_Panic_CauseStrings[] = {
    "IllegalInstruction",
    "Syscall",
    "InstructionFetchError",
    "LoadStoreError",
    "Level1Interrupt",
    "Alloca",
    "DivideByZero",
    _reserved_,
    "PrivilegeMismatch",
    "LoadStoreAlignment",
    _reserved_,
    _reserved_,
    "InstrPIFDataError",
    "LoadStorePIFDataError",
    "InstrPIFAddrError",
    "LoadStorePIFAddrError",
    "InstTLBMiss",
    "InstTLBMultiHit",
    "InstFetchPrivilegeMismatch",
    _reserved_,
    "InstFetchProhibited",
    _reserved_,
    _reserved_,
    _reserved_,
    "LoadStoreTLBMiss",
    "LoadStoreTLBMultiHit",
    "LoadStorePrivilegeMismatch",
    _reserved_,
    "LoadProhibited",
    "StoreProhibited",
    _reserved_,
    _reserved_,
    "Coprocessor0Disabled",
    "Coprocessor1Disabled",
    "Coprocessor2Disabled",
    "Coprocessor3Disabled",
    "Coprocessor4Disabled",
    "Coprocessor5Disabled",
    "Coprocessor6Disabled",
    "Coprocessor7Disabled",
};
