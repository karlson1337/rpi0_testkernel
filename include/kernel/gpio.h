// SPDX-License-Identifier: GPL-3.0-only

#ifndef GPIO_H
#define GPIO_H

enum gpio_function {
    GPIO_INPUT = 0,
    GPIO_OUTPUT = 1,
    GPIO_ALT0 = 4
};

enum gpio_pull {
    GPIO_PULL_NONE = 0,
    GPIO_PULL_DOWN = 1,
    GPIO_PULL_UP = 2
};

void gpio_set_function(int pin, enum gpio_function function);
void gpio_set_pull(int pin, enum gpio_pull pull);
void gpio_set_output(int pin);
void gpio_high(int pin);
void gpio_low(int pin);

#endif
