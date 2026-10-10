#include <stdint.h>

#include "include/gpio.h"
#include "include/timer.h"
#include "include/uart.h"

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{
    (void)r0;
    (void)r1;
    (void)atags;

    uart_init();
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
