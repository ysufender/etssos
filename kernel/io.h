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

void Kernel_IO_Init(void);

void Kernel_IO_PrintFormat(char const* const, ...);
void Kernel_IO_PutString(char const* const);
void Kernel_IO_PutStringLine(char const* const);

#endif /* _ETSSOS_KERNEL_IO_H_ */
