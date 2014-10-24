#include "multiboot.h"
#include "kvideo.h"
#include "kdescriptor_tables.h"
#include "timer.h"

extern "C" void _main(multiboot_info_t *mbd, unsigned int magic);

void _main(multiboot_info_t *mbd, unsigned int magic)
{
	kdt_init();
	init_timer(100);
	enable_interrupts();
	kcls();
}
