// SPDX-License-Identifier: GPL-3.0-only

#include <kernel/drivers/gpio.h>
#include <kernel/drivers/timer.h>
#include <kernel/drivers/uart.h>
#include <kernel/memory/alloc.h>

#include <stdint.h>

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{

    (void)r0;
    (void)r1;
    (void)atags;

    
    uart_init();
    
    //query __bss_end and free RAM;
    init_kmalloc();

    uart_puts("Hello, kernel World!\r\n");

    // ACT LED blink sequence.
    // Why just why does low turn it on lol
    gpio_set_output(47);
    gpio_low(47);
    sleep(1);
    gpio_high(47);


    while (1) {
    char buf[100];
    uart_gets(buf, sizeof(buf));
    uart_puts(buf);
    }
}
