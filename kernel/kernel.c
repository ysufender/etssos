#include "kernel.h"

#include "../drivers/gpio/gpio.h"
#include "../drivers/uart/uart.h"
#include "../drivers/timer/timer.h"
#include "../config/etssos_config.h"

static char const _reserved_[] = "RESERVED";
static char const* const Kernel_Panic_CauseStrings[] = {
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

void Kernel_Main(void) {
    Drivers_GPIO_Init();
    Drivers_Timer_Init();
    Drivers_UART_Init();

    _etssos_interrupt_enable();

    Drivers_UART_PutStringLine("UART Initialization successful.");
    Kernel_DumpInfo();
}

void Kernel_DumpInfo(void) {
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
    Drivers_UART_PrintFormat("UART CLK : %u\n", DRIVERS_UART0_CLK_FREQ);
}

void __attribute__((noreturn)) Kernel_Panic(void) {
    uint32_t cause, addr;

    __asm__ volatile (
            "rsr.exccause %0\n"
             "rsr.epc1 %1"
            : "=a" (cause), "=a" (addr));

    Drivers_UART_PrintFormat("Address: %u\n", addr);
    Drivers_UART_PrintFormat("Cause: %s\n", cause < 30 ? Kernel_Panic_CauseStrings[cause] : _reserved_);
    Drivers_UART_PutStringLine("Entering fault loop.");
    while (1);
}

void Kernel_Panic_Unreachable(void) {
    Drivers_UART_PutStringLine("Kernel reached unreachable code.");
    return Kernel_Panic();
}

void Kernel_Panic_Debug(void) {
    Drivers_UART_PutStringLine("Kernel reached debug exception.");
    return Kernel_Panic();
}

void Kernel_Panic_NonMaskable(void) {
    Drivers_UART_PutStringLine("Kernel reached a non-maskable interrupt.");
    return Kernel_Panic();
}

void Kernel_Panic_UserError(void) {
    Drivers_UART_PutStringLine("Panic in userspace code.");
    return Kernel_Panic();
}

void Kernel_Panic_Double(void) {
    Drivers_UART_PutStringLine("Double panic.");

    uint32_t addr;

    __asm__ volatile (
            "rsr.epc2 %0"
            : "=a" (addr));

    Drivers_UART_PrintFormat("Most Recent Addr: %u\n", addr);
    return Kernel_Panic();
}
