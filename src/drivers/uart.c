// SPDX-License-Identifier: GPL-3.0-only

#include <kernel/drivers/uart.h>
#include <kernel/drivers/gpio.h>
#include <kernel/drivers/mailbox.h>
#include <kernel/mmio.h>

#include <stddef.h>
#include <stdint.h>

enum {
    UART0_BASE = 0x201000,
    UART0_DR = UART0_BASE + 0x00,
    UART0_FR = UART0_BASE + 0x18,
    UART0_IBRD = UART0_BASE + 0x24,
    UART0_FBRD = UART0_BASE + 0x28,
    UART0_LCRH = UART0_BASE + 0x2C,
    UART0_CR = UART0_BASE + 0x30,
    UART0_IMSC = UART0_BASE + 0x38,
    UART0_ICR = UART0_BASE + 0x44
};

void uart_init()
{
    while (mmio_read(UART0_FR) & (1u << 3)) { }
    mmio_write(UART0_CR, 0);

    gpio_set_function(14, GPIO_ALT0);
    gpio_set_function(15, GPIO_ALT0);
    gpio_set_pull(14, GPIO_PULL_NONE);
    gpio_set_pull(15, GPIO_PULL_NONE);
    mmio_write(UART0_ICR, 0x7FF);

    //Get clock rate
    static volatile uint32_t __attribute__((aligned(16))) mbox[] = {
    32,          // total message size: 8 words
    0,           // request
    0x00030002,  // get clock rate
    8,           // value buffer size
    0,           // tag request code
    0,    // clock ID
    0,           // returned rate
    0            // end tag
    };
    mbox[5] = MAILBOX_CLOCK_UART;

    uint32_t message = ((uint32_t)(uintptr_t)mbox & ~0xFu) | 8u;
    mailbox_write(message);

    uint32_t response = mailbox_read(8);
    uint32_t clock = 0;

    if (!(response != message ||
    mbox[1] != 0x80000000u ||
    (mbox[4] & 0x80000000u) == 0))
    { clock = mbox[6]; }

    else { for (;;) { __asm__ volatile("wfe"); } }

    /* Baud divider in units of 1/64, rounded to the nearest unit. */
    uint32_t divisor = (clock * 4u + 115200u / 2u) / 115200u;
    mmio_write(UART0_IBRD, divisor / 64u);
    mmio_write(UART0_FBRD, divisor % 64u);

    mmio_write(UART0_LCRH, (1u << 4) | (1u << 5) | (1u << 6));
    mmio_write(UART0_IMSC, 0);
    mmio_write(UART0_CR, (1u << 0) | (1u << 8) | (1u << 9));

    uart_puts("UART clock rate (Hz): ");
    uart_putdec(clock);
    uart_puts("\r\n");
}

void uart_putdec(uint32_t v)
{
    char buf[11];
    int i = 10;
    buf[i] = '\0';
    do {
        buf[--i] = '0' + (v % 10);
        v /= 10;
    } while (v);
    uart_puts(&buf[i]);
}

void uart_puthex(unsigned int value) {
    char hex_digits[] = "0123456789ABCDEF";
    
    // Print the hexadecimal prefix
    uart_putc('0');
    uart_putc('x');
    
    // Loop through all 8 nibbles (4 bits each) of a 32-bit integer, starting from the top
    for (int i = 28; i >= 0; i -= 4) {
        int nibble = (value >> i) & 0xF;
        uart_putc(hex_digits[nibble]);
    }
}

void uart_putc(unsigned char c)
{
    while (mmio_read(UART0_FR) & (1u << 5)) { }
    mmio_write(UART0_DR, c);
}

unsigned char uart_getc(void)
{
    while (mmio_read(UART0_FR) & (1u << 4)) { }
    return (unsigned char)mmio_read(UART0_DR);
}

void uart_puts(const char *str)
{
    while (*str) uart_putc((unsigned char)*str++);
}

char *uart_gets(char *str, size_t n)
{
    if (n == 0)
        return str;

    size_t i = 0;
    while (i < n - 1) 
    {
        char c = (char)uart_getc();

        if (c == '\r') 
        {
            str[i++] = '\n';
            break;
        }
        str[i++] = c;

        if (c == '\n')
            break;        
    }
    str[i] = '\0';
    return str;
}
