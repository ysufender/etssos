#include "memory.h"

void* memcpy(void* const dest, void const* const src, size_t size) {
    for (; size > 0; size--) {
        *(char*)(dest + size - 1) = *(char*)(src + size - 1);
    }

    return dest;
}
