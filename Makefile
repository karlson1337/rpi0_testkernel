CC = arm-none-eabi-gcc

all: 
	$(CC) -mcpu=arm1176jzf-s -fpic -ffreestanding -c src/boot.S -o bin/boot.o
	$(CC) -mcpu=arm1176jzf-s -fpic -ffreestanding -std=gnu99 -c src/kernel.c -o bin/kernel.o -O2 -Wall -Wextra
	$(CC) -T src/linker.ld -o bin/kernel.elf -ffreestanding -O2 -nostdlib bin/boot.o bin/kernel.o -lgcc
	arm-none-eabi-objcopy -O binary bin/kernel.elf out/kernel.img
