#include "memory.h"

void *memcpy(void *dest, const void *src, uint32_t n) {
	uint8_t *d = dest;
	const uint8_t *s = src;
	while (n--) *d++ = *s++;
	return dest;
}

void *memset(void *dest, uint8_t c, uint32_t n) {
	uint8_t *d = dest;
	while (n--) *d++ = c;
	return dest;
}

void *memmove(void *dest, const void *src, uint32_t n) {
	uint8_t *d = dest;
	const uint8_t *s = src;

	if (d == s || n == 0) {
		return dest;
	}

	if (d > s && d < s + n) {
		for (uint32_t i = n; i > 0; i--) {
			d[i - 1] = s[i - 1];
		}
	} else {
		for (uint32_t i = 0; i < n; i++) {
			d[i] = s[i];
		}
	}

	return dest;
}

