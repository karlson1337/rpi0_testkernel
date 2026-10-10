#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stddef.h>

void uart_init();
void uart_putdec(uint32_t v);
void uart_putc(unsigned char c);
unsigned char uart_getc(void);
void uart_puts(const char *str);

//Reads n bytes from UART into str (or until \n)
char *uart_gets(char *str, size_t n);

#endif
