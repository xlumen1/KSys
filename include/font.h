#pragma once
#include "types.h"

#define FONT_HEIGHT 8
#define FONT_WIDTH 6

#define FONT_BIT(c, column, row) \
		(font_data[((uint8_t)c*FONT_WIDTH)+column]&(1<<row))

extern const uint8_t font_data[];

