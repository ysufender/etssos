#include "string.h"

int16_t strncmp(char const* s1, char const* s2, uint32_t n) {
    while (n && *s1 && (*s1 == *s2)) {
        ++s1;
        ++s2;
        --n;
    }
    if (n == 0) {
        return 0;
    }
    else {
        return (*(unsigned char *)s1 - *(unsigned char *)s2);
    }
}

int16_t strcmp(char const* s1, char const* s2) {
    while (*s2 && *s1 && (*s1 == *s2)) {
        ++s1;
        ++s2;
    }
    return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

uint32_t strtoul(char const* str, char** const end, uint8_t const base) {
    uint32_t res = 0;
    for (; *str; str++) {
        res = (res * 10) + (*str - '0');
    }
    (void)base;
    (void)end;
    return res;
}
