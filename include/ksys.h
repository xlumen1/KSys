#pragma once

#include "types.h"

#define NULL ((void *)0)

struct bootInfo {
	void        *acpiTableAddress;
	uint64_t     memorySize;
	struct {
		void    *address;
		uint64_t size;

		uint32_t width;
		uint32_t height;

		uint32_t pitch;
		uint16_t bpp;

		uint32_t format;
	} framebuffer;
};

extern struct bootInfo *gBootInfo;

