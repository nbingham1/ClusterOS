#include "multiboot.h"
#include "video.h"
#include "memory.h"

extern "C" void _main(multiboot_info_t *mbd, unsigned int magic);

void _main(multiboot_info_t *mbd, unsigned int magic)
{
	__memory.initialize(mbd, magic);
	__memory.display();

	__video.writestr((char*)"Hello World!!!!\n");
}
