#ifndef MAILBOX_H
#define MAILBOX_H

#include <stdint.h>

enum mailbox_clock {
    MAILBOX_CLOCK_UART = 2
};
typedef struct {
    uint8_t channel: 4;
    uint32_t data: 28;
} mail_message_t;

typedef struct {
    uint32_t reserved: 30;
    uint8_t empty: 1;
    uint8_t full:1;
} mail_status_t;

void mailbox_write(uint32_t message);
uint32_t mailbox_read(uint8_t expected_channel);
#endif
