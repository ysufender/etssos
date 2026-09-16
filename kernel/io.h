/*
 * THIS FILE IS A PART OF THE ETSSOS PROJECT
 * AND IS LICENSED UNDER THE MIT LICENSE
 * 
 * SEE (LICENSE)[/LICENSE] FOR MORE INFORMATION
 *
 *
 * NAME       : kernel/io.h
 * DESCRIPTION: UART IO utilities
 */

#ifndef _ETSSOS_KERNEL_IO_H_
#define _ETSSOS_KERNEL_IO_H_

#include <stdint.h>

typedef struct Kernel_IO {
    void    (*stdout)(uint8_t const);
    uint8_t (*stdin)(uint8_t* const);
} Kernel_IO;

extern Kernel_IO Kernel_IO_Uart;

void     Kernel_IO_Init(void);
void     Kernel_IO_PrintFormat(char const* const, ...);
void     Kernel_IO_PutString(char const* const);
void     Kernel_IO_PutStringLine(char const* const);
void     Kernel_IO_PutChar(char const);
void     Kernel_IO_Flush(void);
uint32_t Kernel_IO_GetString(char* const, uint32_t const);
uint8_t  Kernel_IO_GetChar(void);

#endif /* _ETSSOS_KERNEL_IO_H_ */
