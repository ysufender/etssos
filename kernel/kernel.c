#include "kernel.h"

#include "../drivers/uart/uart.h"

#include "interrupt.h"
#include "timer.h"
#include "io.h"
#include "scheduler.h"
#include "task.h"
#include "system.h"

#define noreturn __attribute__((noreturn))

extern Kernel_Task Kernel_Task_Pool[KERNEL_TASK_MAX_COUNT];
extern uint8_t     Kernel_Task_Count                      ;

void noreturn Kernel_Kernel_Panic_Unreachable(void);
void __init(void);

void Kernel_Kernel_Main(void) {
    __init();

    Kernel_Timer_Init();
    Kernel_Interrupt_Init();
    Kernel_Scheduler_Init();
    Kernel_Task_Create("idlet", Kernel_System_Idle, 0, Kernel_IO_Uart),
    Kernel_Task_Create("systemt", Kernel_System_Task, 255, Kernel_IO_Uart);
    Kernel_Scheduler_Start();
    Kernel_Kernel_Panic_Unreachable();
}

void noreturn Kernel_Kernel_Panic_Dump() {
    uint8_t  cause;
    uint32_t addr;
    uint32_t excvaddr;

    __asm__ volatile (
        "rsr.exccause %0\n"
        "rsr.epc1 %1\n"
        "rsr.excvaddr %2"
        : "=a" (cause), "=a" (addr), "=a" (excvaddr));

    Kernel_IO_PrintFormat("Task: %s\n", Kernel_Scheduler_Current->name);
    Kernel_IO_PrintFormat("Address: %x\n", addr);
    Kernel_IO_PrintFormat("Excvaddr: %x\n", excvaddr);
    Kernel_IO_PrintFormat("Cause: %s\n", cause < 30
                                            ? Kernel_Kernel_Panic_CauseStrings[cause]
                                            : "RESERVED");
    Kernel_IO_PutStringLine("Entering fault loop.");

    Kernel_IO_Flush();
    if (Kernel_Task_Count > 1) {
        Kernel_Task_Terminate(Kernel_Scheduler_Current);
        Kernel_Interrupt_Restore(0);
    }
    while (1) Kernel_Task_Yield();
}

void Kernel_Kernel_Panic(void) {
    uint32_t const ps = Kernel_Interrupt_Disable();

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

    Kernel_Interrupt_Restore(ps);
}

void noreturn Kernel_Kernel_Panic_Unreachable(void) {
    Kernel_IO_PutStringLine("Kernel reached unreachable code.");
    Kernel_IO_Flush();
    while (1) Kernel_Task_Yield();
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
    uint32_t const ps = Kernel_Interrupt_Disable();

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

    Kernel_Interrupt_Restore(ps);
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
