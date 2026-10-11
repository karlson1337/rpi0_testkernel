# SPDX-License-Identifier: GPL-3.0-only

CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

CFLAGS = -mcpu=arm1176jzf-s -fpic -ffreestanding -std=gnu99 -O2 -Wall -Wextra -Iinclude
ASFLAGS = -mcpu=arm1176jzf-s -fpic -ffreestanding
LDFLAGS = -mcpu=arm1176jzf-s -T src/linker.ld -ffreestanding -nostdlib

S_SOURCES := $(wildcard src/*.S)
C_SOURCES := $(wildcard src/*.c)
OBJECTS := $(patsubst src/%.S,bin/%.o,$(S_SOURCES)) \
           $(patsubst src/%.c,bin/%.o,$(C_SOURCES))

.PHONY: all
all: out/kernel.img

out/kernel.img: bin/kernel.elf | out
	$(OBJCOPY) -O binary $< $@

bin/kernel.elf: $(OBJECTS) src/linker.ld Makefile | bin
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) -lgcc

bin/%.o: src/%.c Makefile | bin
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

bin/%.o: src/%.S Makefile | bin
	$(CC) $(CPPFLAGS) $(ASFLAGS) -MMD -MP -c $< -o $@

bin out:
	mkdir -p $@

clean:
	rm -r bin/
	rm out/kernel.img

-include $(OBJECTS:.o=.d)
