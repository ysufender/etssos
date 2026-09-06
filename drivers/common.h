/*
 * THIS FILE IS A PART OF THE ETSSOS PROJECT
 * AND IS LICENSED UNDER THE MIT LICENSE
 * 
 * SEE (LICENSE)[/LICENSE] FOR MORE INFORMATION
 *
 *
 * NAME       : drivers/common.h
 * DESCRIPTION: Common definitions for all drivers
 */

#ifndef _ETSSOS_DRIVERS_COMMON_H_
#define _ETSSOS_DRIVERS_COMMON_H_

#include <stdint.h>

#define backing(x) __attribute__((aligned(sizeof(x))))
#define word_sized backing(uint32_t)

#endif /* _ETSSOS_DRIVERS_COMMON_H_ */
