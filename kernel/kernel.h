/*
 * THIS FILE IS A PART OF THE ETSSOS PROJECT
 * AND IS LICENSED UNDER THE MIT LICENSE
 * 
 * SEE (LICENSE)[/LICENSE] FOR MORE INFORMATION
 *
 *
 * NAME       : kernel/kernel.h
 * DESCRIPTION: Basic kernel implementation fo 8266
 */

#ifndef _ETSSOS_KERNEL_H_
#define _ETSSOS_KERNEL_H_

#include <stdint.h>

void Kernel_Kernel_Main(void);
void Kernel_Kernel_DumpInfo(void);
void Kernel_Kernel_Panic(void);
void Kernel_Kernel_Panic_Unreachable(void);
void Kernel_Kernel_Panic_Debug(void);

#endif /* _ETSSOS_KERNEL_H_ */
