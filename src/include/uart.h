#ifndef UART_H
#define UART_H

#include <stdint.h>

void uart_init();
void uart_putdec(uint32_t v);
void uart_putc(unsigned char c);
unsigned char uart_getc(void);
void uart_puts(const char *str);

#endif
