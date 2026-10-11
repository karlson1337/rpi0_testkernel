// SPDX-License-Identifier: GPL-3.0-only

#ifndef MEM_H 
#define MEM_H

#include <stddef.h>

//Copies 'count' bytes from 'source' to 'destination'
void *memcpy(void *destination, const void *source, size_t count);

#endif

