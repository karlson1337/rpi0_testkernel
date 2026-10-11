// SPDX-License-Identifier: GPL-3.0-only

#include <kernel/drivers/timer.h>
#include <kernel/mmio.h>

#define SYSTMR_CLO 0x3004u

void wait_usec(uint32_t usec)
{
    uint32_t start = mmio_read(SYSTMR_CLO);

    while ((uint32_t)(mmio_read(SYSTMR_CLO) - start) < usec) {
    }
}

void sleep(uint32_t sec)
{
    while (sec > 0) {
        wait_usec(1000000);
        --sec;
    }
}
