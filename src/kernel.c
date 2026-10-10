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
    uart_puts("\nHello, kernel World!\r\n");

    // ACT LED blink sequence.
    gpio_set_output(47);
    gpio_low(47);
    sleep(1);
    gpio_high(47);

    while (1) {
        uart_putc(uart_getc());
    }
}
