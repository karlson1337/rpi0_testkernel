#!/usr/bin/env bash

qemu-system-arm -m 512 -M raspi0 -serial stdio -display none -kernel bin/kernel.elf
