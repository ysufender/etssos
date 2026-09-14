/*
 * THIS FILE IS A PART OF THE ETSSOS PROJECT AND IS LICENSED UNDER THE MIT LICENSE
 * 
 * SEE (LICENSE)[/LICENSE] FOR MORE INFORMATION
 *
 *
 * NAME       : libc/ringbuffer.h
 * DESCRIPTION: Byte based ring buffer implementation
 */

#ifndef _ETSSOS_LIBC_RINGBUFFER_H_
#define _ETSSOS_LIBC_RINGBUFFER_H_

#include <stdint.h>

typedef struct LibC_RingBuffer {
    uint8_t* data;
    uint16_t  head;
    uint16_t  tail;
    uint16_t  size;
} LibC_RingBuffer;

#define LibC_RingBuffer_Default (LibC_RingBuffer){ 0, 0, 0, 0 }

LibC_RingBuffer LibC_RingBuffer_Create(uint16_t const);
uint8_t         LibC_RingBuffer_Push(LibC_RingBuffer* const, uint8_t const);
uint8_t         LibC_RingBuffer_Pop(LibC_RingBuffer* const, uint8_t* const);
uint8_t         LibC_RingBuffer_Empty(LibC_RingBuffer* const);
uint8_t         LibC_RingBuffer_Peek(LibC_RingBuffer* const, uint8_t* const);

#endif /* _ETSSOS_LIBC_RINGBUFFER_H_ */
