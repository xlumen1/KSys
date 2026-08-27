#pragma once

#include "../ksys.h"
#include "../types.h"

typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} color_t;

typedef struct {
	void *address;

	uint32_t width;
	uint32_t height;

	uint32_t pitch;
	uint16_t bpp;
} framebuffer_t;

typedef uint32_t (*colorAdapter_t)(color_t);
typedef color_t (*reverseColorAdapter_t)(uint32_t);

extern framebuffer_t masterFramebuffer;

extern colorAdapter_t colorAdapter;
extern reverseColorAdapter_t reverseColorAdapter;

void video_init(void);

void video_setpixel(uint32_t x, uint32_t y, color_t color);
color_t video_getpixel(uint32_t x, uint32_t y);

void video_rect(uint32_t x, uint32_t y, uint32_t width, uint32_t height, color_t color);
void video_fillrect(uint32_t x, uint32_t y, uint32_t width, uint32_t height, color_t color);

void video_printchar(char c, uint32_t column, uint32_t row, color_t color);
void video_print(const char *s, uint32_t column, uint32_t row, color_t color);

