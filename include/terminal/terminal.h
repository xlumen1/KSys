#pragma once

#include "../ksys.h"
#include "../types.h"

#define MAX_TERMINAL_BUFFER (1024 * 1024)

struct terminalData {
	uint16_t width;
	uint16_t height;
	size_t size;
	char *data;
	uint16_t cursor_x;
	uint16_t cursor_y;
};

extern struct terminalData gTerminal;

void terminal_init(void);

void terminal_sendchar(char c);
void terminal_print(char *string);
void terminal_flush();

