## Kernel in C for Raspberry Pi Zero v1.3

### Prerequisites:
1. A cross compiler for ARM (for example `arm-none-eabi-gcc`)
2. `make`
3. `bear` (Optional, to generate `compile_commands.json` for clangd.

### Build instructions:
Run from repo root:
```
make
```

This generates .o files and a `kernel.elf` in `bin/`, along with a `kernel.img` in `out/`

To generate `compile_commands.json` for clangd, run from repo root:
```
bear -- make -B
```
