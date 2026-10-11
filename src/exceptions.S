.section .text.exceptions, "ax"
.align 2

.global reset_handler
.global undef_handler
.global svc_handler
.global pabort_handler
.global dabort_handler
.global reserved_handler
.global irq_handler
.global fiq_handler

reset_handler:
undef_handler:
svc_handler:
pabort_handler:
dabort_handler:
reserved_handler:
irq_handler:
fiq_handler:
    b .
