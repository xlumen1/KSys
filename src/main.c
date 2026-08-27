#include "ksys.h"
#include "video/video.h"

struct bootInfo *gBootInfo;

void kmain(struct bootInfo *kbp_bootinfo) {
	gBootInfo = kbp_bootinfo;

	video_init();

	video_fillrect(0, 0, masterFramebuffer.width, masterFramebuffer.height, (color_t){
			.r = 255,
			.g = 255,
			.b = 255
	});

	color_t font_color = (color_t) {
		.r = 0,
		.g = 0,
		.b = 0
	};

	video_print("KSys Initialized", 0, 0, font_color);

	for (;;) {} ;
}
