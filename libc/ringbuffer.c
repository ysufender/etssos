#include "ringbuffer.h"

#include "memory.h"

LibC_RingBuffer LibC_RingBuffer_Create(uint16_t const size) {
    return (LibC_RingBuffer){
        .size = size,
        .data = malloc(size),
        .head = 0,
        .tail = 0,
    };
}

uint8_t LibC_RingBuffer_Push(LibC_RingBuffer* const ring, uint8_t const byte) {
    uint16_t const next = ring->head >= ring->size
                        ? 0
                        : ring->head + 1;

    if (next == ring->tail) {
        return 0;
    }

    ring->data[ring->head] = byte;
    ring->head = next;
    return 1;
}

uint8_t LibC_RingBuffer_Pop(LibC_RingBuffer* const ring, uint8_t* const byte) {
    if (ring->head == ring->tail) {
        return 0;
    }
    *byte = ring->data[ring->tail];
    ring->tail += ring->tail >= ring->size
               ?  -ring->tail
               : 1;
    return 1;
}

uint8_t LibC_RingBuffer_Empty(LibC_RingBuffer* const ring) {
    return ring->tail == ring->head;
}

uint8_t LibC_RingBuffer_Peek(LibC_RingBuffer* const ring, uint8_t* const byte) {
    if (ring->head == ring->tail) {
        return 0;
    }
    *byte = ring->data[ring->tail];
    return 1;
}
