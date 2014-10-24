#include "multiboot.h"

#ifndef memory_h
#define memory_h

class memory
{
	public:
		memory();
		~memory();

		void initialize(multiboot_info_t *mbd, unsigned int magic);
		void display();

	private:
		multiboot_info_t *boot_info;
		unsigned int magic_number;

		unsigned long long int kern_start;
		unsigned long long int kern_end;
};

extern memory __memory;

#endif
