// SPDX-License-Identifier: GPL-3.0-only

#ifndef KMALLOC_H
#define KMALLOC_H

#include <stddef.h>
#include <stdint.h>

void init_kmalloc();

uintptr_t virt_to_phys(const void *virt);
void *phys_to_virt(uintptr_t phys);

uintptr_t page_alloc(void);
void page_free(uintptr_t phys);
void *kmalloc(size_t bytes);
void kfree(void *ptr);

#endif
