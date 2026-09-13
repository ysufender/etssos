#include "memory.h"

typedef struct LibC_Memory_HeapBlock {
    uint32_t                      size; /* bit 0 is free flag */
    struct LibC_Memory_HeapBlock* next;
} LibC_Memory_HeapBlock;

extern LibC_Memory_HeapBlock _heap_start;
extern LibC_Memory_HeapBlock _heap_end;

static LibC_Memory_HeapBlock* LibC_Memory_HeapHead = 0;

void __init(void) {
    LibC_Memory_HeapHead = &_heap_start;
    LibC_Memory_HeapHead->size = ((uint8_t*)&_heap_end
                                  - (uint8_t*)&_heap_start
                                  - sizeof(LibC_Memory_HeapBlock))
                               << 1;
    LibC_Memory_HeapHead->size |= 1;
    LibC_Memory_HeapHead->next  = 0;
}

void* memcpy(void* const dest, void const* const src, uint32_t const _size) {
    uint32_t size = _size;
    for (; size > 0; size--) {
        *(char*)(dest + size - 1) = *(char*)(src + size - 1);
    }

    return dest;
}

void* malloc(uint32_t const _size) {
    uint32_t size = _size;

    size = (size + 3) & ~3;

    LibC_Memory_HeapBlock* block = LibC_Memory_HeapHead;

    while (block) {
        if ((block->size & 1) && (block->size >> 1) >= size) {
            if ((block->size >> 1) >= size + sizeof(LibC_Memory_HeapBlock) + 4) {
                LibC_Memory_HeapBlock* split = (LibC_Memory_HeapBlock*)
                    ((uint8_t*)block + sizeof(LibC_Memory_HeapBlock) + size);
                split->size  = (block->size >> 1) - size - sizeof(LibC_Memory_HeapBlock);
                split->size |= 1;
                split->next  = block->next;
                block->next  = split;
                block->size  = (size << 1) | (block->size & 1);
            }
            block->size = (size << 1);
            return (void*)((uint8_t*)block + sizeof(LibC_Memory_HeapBlock));
        }
        block = block->next;
    }

    return 0;
}

void free(void* const ptr) {
    if (!ptr) return;

    LibC_Memory_HeapBlock* block = (LibC_Memory_HeapBlock*)
        ((uint8_t*)ptr - sizeof(LibC_Memory_HeapBlock));
    block->size |= 1;

    // coalesce adjacent free blocks
    LibC_Memory_HeapBlock* cur = LibC_Memory_HeapHead;
    while (cur && cur->next) {
        if ((cur->size & 1) && (cur->next->size & 1)) {
            cur->size = (((cur->size >> 1) + sizeof(LibC_Memory_HeapBlock) + (cur->next->size >> 1)) << 1) | 1;
            cur->next  = cur->next->next;
        } else {
            cur = cur->next;
        }
    }
}
