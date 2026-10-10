#include <stddef.h>

//Prototype in include/mem.h

void *memcpy(void *destination, const void *source, size_t count)
{
    unsigned char *dst = destination;
    const unsigned char *src = source;

    for (size_t i = 0; i < count; i++)
        dst[i] = src[i];

    return destination;
}
