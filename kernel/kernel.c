#include <stdarg.h>

#include "../config/etssos_config.h"

#include "kernel.h"

#include "interrupt.h"
#include "timer.h"
#include "io.h"
#include "pin.h"

#define noreturn __attribute__((noreturn))
uint8_t val = 1;

void pin_callback(void) {
    Kernel_Pin_Digital_Write(2, val);
    val = !val;
}

void Kernel_Kernel_Main(void) {
    Kernel_Timer_Init();
    Kernel_IO_Init();
    Kernel_Pin_Init();
    Kernel_Interrupt_Init();

    Kernel_Pin_SetFunc(2, KERNEL_PIN_GPIO2_FUNC_GPIO, ON);
    Kernel_Pin_SetMode(2, Kernel_Pin_Mode_Output);

    Kernel_Timer* const timer = Kernel_Timer_Create(Kernel_Timer_Mode_Seconds, 1, pin_callback);
    timer->flags |= KERNEL_TIMER_FLAGS_RELOAD | KERNEL_TIMER_FLAGS_ACTIVE;

    while (1);
}

void Kernel_Kernel_DumpInfo(void) {
    Kernel_IO_PutStringLine("Kernel Info:");
    Kernel_IO_PrintFormat("Name     : %s\n", ETSSOS_NAME);
    Kernel_IO_PrintFormat("Version  : %s\n", ETSSOS_VERSION);
    Kernel_IO_PrintFormat("Compiler : %s\n", ETSSOS_CC);
    Kernel_IO_PrintFormat("CFLAGS   : %s\n", ETSSOS_CFLAGS);
    Kernel_IO_PrintFormat("Linker   : %s\n", ETSSOS_LD);
    Kernel_IO_PrintFormat("LDFLAGS  : %s\n", ETSSOS_LDFLAGS);
    Kernel_IO_PrintFormat("Assembler: %s\n", ETSSOS_AS);
    Kernel_IO_PrintFormat("ASFLAGS  : %s\n", ETSSOS_ASFLAGS);
    Kernel_IO_PrintFormat("Burner   : %s\n", ETSSOS_BURNER);
    Kernel_IO_PrintFormat("BAUD     : %u\n", ETSSOS_BAUD);
    Kernel_IO_PrintFormat("Board    : %s\n", ETSSOS_BOARD);
    Kernel_IO_PrintFormat("UART CLK : %u\n", DRIVERS_TIMER_CLK_FREQ);
}

void noreturn Kernel_Kernel_Panic_Dump() {
    uint8_t  cause;
    uint32_t addr;

    __asm__ volatile (
        "rsr.exccause %0\n"
        "rsr.epc1 %1"
        : "=a" (cause), "=a" (addr));

    Kernel_IO_PrintFormat("Address: %x\n", addr);
    Kernel_IO_PrintFormat("Cause: %s\n", cause < 30
                                            ? Kernel_Kernel_Panic_CauseStrings[cause]
                                            : "RESERVED");
    Kernel_IO_PutStringLine("Entering fault loop.");

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
    Kernel_IO_PutStringLine("Kernel reached unreachable code.");
    while (1);
}

void noreturn Kernel_Kernel_Panic_Debug(void) {
    Kernel_IO_PutStringLine("Kernel reached debug exception.");
    Kernel_Kernel_Panic_Dump();
}

void noreturn Kernel_Kernel_Panic_NonMaskable(void) {
    Kernel_IO_PutStringLine("Kernel reached a non-maskable interrupt.");
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
        Kernel_IO_PutStringLine("Panic in userspace code.");
        Kernel_Kernel_Panic_Dump();
    }
}

void noreturn Kernel_Kernel_Panic_Double(void) {
    Kernel_IO_PutStringLine("Double panic.");

    uint32_t addr;

    __asm__ volatile (
        "rsr.epc2 %0"
        : "=a" (addr));

    Kernel_IO_PrintFormat("Most Recent Addr: %x\n", addr);
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
