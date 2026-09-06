/*
 * THIS FILE IS A PART OF THE ETSSOS PROJECT AND IS LICENSED UNDER THE MIT LICENSE
 * 
 * SEE (LICENSE)[/LICENSE] FOR MORE INFORMATION
 *
 *
 * NAME       : drivers/gpio/gpio.h
 * DESCRIPTION: Basic GPIO driver for 8266
 */

#ifndef _ETSSOS_DRIVERS_GPIO_H_
#define _ETSSOS_DRIVERS_GPIO_H_

#include "../common.h"
#include "../iomux.h"

#define GPIO_PERI    0x60000300
#define GPIO_PIN_CNT 16

#define GPIO_OUT             (*(volatile uint32_t*)(GPIO_PERI + 0x00000000))
#define GPIO_OUT_W1TS        (*(volatile uint32_t*)(GPIO_PERI + 0x00000004))
#define GPIO_OUT_W1TC        (*(volatile uint32_t*)(GPIO_PERI + 0x00000008))
#define GPIO_ENA             (*(volatile uint32_t*)(GPIO_PERI + 0x0000000C))
#define GPIO_ENA_W1TS        (*(volatile uint32_t*)(GPIO_PERI + 0x00000010))
#define GPIO_ENA_W1TC        (*(volatile uint32_t*)(GPIO_PERI + 0x00000014))
#define GPIO_IN              (*(volatile uint32_t*)(GPIO_PERI + 0x00000018))
#define GPIO_STATUS          (*(volatile uint32_t*)(GPIO_PERI + 0x0000001C))
#define GPIO_STATUS_W1TS     (*(volatile uint32_t*)(GPIO_PERI + 0x00000020))
#define GPIO_STATUS_W1TC     (*(volatile uint32_t*)(GPIO_PERI + 0x00000024))
#define GPIO_PIN(__pinnum__) (*(volatile uint32_t*)(GPIO_PERI + ((0x0000000a + (__pinnum__)) * 4)))
#define GPIO_SIGMA_DELTA     (*(volatile uint32_t*)(GPIO_PERI + 0x00000068))
#define GPIO_RTC_CALIB_SYNC  (*(volatile uint32_t*)(GPIO_PERI + 0x0000006C))
#define GPIO_RTC_CALIB_VALUE (*(volatile uint32_t*)(GPIO_PERI + 0x00000070))

typedef enum word_sized GPIO_OUT_BIT {
    GPIO_OUT_BT_SEL = 0xFFFF0000,
    GPIO_OUT_DATA   = 0x0000FFFF,
} GPIO_OUT_BIT;

typedef enum word_sized GPIO_OUT_W1TS_BIT {
    GPIO_OUT_W1TS_W1TS = 0xFFFF0000,
    GPIO_OUT_W1TS_DATA = 0x0000FFFF,
} GPIO_OUT_W1TS_BIT;

typedef enum word_sized GPIO_OUT_W1TC_BIT {
    GPIO_OUT_W1TC_W1TS = 0xFFFF0000,
    GPIO_OUT_W1TC_DATA = 0x0000FFFF,
} GPIO_OUT_W1TC_BIT;

typedef enum word_sized GPIO_ENA_BIT {
    GPIO_ENA_ENA  = 0xFFC00000,
    GPIO_ENA_SEL  = 0x003F0000,
    GPIO_ENA_DATA = 0x0000FFFF,
} GPIO_ENA_BIT;

typedef enum word_sized GPIO_ENA_W1TS_BIT {
    GPIO_ENA_W1TS_W1TS = 0xFFFF0000,
    GPIO_ENA_W1TS_DATA = 0x0000FFFF,
} GPIO_ENA_W1TS_BIT;

typedef enum word_sized GPIO_ENA_W1TC_BIT {
    GPIO_ENA_W1TC_W1TC = 0xFFFF0000,
    GPIO_ENA_W1TC_DATA = 0x0000FFFF,
} GPIO_ENA_W1TC_BIT;

typedef enum word_sized GPIO_IN_BIT {
    GPIO_IN_STRAPPING = 0xFFFF0000,
    GPIO_IN_DATA      = 0x0000FFFF,
} GPIO_IN_BIT;

typedef enum word_sized GPIO_STATUS_BIT {
    GPIO_STATUS_STATUS = 0xFFFF0000,
    GPIO_STATUS_INT    = 0x0000FFFF,
} GPIO_STATUS_BIT;

typedef enum word_sized GPIO_STATUS_W1TS_BIT {
    GPIO_STATUS_W1TS_W1TS = 0xFFFF0000,
    GPIO_STATUS_W1TS_INT  = 0x0000FFFF,
} GPIO_STATUS_W1TS_BIT;

typedef enum word_sized GPIO_STATUS_W1TC_BIT {
    GPIO_STATUS_W1TC_W1TC = 0xFFFF0000,
    GPIO_STATUS_W1TC_INT  = 0x0000FFFF,
} GPIO_STATUS_W1TC_BIT;

typedef enum word_sized GPIO_PIN_BIT {
    GPIO_PIN_PIN     = 0xFFFFF800,
    GPIO_PIN_WKU_ENA = 0x00000400,
    GPIO_PIN_INT_TYP = 0x00000380,
    GPIO_PIN_DRIVER  = 0x00000004,
    GPIO_PIN_DATA    = 0x00000001,
} GPIO_PIN_BIT;

typedef enum word_sized GPIO_SIGMA_DELTA_BIT {
    GPIO_SIGMA_DELTA_ENA    = 0x00010000,
    GPIO_SIGMA_DELTA_PSC    = 0x0000FF00,
    GPIO_SIGMA_DELTA_TARGET = 0x000000FF,
} GPIO_SIGMA_DELTA_BIT;

typedef enum word_sized GPIO_RTC_CALIB_SYNC_BIT {
    GPIO_RTC_CALIB_SYNC_ENA    = 0x80000000,
    GPIO_RTC_CALIB_SYNC_PERIOD = 0x000003FF,
} GPIO_RTC_CALIB_SYNC_BIT;

typedef enum word_sized GPIO_RTC_CALIB_VALUE_BIT {
    GPIO_RTC_CALIB_VALUE_RDY      = 0x80000000,
    GPIO_RTC_CALIB_VALUE_RDY_REAL = 0x40000000,
    GPIO_RTC_CALIB_VALUE_VALUE    = 0x000FFFFF,
} GPIO_RTC_CALIB_VALUE_BIT;

typedef enum backing(uint8_t) GPIO_Mode {
    GPIO_Mode_Input,
    GPIO_Mode_Output,
} GPIO_Mode;

#define GPIO_Read(__pinnum__) ((GPIO_IN >> (__pinnum__)) & 1)
#define GPIO_Enable(__pinnum__, __ena__) IOMUX_SetFunc((__pinnum__), IOMUX_GPIO_FuncVector[(__pinnum__)], (__ena__))

void     GPIO_Init(void);
void     GPIO_SetMode(uint8_t const, GPIO_Mode const);
void     GPIO_Write(uint8_t const, uint16_t const);

#endif /* _ETSSOS_DRIVERS_GPIO_H_ */
