// SPDX-License-Identifier: GPL-3.0-only

// AArch32 startup for the BCM2835 / ARM1176.
.section ".text.boot", "ax"
.globl _start
.type _start, %function

// The linker places this section at 0x8000, with _start at its beginning.
_start:
	// The initial stack grows down from the address defined in .section .bss.stack
	ldr sp, =stack_top
	cpsid if

	// Preserve the firmware arguments while installing the vector table.
	mov r10, r0
	mov r11, r1
	mov r12, r2

	// Copy eight vector instructions and their eight literal handler addresses
	// to low vectors (0x00000000..0x0000003f). Each vector uses LDR pc,[pc,#24].
	ldr r0, =vectors
	mov r1, #0
	mov r2, #16
1:
	ldr r3, [r0], #4
	str r3, [r1], #4
	subs r2, r2, #1
	bne 1b

	// Select low vectors and flush the instruction prefetch buffer.
	mrc p15, 0, r0, c1, c0, 0
	bic r0, r0, #(1 << 13)		// SCTLR.V = 0
	mcr p15, 0, r0, c1, c0, 0
	mov r0, #0
	mcr p15, 0, r0, c7, c5, 4

	// Clear BSS. __bss_end is page-aligned by the linker, so this word loop
	// covers the complete range.
	ldr r4, =__bss_start
	ldr r9, =__bss_end
	mov r5, #0
	mov r6, #0
	mov r7, #0
	mov r8, #0
	b 3f
2:
	stmia r4!, {r5-r8}
3:
	cmp r4, r9
	blo 2b

	// Restore the firmware's entry arguments and enter C.
	mov r0, r10
	mov r1, r11
	mov r2, r12
	bl kernel_main

halt:
	wfe
	b halt
.size _start, . - _start

// Low-vector table. The literal words are part of the copied 64-byte table.
.section .vectors, "ax"
.align 5
.global vectors
vectors:
	ldr pc, [pc, #24]		// 0x00 Reset
	ldr pc, [pc, #24]		// 0x04 Undefined instruction
	ldr pc, [pc, #24]		// 0x08 SVC
	ldr pc, [pc, #24]		// 0x0C Prefetch abort
	ldr pc, [pc, #24]		// 0x10 Data abort
	ldr pc, [pc, #24]		// 0x14 Reserved
	ldr pc, [pc, #24]		// 0x18 IRQ
	ldr pc, [pc, #24]		// 0x1C FIQ
	.word reset_handler
	.word undef_handler
	.word svc_handler
	.word pabort_handler
	.word dabort_handler
	.word reserved_handler
	.word irq_handler
	.word fiq_handler

//Stack size setup
.section .bss.stack, "aw", %nobits
.balign 16
stack_bottom:
    .space 16384
stack_top:
