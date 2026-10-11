// SPDX-License-Identifier: GPL-3.0-only

#include <kernel/mailbox.h>
#include <kernel/mmio.h>

enum {
    MBOX_BASE   = 0xB880,
    MBOX_READ   = MBOX_BASE + 0x00,
    MBOX_STATUS = MBOX_BASE + 0x18,
    MBOX_WRITE  = MBOX_BASE + 0x20,
    MBOX_FULL   = (1u << 31),
    MBOX_EMPTY  =  (1u << 30)
};

void mailbox_write(uint32_t message)
{
    // Wait until the hardware can accept a word.
    while (mmio_read(MBOX_STATUS) & MBOX_FULL) {}

    mmio_write(MBOX_WRITE, message);
}

uint32_t mailbox_read(uint8_t expected_channel)
{
    uint32_t message;

    for (;;) 
    {
        // Wait until a word is available.
        while (mmio_read(MBOX_STATUS) & MBOX_EMPTY) {}

        message = mmio_read(MBOX_READ);

        // The channel is in bits 0-3. Data is in bits 4-31.
        if ((message & 0xFu) == expected_channel) { return message; }
    }
}
