#include "gdt.h"

struct gdt_entry {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_mid;
	uint8_t access;
	uint8_t limit_high:4;
	uint8_t flags:4;
	uint8_t base_high;
} __attribute__((packed));

struct tss_desc {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_mid;
	uint8_t access;
	uint8_t limit_high:4;
	uint8_t flags:4;
	uint8_t base_high;
	uint32_t base_upper;
	uint32_t :32; // Cursed Padding
} __attribute__((packed));

struct gdt_ptr {
	uint16_t limit;
	uint64_t base;
} __attribute__((packed));

struct gdt {
	struct gdt_entry entries[5];
	struct tss_desc  tss;
} __attribute__((packed, aligned(8)));

_Static_assert(sizeof(struct gdt_entry) == 8, "gdt_entry size");
_Static_assert(sizeof(struct tss_desc) == 16, "tss_desc size");

static struct gdt gdt;
static struct gdt_ptr gdtr;

extern void gdt_flush(struct gdt_ptr *);

static void set_entry(int i, uint8_t access, uint8_t flags) {
	gdt.entries[i] = (struct gdt_entry){
		.limit_low = 0xFFFF,
		.limit_high = 0xF,
		.access = access,
		.flags = flags
	};
}

void gdt_init(void) {
	gdt.entries[0] = (struct gdt_entry){0}; // Null
	
	set_entry(1, 0x9A, 0xA); // Kernel Code
	set_entry(2, 0x92, 0xC); // Kernel Data
	set_entry(3, 0xF2, 0xC); // User Data
	set_entry(4, 0xFA, 0xA); // User Code
	
	gdtr.limit = sizeof(gdt) - 1;
	gdtr.base = (uint64_t)&gdt;
	gdt_flush(&gdtr);
}
