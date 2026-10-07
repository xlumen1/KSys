#pragma once

#include "types.h"

#define GDT_KERNEL_CODE 0x08
#define GDT_KERNEL_DATA 0x10
#define GDT_USER_DATA	(0x18 | 3) // RPL 3
#define GDT_USER_CODE	(0x20 | 3) // RPL 3
#define GDT_TSS			0x28

void gdt_init(void);

