#include "memory.h"
#include "video.h"

memory __memory;

memory::memory()
{
	boot_info = NULL;
	magic_number = 0;
	free_memory = NULL;
	used_memory = NULL;
	kern_start = NULL;
	kern_end = NULL;
}
memory::~memory()
{
}

void memory::initialize(multiboot_info_t *mbd, unsigned int magic)
{
	__video.writestr((char *)"Initializing Memory Manager...");
	boot_info = mbd;
	magic_number = magic;
	extern char start;
	extern char end;
	kern_start = (addr_t)&start;
	kern_end = (addr_t)&end;

	free_memory = NULL;
	memory_map_t *mmap = (memory_map_t*)boot_info->mmap_addr;
	mem_header_t *header = NULL;
	while ((unsigned int)mmap < boot_info->mmap_addr + boot_info->mmap_length - 40)
	{
		if (mmap->base_addr >= kern_start && mmap->type == 1)
		{
			if (free_memory == NULL)
			{
				if (mmap->base_addr < kern_end+1)
				{
					free_memory = (mem_header_t*)(kern_end+1);
					header = free_memory;
				}
				else
				{
					free_memory = (mem_header_t*)mmap->base_addr;
					header = (mem_header_t*)mmap->base_addr;
				}
			}
			else
			{
				header->next_cont = (mem_header_t*)mmap->base_addr;
				header = (mem_header_t*)mmap->base_addr;
			}

			header->length = mmap->length - (kern_end+1 - kern_start);
			header->proc_id = -1;
			header->next_cont = NULL;
			header->next_addr = NULL;
		}
		mmap = (memory_map_t*)((unsigned int)mmap + mmap->size + sizeof(unsigned int));
	}
	__video.writestr((char *)"  [ done ]\n");
}

void memory::showfullmap()
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

void memory::showfreemap()
{
	mem_header_t *curr_h = used_memory < free_memory && used_memory != NULL ? used_memory : free_memory;
	while (curr_h != NULL)
	{
		__video.writestr((char*)"address: ");
		__video.writeaddr((addr_t)curr_h);
		__video.writestr((char*)"\n");
		__video.writestr((char*)"size: ");
		__video.writenum(curr_h->length, 10);
		__video.writestr((char*)"\n");
		__video.writestr((char*)"id: ");
		__video.writenum(curr_h->proc_id, 10);
		__video.writestr((char*)"\n");
		__video.writestr((char*)"next contig: ");
		__video.writeaddr((addr_t)curr_h->next_cont);
		__video.writestr((char*)"\n");
		__video.writestr((char*)"\n");
		curr_h = curr_h->next_addr;
	}
}

void *memory::alloc(int size, int id)
{
	mem_header_t *curr_h = free_memory, *prev_h = NULL;
	mem_header_t *newblock = NULL;

	mem_header_t *temp1 = NULL, *temp2 = NULL;
	while (curr_h != NULL)
	{
		if (curr_h->length - sizeof(mem_header_t) >= size)
		{
			if (curr_h->length - 2*sizeof(mem_header_t) - size >= min_block_size)
			{
				newblock = (mem_header_t*)(curr_h + sizeof(mem_header_t) + size);
				newblock->length = curr_h->length - 2*sizeof(mem_header_t) - size;
				newblock->proc_id = -1;
				newblock->next_addr = curr_h->next_addr;
				newblock->next_cont = curr_h->next_cont;
				curr_h->next_addr = newblock;
				curr_h->next_cont = newblock;
				curr_h->length = size + sizeof(mem_header_t);
			}

			if (prev_h != NULL)
			{
				temp1 = prev_h;
				prev_h->next_cont = curr_h->next_cont;
			}
			else
			{
				temp1 = used_memory;
				free_memory = curr_h->next_cont;
			}
			while (temp1 != NULL && temp1 < curr_h)
			{
				temp2 = temp1;
				temp1 = temp1->next_cont;
			}
			if (temp2 != NULL)
			{
				temp2->next_cont = curr_h;
				curr_h->next_cont = temp1;
			}
			else
			{
				curr_h->next_cont = used_memory;
				used_memory = curr_h;
			}

			curr_h->proc_id = id;
			return (void*)((addr_t)curr_h + sizeof(mem_header_t));
		}
		prev_h = curr_h;
		curr_h = curr_h->next_cont;
	}
	return NULL;
}

void memory::free(void *addr)
{
	mem_header_t *curr_h = (mem_header_t*)((addr_t)addr - sizeof(mem_header_t));
	curr_h->proc_id = -1;
	mem_header_t *prev_h, *iter = used_memory;
	while (iter < curr_h)
	{
		prev_h = iter;
		iter = iter->next_cont;
	}

	if (prev_h != NULL)
		prev_h->next_cont = curr_h->next_cont;
	else
		used_memory = curr_h->next_cont;

	iter = free_memory;
	while (iter < curr_h)
	{
		prev_h = iter;
		iter = iter->next_cont;
	}

	if (prev_h != NULL)
	{
		prev_h->next_cont = curr_h;
		curr_h->next_cont = iter;

		if (curr_h->next_cont == curr_h->next_addr)
		{
			curr_h->length += curr_h->next_addr->length;
			curr_h->next_cont = curr_h->next_cont->next_cont;
			curr_h->next_addr = curr_h->next_addr->next_addr;
		}

		if (prev_h->next_cont == prev_h->next_addr)
		{
			prev_h->length += prev_h->next_addr->length;
			prev_h->next_cont = prev_h->next_cont->next_cont;
			prev_h->next_addr = prev_h->next_addr->next_addr;
		}
	}
	else
	{
		curr_h->next_cont = free_memory;
		free_memory = curr_h;

		if (curr_h->next_cont == curr_h->next_addr)
		{
			curr_h->length += curr_h->next_addr->length;
			curr_h->next_cont = curr_h->next_cont->next_cont;
			curr_h->next_addr = curr_h->next_addr->next_addr;
		}
	}
}
