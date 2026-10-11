// SPDX-License-Identifier: GPL-3.0-only

#include <kernel/mailbox.h>
#include <kernel/uart.h>

#include <stdint.h>

void init_kmalloc()
{
    extern uint32_t __bss_end;
    
    static volatile uint32_t __attribute__((aligned(16))) mbox[] = {
        32,          // total message size: 8 words
        0,           // request
        0x00010005,  // get free RAM
        8,           // value buffer size
        0,           // tag request code
        0,           // returned base address
        0,           // returned size in bytes
        0            // end tag
        };

    uint32_t message = ((uint32_t)(uintptr_t)mbox & ~0xFu) | 8u;
    mailbox_write(message);

    uint32_t response = mailbox_read(8);

    uint32_t mem_base = 0;
    uint32_t mem_size = 0;
    if(!(response != message))
    {
        mem_base = mbox[5];
        mem_size = mbox[6];
    }
    
    
    uint32_t usable_mem = mem_base + mem_size - (uint32_t)&__bss_end;

    uart_puts("Usable memory (bytes): ");
    uart_putdec(usable_mem);
    uart_puts("\r\n");
}

void *kmalloc(size_t bytes)
{

}

