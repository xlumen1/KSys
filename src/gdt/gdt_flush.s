.section .text

.global gdt_flush
.type gdt_flush, @function
gdt_flush:
	lgdt (%rdi)
	movw $0x10, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	movw %ax, %ss

	popq %rax
	pushq $0x08
	pushq %rax
	lretq
