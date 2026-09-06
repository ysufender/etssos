#include "gpio.h"

#include "../iomux.h"

void GPIO_Init(void) {
    for (uint8_t pin = 0; pin < GPIO_PIN_CNT; pin++) {
        IOMUX_GPIO_SetPullup(pin, 1);
    }
}

void GPIO_SetMode(uint8_t const pin, GPIO_Mode const mode) {
    if (mode == GPIO_Mode_Output) {
        GPIO_ENA_W1TS = (1 << pin); /* Set output */
    }
    else {
        GPIO_ENA_W1TC = (1 << pin);
    }
}

void GPIO_Write(uint8_t const pin, uint16_t const val) {
    if (pin >= 6 && pin <= 11) return;
    if (val) {
        GPIO_OUT_W1TS = (1 << pin);
    } else {
        GPIO_OUT_W1TC = (1 << pin);
    }
}
