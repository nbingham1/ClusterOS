#include "memory.h"
#include "video.h"

memory __memory;

memory::memory()
{
	boot_info = 0x0;
	magic_number = 0;
}
memory::~memory()
{
}

void memory::initialize(multiboot_info_t *mbd, unsigned int magic)
{
	__video.writestr((char *)"Initializing Random Access Memory...");
	boot_info = mbd;
	magic_number = magic;
	extern char start;
	extern char end;
	kern_start = (unsigned long long int)&start;
	kern_end = (unsigned long long int)&end;
	__video.writestr((char *)"  [ done ]\n");
}

void memory::display()
{
	memory_map_t* mmap = (memory_map_t*)boot_info->mmap_addr;
	while ((unsigned int)mmap < boot_info->mmap_addr + boot_info->mmap_length - 40)
	{
		__video.writenum((char)mmap->size, 10);
		__video.writestr((char*)" ");

		__video.writeaddr(mmap->base_addr);
		__video.writestr((char*)" ");

		__video.writenum(mmap->length, 10);
		__video.writestr((char*)" ");

		__video.writenum(mmap->type, 16);
		__video.writestr((char*)"\n");

		mmap = (memory_map_t*)((unsigned int)mmap + mmap->size + sizeof(unsigned int));
	}

	__video.writestr((char*)"Start of Kernel: ");
	__video.writeaddr(kern_start);
	__video.writestr((char*)"\n");
	__video.writestr((char*)"End of Kernel: ");
	__video.writeaddr(kern_end);
	__video.writestr((char*)"\n");
	__video.writestr((char*)"Size of Kernel: ");
	__video.writenum(kern_end - kern_start, 10);
	__video.writestr((char*)"\n");
}
