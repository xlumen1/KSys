#pragma once

#include "types.h"

#define NULL ((void *)0)

struct bootInfo {
	void         *acpiTableAddress;
	struct {
		void     *address;
		uint64_t  size;

		uint32_t  width;
		uint32_t  height;

		uint32_t  pitch;
		uint16_t  bpp;

		uint32_t  format;
	} framebuffer;
	struct {
		void     *memoryMap;
		uint64_t *memoryMapSize;
		uint64_t *memoryMapDescSize;
		uint32_t *memoryMapDescVersion;
	} memory;
};

struct memoryDescriptor {
	uint32_t type;
	uint32_t pad;
	uint64_t physicalStart;
	uint64_t virtualStart;
	uint64_t numberOfPages;
	uint64_t attribute;
};

extern struct bootInfo *gBootInfo;

