.section .bss
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text.entry

.global _start
.type _start, @function
_start:
	mov $stack_top, %rsp
	cli

	jmp kmain

	hlt
	jmp .
