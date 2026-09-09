/*
 * THIS FILE IS A PART OF THE ETSSOS PROJECT
 * AND IS LICENSED UNDER THE MIT LICENSE
 * 
 * SEE (LICENSE)[/LICENSE] FOR MORE INFORMATION
 *
 *
 * NAME       : kernel/pin.h
 * DESCRIPTION: GPIO utilities
 */

#ifndef _ETSSOS_KERNEL_PIN_H_
#define _ETSSOS_KERNEL_PIN_H_

#include <stdint.h>

#include "../drivers/common.h"

#define KERNEL_PIN_GPIO0_FUNC_GPIO              (0)
#define KERNEL_PIN_GPIO0_FUNC_SPI0_CS2          (1)
#define KERNEL_PIN_GPIO0_FUNC_CLOCK_OUT         (4)
#define KERNEL_PIN_GPIO1_FUNC_UART0_TXD         (0)
#define KERNEL_PIN_GPIO1_FUNC_SPI0_CS1          (1)
#define KERNEL_PIN_GPIO1_FUNC_GPIO              (3)
#define KERNEL_PIN_GPIO1_FUNC_CLOCK_RTC_BLINK   (4)
#define KERNEL_PIN_GPIO2_FUNC_GPIO              (0)
#define KERNEL_PIN_GPIO2_FUNC_I2SO_WS           (1)
#define KERNEL_PIN_GPIO2_FUNC_UART1_TXD         (2)
#define KERNEL_PIN_GPIO2_FUNC_UART0_TXD         (4)
#define KERNEL_PIN_GPIO3_FUNC_UART0_RXD         (0)
#define KERNEL_PIN_GPIO3_FUNC_I2SO_DATA         (1)
#define KERNEL_PIN_GPIO3_FUNC_GPIO              (3)
#define KERNEL_PIN_GPIO3_FUNC_CLOCK_XTAL_BLINK  (4)
#define KERNEL_PIN_GPIO4_FUNC_GPIO              (0)
#define KERNEL_PIN_GPIO4_FUNC_CLOCK_XTAL        (1)
#define KERNEL_PIN_GPIO5_FUNC_GPIO              (0)
#define KERNEL_PIN_GPIO5_FUNC_CLOCK_RTC         (1)
#define KERNEL_PIN_GPIO6_FUNC_SD_CLK            (0)
#define KERNEL_PIN_GPIO6_FUNC_SPI0_CLK          (1)
#define KERNEL_PIN_GPIO6_FUNC_GPIO              (3)
#define KERNEL_PIN_GPIO6_FUNC_UART1_CTS         (4)
#define KERNEL_PIN_GPIO7_FUNC_SD_DATA0          (0)
#define KERNEL_PIN_GPIO7_FUNC_SPI0_Q_MISO       (1)
#define KERNEL_PIN_GPIO7_FUNC_GPIO              (3)
#define KERNEL_PIN_GPIO7_FUNC_UART1_TXD         (4)
#define KERNEL_PIN_GPIO8_FUNC_SD_DATA1          (0)
#define KERNEL_PIN_GPIO8_FUNC_SPI0_D_MOSI       (1)
#define KERNEL_PIN_GPIO8_FUNC_GPIO              (3)
#define KERNEL_PIN_GPIO8_FUNC_UART1_RXD         (4)
#define KERNEL_PIN_GPIO9_FUNC_SD_DATA2          (0)
#define KERNEL_PIN_GPIO9_FUNC_SPI0_HD           (1)
#define KERNEL_PIN_GPIO9_FUNC_GPIO              (3)
#define KERNEL_PIN_GPIO9_FUNC_SPI1_HD           (4)
#define KERNEL_PIN_GPIO10_FUNC_SD_DATA3         (0)
#define KERNEL_PIN_GPIO10_FUNC_SPI0_WP          (1)
#define KERNEL_PIN_GPIO10_FUNC_GPIO             (3)
#define KERNEL_PIN_GPIO10_FUNC_SPI1_WP          (4)
#define KERNEL_PIN_GPIO11_FUNC_SD_CMD           (0)
#define KERNEL_PIN_GPIO11_FUNC_SPI0_CS0         (1)
#define KERNEL_PIN_GPIO11_FUNC_GPIO             (3)
#define KERNEL_PIN_GPIO11_FUNC_UART1_RTS        (4)
#define KERNEL_PIN_GPIO12_FUNC_MTDI             (0)
#define KERNEL_PIN_GPIO12_FUNC_I2SI_DATA        (1)
#define KERNEL_PIN_GPIO12_FUNC_SPI1_Q_MISO      (2)
#define KERNEL_PIN_GPIO12_FUNC_GPIO             (3)
#define KERNEL_PIN_GPIO12_FUNC_UART0_DTR        (4)
#define KERNEL_PIN_GPIO13_FUNC_MTCK             (0)
#define KERNEL_PIN_GPIO13_FUNC_I2SI_BCK         (1)
#define KERNEL_PIN_GPIO13_FUNC_SPI1_D_MOSI      (2)
#define KERNEL_PIN_GPIO13_FUNC_GPIO             (3)
#define KERNEL_PIN_GPIO13_FUNC_UART0_CTS        (4)
#define KERNEL_PIN_GPIO14_FUNC_MTMS             (0)
#define KERNEL_PIN_GPIO14_FUNC_I2SI_WS          (1)
#define KERNEL_PIN_GPIO14_FUNC_SPI1_CLK         (2)
#define KERNEL_PIN_GPIO14_FUNC_GPIO             (3)
#define KERNEL_PIN_GPIO14_FUNC_UART0_DSR        (4)
#define KERNEL_PIN_GPIO15_FUNC_MTDO             (0)
#define KERNEL_PIN_GPIO15_FUNC_I2SO_BCK         (1)
#define KERNEL_PIN_GPIO15_FUNC_SPI1_CS0         (2)
#define KERNEL_PIN_GPIO15_FUNC_GPIO             (3)
#define KERNEL_PIN_GPIO15_FUNC_UART0_RTS        (4)

#define ON   1
#define OFF  0

#define HIGH 1
#define LOW  0

typedef enum backing(uint8_t) Kernel_Pin_Mode {
    Kernel_Pin_Mode_Output,
    Kernel_Pin_Mode_Input,
} Kernel_Pin_Mode;

void    Kernel_Pin_Init(void);
void    Kernel_Pin_SetFunc(uint8_t const, uint8_t const, uint8_t const);
void    Kernel_Pin_SetMode(uint8_t const, Kernel_Pin_Mode const);
void    Kernel_Pin_Digital_Write(uint8_t const, uint8_t const);
uint8_t Kernel_Pin_Digital_Read(uint8_t const);

#endif /* _ETSSOS_KERNEL_PIN_H_ */
