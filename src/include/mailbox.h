#ifndef MAILBOX_H
#define MAILBOX_H

#include <stdint.h>

enum mailbox_clock {
    MAILBOX_CLOCK_UART = 2
};

/* Blocking firmware query. Call serially, with the MMU/data cache off. */
void mailbox_write(uint32_t message);
uint32_t mailbox_read(uint8_t expected_channel);
#endif
