// SPDX-License-Identifier: GPL-3.0-only

#ifndef MMIO_H
#define MMIO_H

#include <stdint.h>

#define MMIO_BASE 0x20000000u

//Writes 'value' to the 'offset' from MMIO_BASE 
static inline void mmio_write(uint32_t offset, uint32_t value)
{
    *(volatile uint32_t *)(MMIO_BASE + offset) = value;
}

//Reads data from 'offset' from MMIO_BASE and returns it
static inline uint32_t mmio_read(uint32_t offset)
{
    return *(volatile uint32_t *)(MMIO_BASE + offset);
}

#endif
