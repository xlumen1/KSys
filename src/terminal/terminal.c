#include "terminal/terminal.h"
#include "video/video.h"
#include "font.h"
#include "util.h"

#define MAX_TERMINAL_BUFFER (1024 * 1024)
char terminal_buffer[MAX_TERMINAL_BUFFER];

struct terminalData gTerminal = {
	.width = 0,
	.height = 0,
	.size = 0,
	.data = terminal_buffer
};

void terminal_init(void) {
	gTerminal.width = masterFramebuffer.width / FONT_WIDTH;
	gTerminal.height = masterFramebuffer.height / FONT_HEIGHT;
	gTerminal.size = gTerminal.width * gTerminal.height;
	memset(gTerminal.data, 0, MAX_TERMINAL_BUFFER);
}

void terminal_sendchar(char c) {
	switch (c) {
		case 0x08:	// Backspace
			gTerminal.data[gTerminal.cursor_y * gTerminal.width + --gTerminal.cursor_x] = '\0';
			break;
		case 0x0A:	// Line Feed
			gTerminal.cursor_x = 0;
			gTerminal.cursor_y++;
			break;
		default:
			gTerminal.data[gTerminal.cursor_y * gTerminal.width + gTerminal.cursor_x++] = c;
	}

	if (gTerminal.cursor_x >= gTerminal.width) {
		gTerminal.cursor_y += 1;
	}

	gTerminal.cursor_x = gTerminal.cursor_x % gTerminal.width;

	if (gTerminal.cursor_y == gTerminal.height) {
		memmove(gTerminal.data, gTerminal.data + gTerminal.width, gTerminal.width * (gTerminal.height - 1));
		memset(gTerminal.data + ((gTerminal.height - 1) * gTerminal.width), 0, gTerminal.width);
		gTerminal.cursor_y--;
	}
}

void terminal_print(char *string) {
	int i = 0;
	while (string[i] != '\0') {
		terminal_sendchar(string[i++]);
	}
	terminal_flush();
}

void terminal_flush() {
	video_fillrect(0, 0, masterFramebuffer.width, masterFramebuffer.height, (color_t){255,255,255});

	for (size_t i = 0; i < gTerminal.size; i++) {
		if (gTerminal.data[i] == '\0') {
			continue;
		}

		size_t x = i % gTerminal.width;
		size_t y = i / gTerminal.width;

		video_printchar(gTerminal.data[i], x, y, (color_t){0,0,0});
	}
}
