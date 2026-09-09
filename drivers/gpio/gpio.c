#include "gpio.h"

#include "../iomux.h"

void Drivers_GPIO_Init(void) {
    for (uint8_t pin = 0; pin < DRIVERS_GPIO_PIN_CNT; pin++) {
        Drivers_IOMUX_GPIO_SetPullup(pin, 1);
        Drivers_GPIO_PinSetup(pin);
    }
}

void Drivers_GPIO_SetMode(uint8_t const pin, DRIVERS_GPIO_MODE const mode) {
    if (mode == DRIVERS_GPIO_MODE_OUTPUT) {
        DRIVERS_GPIO_ENA_W1TS = (1 << pin); /* Set output */
    }
    else {
        DRIVERS_GPIO_ENA_W1TC = (1 << pin);
    }
}

void Drivers_GPIO_PinSetup_Impl(uint8_t const pinnum, Drivers_GPIO_Pin_Setup_Params const params) {
    Drivers_GPIO_PIN(pinnum) = (params.source        << 0)
                             | (params.driver        << 2)
                             | (params.interruptType << 7)
                             | (params.wakeup        << 10);
}
