#include "multiboot.h"

#ifndef memory_h
#define memory_h

#define NULL 0x0
#define min_block_size 128

typedef unsigned long long int addr_t;

class mem_header_t
{
	public:
		int proc_id;
		/*
		 * -1         -> free
		 *  0         -> kernel
		 *  1 and on  -> other applications
		 */


		int length;

		mem_header_t *next_cont;
		mem_header_t *next_addr;
};

class memory
{
	public:
		memory();
		~memory();

		void initialize(multiboot_info_t *mbd, unsigned int magic);
		void showfullmap();
		void showfreemap();

		void *alloc(int size, int id);
		void free(void *addr);
	private:
		multiboot_info_t *boot_info;
		unsigned int magic_number;

		addr_t kern_start;
		addr_t kern_end;

		mem_header_t *free_memory;
		mem_header_t *used_memory;
};

extern memory __memory;

#endif
