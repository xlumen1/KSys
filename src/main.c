#include "ksys.h"
#include "video/video.h"
#include "terminal/terminal.h"

struct bootInfo *gBootInfo;

void kmain(struct bootInfo *kbp_bootinfo) {
	gBootInfo = kbp_bootinfo;

	video_init();
	terminal_init();

	terminal_print(" _______\n");
	terminal_print("< KSys! >\n");
	terminal_print(" -------\n");
	terminal_print("        \\   ^__^\n");
	terminal_print("         \\  (oo)\\_______\n");
	terminal_print("            (__)\\       )\\/\\\n");
	terminal_print("                ||----w |\n");
	terminal_print("                ||     ||\n");

	for (int i = 0; i < 2600; i++) {
		terminal_sendchar('A'+(i%26));
		terminal_flush();
	}

	for (;;) {} ;
}
