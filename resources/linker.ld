ENTRY(_start)

KERNEL_ORIGIN = 0x100000;

SECTIONS {
	. = KERNEL_ORIGIN;

	.text : ALIGN(16) {
		*(.text.entry)
		*(.text*)
	}

	.rodata : ALIGN(16) { *(.rodata*) }
	.data   : ALIGN(16) { *(.data*) }

	.bss : ALIGN(16) {
		__bss_start = .;
		*(.bss*)
		*(COMMON)
		__bss_end = .;
	}
}

