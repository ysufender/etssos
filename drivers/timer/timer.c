#include <stdatomic.h>

#include "timer.h"

#include "../../kernel/interrupt.h"
#include "../uart/uart.h"
#include "../gpio/gpio.h"

void Drivers_Timer_DetectClock(void) {
    uint32_t const div = DRIVERS_UART0_CLKDIV & 0x000FFFFF;
    *(uint32_t*)(&DRIVERS_UART0_CLK_FREQ) = 74880 * div;
}

void Drivers_Timer_Init(void) {
    Drivers_Timer_DetectClock();

    Kernel_Interrupt_Register(KERNEL_INTERRUPT_SOURCE_TIMER_FRC1, Drivers_Timer_FRC1_Interrupt_Handler);
    Kernel_Interrupt_Register(KERNEL_INTERRUPT_SOURCE_TIMER_FRC2, Drivers_Timer_FRC2_Interrupt_Handler);

    DRIVERS_TIMER_FRC1_LOAD      = DRIVERS_TIMER_FRC1_INTERVAL_TICKS; 
    DRIVERS_TIMER_FRC1_CTRL_ADDR = (1 << 0)
                                 | (DRIVERS_TIMER_PRESCALE_DIVIDER << 2)
                                 | (1 << 6)
                                 | (1 << 7);

    DRIVERS_TIMER_FRC2_LOAD       = 0; 
    DRIVERS_TIMER_FRC2_ALARM_ADDR = DRIVERS_TIMER_FRC2_INTERVAL_TICKS;
    DRIVERS_TIMER_FRC2_CTRL_ADDR  = (1 << 0)
                                  | (DRIVERS_TIMER_PRESCALE_DIVIDER << 2)
                                  | (1 << 6)
                                  | (1 << 7);
}

void Drivers_Timer_FRC1_Interrupt_Handler(void) {
    Drivers_GPIO_Write(5, 1);
}

void Drivers_Timer_FRC2_Interrupt_Handler(void) {
}
