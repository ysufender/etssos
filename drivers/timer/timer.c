#include "timer.h"

extern volatile uint32_t UART0_CLK_FREQ;
#define MS_TO_TICKS (UART0_CLK_FREQ / 16 / 1000)

void Timer_Init(void) {
    TIMER_FRC2_CTRL_ADDR = (1 << 2)  /* div16 */
                         | (1 << 7); /* enable */
}

void Timer_Delay(uint32_t const ms) {
    uint32_t const ticks = ms * MS_TO_TICKS;
    uint32_t const target = TIMER_FRC2_CNT + ticks;
    TIMER_FRC2_ALARM_ADDR = target;
    while (TIMER_FRC2_CNT < target);
}
