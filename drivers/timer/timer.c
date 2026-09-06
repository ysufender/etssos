#include "timer.h"

extern volatile uint32_t DRIVERS_UART0_CLK_FREQ;
#define MS_TO_TICKS (DRIVERS_UART0_CLK_FREQ / 16 / 1000)

void Drivers_Timer_Init(void) {
    DRIVERS_TIMER_FRC2_CTRL_ADDR = (1 << 2)  /* div16 */
                                 | (1 << 7); /* enable */
}

void Drivers_Timer_Delay(uint32_t const ms) {
    uint32_t const ticks = ms * MS_TO_TICKS;
    uint32_t const target = DRIVERS_TIMER_FRC2_CNT + ticks;
    DRIVERS_TIMER_FRC2_ALARM_ADDR = target;
    while (DRIVERS_TIMER_FRC2_CNT < target);
}
