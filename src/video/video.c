#include "video/video.h"
#include "font.h"

framebuffer_t masterFramebuffer = (framebuffer_t) {0};

colorAdapter_t colorAdapter = NULL;
reverseColorAdapter_t reverseColorAdapter = NULL;

uint32_t bga_coloradapter(color_t color) {
	return ((uint32_t)color.r << 16) | ((uint32_t)color.g << 8) | ((uint32_t)color.b);
}

color_t bga_reversecoloradapter(uint32_t color) {
	return (color_t) {
		.r = (color >> 16) & 0xFF,
		.g = (color >> 8) & 0xFF,
		.b = color & 0xFF
	};
}

void video_init(void) {
	colorAdapter = bga_coloradapter;
	reverseColorAdapter = bga_reversecoloradapter;

	masterFramebuffer.address = gBootInfo->framebuffer.address;
	masterFramebuffer.pitch = gBootInfo->framebuffer.pitch;
	masterFramebuffer.bpp = gBootInfo->framebuffer.bpp;
	masterFramebuffer.width = gBootInfo->framebuffer.width;
	masterFramebuffer.height = gBootInfo->framebuffer.height;
}

static inline void isetp(uint32_t x, uint32_t y, uint32_t color) {
	if (x >= masterFramebuffer.width || y >= masterFramebuffer.height) {
		return;
	}

	uint32_t *fb = masterFramebuffer.address;
	int yoff = y * (masterFramebuffer.pitch/4);
	fb[yoff+x] = color;
}

void video_setpixel(uint32_t x, uint32_t y, color_t color) {
	uint32_t c = colorAdapter(color);

	isetp(x, y, c);
}

color_t video_getpixel(uint32_t x, uint32_t y) {
	if (x >= masterFramebuffer.width || y >= masterFramebuffer.height) {
		return (color_t) {
					.r = 0,
					.g = 0,
					.b = 0
				};
	}

	uint32_t *fb = masterFramebuffer.address;
	int yoff = y * (masterFramebuffer.pitch/4);
	return reverseColorAdapter(fb[yoff+x]);
}

void video_rect(uint32_t x, uint32_t y, uint32_t width, uint32_t height, color_t color) {
	uint32_t c = colorAdapter(color);
	for (int h = 0; h < width; h++) {
		isetp(x+h, y, c);
		isetp(x+h, y+height-1, c);
	}

	for (int v = 0; v < height; v++) {
		isetp(x, y+v, c);
		isetp(x+width-1, y+v, c);
	}
}

void video_fillrect(uint32_t x, uint32_t y, uint32_t width, uint32_t height, color_t color) {
	uint32_t c = colorAdapter(color);
	for (int v = 0; v < height; v++) {
		for (int h = 0; h < width; h++) {
			isetp(x+h, y+v, c);
		}
	}
}

void video_printchar(char chr, uint32_t column, uint32_t row, color_t color) {
	uint32_t c = colorAdapter(color);

	uint32_t bx = column * FONT_WIDTH;
	uint32_t by = row * FONT_HEIGHT;

	for (int y = 0; y < FONT_HEIGHT; y++) {
		for (int x = 0; x < FONT_WIDTH; x++) {
			if (FONT_BIT(chr, x, y) != 0) {
				isetp(bx+x, by+y, c);
			}
		}
	}
}
void video_print(const char *s, uint32_t column, uint32_t row, color_t color) {
	int i = 0;
	while (s[i] != '\0') {
		video_printchar(s[i], column+i, row, color);
		i++;
	}
}

