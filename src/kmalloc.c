#include "include/mailbox.h"
#include "include/uart.h"

#include <stdint.h>

void init_kmalloc()
{
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

    uint32_t mem_base;
    uint32_t mem_size;
    if(!(response != message))
    {
        mem_base = mbox[5];
        mem_size = mbox[6];
    }
    uart_puthex(mem_size);
}

void *kmalloc(size_t bytes)
{

}

