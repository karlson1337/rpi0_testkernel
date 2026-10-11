// SPDX-License-Identifier: GPL-3.0-only

#include <kernel/gpio.h>
#include <kernel/mmio.h>
#include <kernel/timer.h>

enum {
    GPIO_BASE = 0x200000,
    GPFSEL0 = GPIO_BASE + 0x00,
    GPSET0 = GPIO_BASE + 0x1C,
    GPCLR0 = GPIO_BASE + 0x28,
    GPPUD = GPIO_BASE + 0x94,
    GPPUDCLK0 = GPIO_BASE + 0x98
};

static int valid_pin(int pin)
{
    return pin >= 0 && pin <= 53;
}

void gpio_set_function(int pin, enum gpio_function function)
{
    if (!valid_pin(pin)) return;
    uint32_t reg = GPFSEL0 + (pin / 10) * 4;
    uint32_t shift = (pin % 10) * 3;
    uint32_t value = mmio_read(reg);
    value &= ~(7u << shift);
    value |= ((uint32_t)function & 7u) << shift;
    mmio_write(reg, value);
}

void gpio_set_pull(int pin, enum gpio_pull pull)
{
    if (!valid_pin(pin)) return;
    uint32_t reg = GPPUDCLK0 + (pin / 32) * 4;
    mmio_write(GPPUD, (uint32_t)pull);
    wait_usec(5);
    mmio_write(reg, 1u << (pin % 32));
    wait_usec(5);
    mmio_write(GPPUD, 0);
    mmio_write(reg, 0);
}

void gpio_set_output(int pin)
{
    gpio_set_function(pin, GPIO_OUTPUT);
}

void gpio_high(int pin)
{
    if (!valid_pin(pin)) return;
    mmio_write(GPSET0 + (pin / 32) * 4, 1u << (pin % 32));
}

void gpio_low(int pin)
{
    if (!valid_pin(pin)) return;
    mmio_write(GPCLR0 + (pin / 32) * 4, 1u << (pin % 32));
}
