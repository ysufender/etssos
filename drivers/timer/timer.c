#include "timer.h"

#include "../uart/uart.h"

volatile uint32_t DRIVERS_TIMER_CLK_FREQ;

void Drivers_Timer_DetectClock(void) {
    uint32_t const div = DRIVERS_UART0_CLKDIV & 0x000FFFFF;
    DRIVERS_TIMER_CLK_FREQ = 74880 * div;
}

void Drivers_Timer_Init(void) {
    Drivers_Timer_DetectClock();

    uint32_t divider = (DRIVERS_TIMER_PRESCALE_DIVIDER == 16)
                     ? 1
                     : 2;

    DRIVERS_TIMER_FRC1_LOAD      = DRIVERS_TIMER_FRC1_INTERVAL_TICKS; 
    DRIVERS_TIMER_FRC1_CTRL_ADDR = (0 << 0)
                                 | (divider << 2)
                                 | (1 << 6)
                                 | (1 << 7);

    DRIVERS_TIMER_FRC2_LOAD       = 0;
    DRIVERS_TIMER_FRC2_ALARM_ADDR = DRIVERS_TIMER_FRC2_INTERVAL_TICKS; 
    DRIVERS_TIMER_FRC1_CTRL_ADDR  = (0 << 0)
                                  | (divider << 2)
                                  | (1 << 6)
                                  | (1 << 7);
}
