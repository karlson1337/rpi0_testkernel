// SPDX-License-Identifier: GPL-3.0-only

#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

void wait_usec(uint32_t usec);
void sleep(uint32_t sec);

#endif
