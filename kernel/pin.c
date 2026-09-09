#include "pin.h"

#include "../drivers/iomux.h"
#include "../drivers/gpio/gpio.h"

void Kernel_Pin_Init(void) {
    Drivers_GPIO_Init();
}

void Kernel_Pin_SetFunc(uint8_t const pin, uint8_t const func, uint8_t const pullup) {
    Drivers_IOMUX_SetFunc(pin, func, pullup);
}

void Kernel_Pin_SetMode(uint8_t const pin, Kernel_Pin_Mode const mode) {
    if (mode == Kernel_Pin_Mode_Output) {
        DRIVERS_GPIO_ENA_W1TS |= (1 << pin);
    }
    else {
        DRIVERS_GPIO_ENA_W1TC |= (1 << pin);
    }
}

void Kernel_Pin_Digital_Write(uint8_t const pin, uint8_t const value) {
    if (value == LOW) {
        DRIVERS_GPIO_OUT &= ~(1 << pin);
    }
    else {
        DRIVERS_GPIO_OUT |= (1 << pin);
    }
}

uint8_t Kernel_Pin_Digital_Read(uint8_t const pin) {
    if ((DRIVERS_GPIO_ENA & DRIVERS_GPIO_ENA_DATA) & (1 << pin)) {
        return 0;
    }

    return (DRIVERS_GPIO_IN >> pin) & 1;
}
