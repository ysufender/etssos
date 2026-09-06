/*
 * THIS FILE IS A PART OF THE ETSSOS PROJECT AND IS LICENSED UNDER THE MIT LICENSE
 * 
 * SEE (LICENSE)[/LICENSE] FOR MORE INFORMATION
 *
 *
 * NAME       : drivers/iomux.h
 * DESCRIPTION: IO multiplexer definitions
 */

#ifndef _ETSSOS_DRIVERS_IOMUX_H_
#define _ETSSOS_DRIVERS_IOMUX_H_

#include <stdint.h>

#define IOMUX_PERI 0x60000800

#define IOMUX_FUNC_MASK  0x00000130
#define IOMUX_FUNC_SHIFT 4
#define IOMUX_PIN_PULLUP 7

#define IOMUX_GPIO0_FUNC_GPIO              (0)
#define IOMUX_GPIO0_FUNC_SPI0_CS2          (1)
#define IOMUX_GPIO0_FUNC_CLOCK_OUT         (4)
#define IOMUX_GPIO1_FUNC_UART0_TXD         (0)
#define IOMUX_GPIO1_FUNC_SPI0_CS1          (1)
#define IOMUX_GPIO1_FUNC_GPIO              (3)
#define IOMUX_GPIO1_FUNC_CLOCK_RTC_BLINK   (4)
#define IOMUX_GPIO2_FUNC_GPIO              (0)
#define IOMUX_GPIO2_FUNC_I2SO_WS           (1)
#define IOMUX_GPIO2_FUNC_UART1_TXD         (2)
#define IOMUX_GPIO2_FUNC_UART0_TXD         (4)
#define IOMUX_GPIO3_FUNC_UART0_RXD         (0)
#define IOMUX_GPIO3_FUNC_I2SO_DATA         (1)
#define IOMUX_GPIO3_FUNC_GPIO              (3)
#define IOMUX_GPIO3_FUNC_CLOCK_XTAL_BLINK  (4)
#define IOMUX_GPIO4_FUNC_GPIO              (0)
#define IOMUX_GPIO4_FUNC_CLOCK_XTAL        (1)
#define IOMUX_GPIO5_FUNC_GPIO              (0)
#define IOMUX_GPIO5_FUNC_CLOCK_RTC         (1)
#define IOMUX_GPIO6_FUNC_SD_CLK            (0)
#define IOMUX_GPIO6_FUNC_SPI0_CLK          (1)
#define IOMUX_GPIO6_FUNC_GPIO              (3)
#define IOMUX_GPIO6_FUNC_UART1_CTS         (4)
#define IOMUX_GPIO7_FUNC_SD_DATA0          (0)
#define IOMUX_GPIO7_FUNC_SPI0_Q_MISO       (1)
#define IOMUX_GPIO7_FUNC_GPIO              (3)
#define IOMUX_GPIO7_FUNC_UART1_TXD         (4)
#define IOMUX_GPIO8_FUNC_SD_DATA1          (0)
#define IOMUX_GPIO8_FUNC_SPI0_D_MOSI       (1)
#define IOMUX_GPIO8_FUNC_GPIO              (3)
#define IOMUX_GPIO8_FUNC_UART1_RXD         (4)
#define IOMUX_GPIO9_FUNC_SD_DATA2          (0)
#define IOMUX_GPIO9_FUNC_SPI0_HD           (1)
#define IOMUX_GPIO9_FUNC_GPIO              (3)
#define IOMUX_GPIO9_FUNC_SPI1_HD           (4)
#define IOMUX_GPIO10_FUNC_SD_DATA3         (0)
#define IOMUX_GPIO10_FUNC_SPI0_WP          (1)
#define IOMUX_GPIO10_FUNC_GPIO             (3)
#define IOMUX_GPIO10_FUNC_SPI1_WP          (4)
#define IOMUX_GPIO11_FUNC_SD_CMD           (0)
#define IOMUX_GPIO11_FUNC_SPI0_CS0         (1)
#define IOMUX_GPIO11_FUNC_GPIO             (3)
#define IOMUX_GPIO11_FUNC_UART1_RTS        (4)
#define IOMUX_GPIO12_FUNC_MTDI             (0)
#define IOMUX_GPIO12_FUNC_I2SI_DATA        (1)
#define IOMUX_GPIO12_FUNC_SPI1_Q_MISO      (2)
#define IOMUX_GPIO12_FUNC_GPIO             (3)
#define IOMUX_GPIO12_FUNC_UART0_DTR        (4)
#define IOMUX_GPIO13_FUNC_MTCK             (0)
#define IOMUX_GPIO13_FUNC_I2SI_BCK         (1)
#define IOMUX_GPIO13_FUNC_SPI1_D_MOSI      (2)
#define IOMUX_GPIO13_FUNC_GPIO             (3)
#define IOMUX_GPIO13_FUNC_UART0_CTS        (4)
#define IOMUX_GPIO14_FUNC_MTMS             (0)
#define IOMUX_GPIO14_FUNC_I2SI_WS          (1)
#define IOMUX_GPIO14_FUNC_SPI1_CLK         (2)
#define IOMUX_GPIO14_FUNC_GPIO             (3)
#define IOMUX_GPIO14_FUNC_UART0_DSR        (4)
#define IOMUX_GPIO15_FUNC_MTDO             (0)
#define IOMUX_GPIO15_FUNC_I2SO_BCK         (1)
#define IOMUX_GPIO15_FUNC_SPI1_CS0         (2)
#define IOMUX_GPIO15_FUNC_GPIO             (3)
#define IOMUX_GPIO15_FUNC_UART0_RTS        (4)

#define IOMUX_GPIO(__pinnum__) (*(volatile uint32_t*)(IOMUX_PERI + (uintptr_t)IOMUX_GPIO_GPIOVector[__pinnum__]))
#define IOMUX_GPIO_SetPullup(__pinnum__, __ena__) do { \
    if (__ena__) IOMUX_GPIO(__pinnum__) |= (1 << IOMUX_PIN_PULLUP); \
    else         IOMUX_GPIO(__pinnum__) &= ~(1 << IOMUX_PIN_PULLUP); \
} while(0)

extern uint32_t const IOMUX_GPIO_GPIOVector[16];
extern uint32_t const IOMUX_GPIO_FuncVector[16];

void IOMUX_SetFunc(uint8_t const, uint8_t const, uint8_t const);

#endif /* _ETSSOS_DRIVERS_IOMUX_H_ */
