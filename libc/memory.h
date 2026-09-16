/*
 * THIS FILE IS A PART OF THE ETSSOS PROJECT AND IS LICENSED UNDER THE MIT LICENSE
 * 
 * SEE (LICENSE)[/LICENSE] FOR MORE INFORMATION
 *
 *
 * NAME       : libc/memory.h
 * DESCRIPTION: Small libc memory utilities implementation
 */

#ifndef _ETSSOS_LIBC_MEMORY_H_
#define _ETSSOS_LIBC_MEMORY_H_

#include <stdint.h>

typedef struct LibC_Memory_HeapBlock {
    uint32_t                      size; /* bit 0 is free flag */
    struct LibC_Memory_HeapBlock* next;
} LibC_Memory_HeapBlock;

void* memcpy(void* const, void const* const, uint32_t const);
void* malloc(uint32_t const);
void  free(void* const);

#endif /* _ETSSOS_LIBC_MEMORY_H_ */
