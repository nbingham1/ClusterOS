#include "common.h"

uint8 inportb(uint16 port)
{
	uint8 ret;

	asm volatile
	(
		"inb %%dx, %%al\n\t"
		: "=a" (ret)
		: "d" (port)
	);

   	return ret;
}

void outportb(uint16 port, uint8 data)
{
	asm volatile
	(
		"outb %%al, %%dx\n\t"
		:
		: "a" (data), "d" (port)
	);
}

uint16 inportw(uint16 port)
{
	uint16 ret;

	asm volatile
	(
		"inw %%dx, %%ax\n\t"
		: "=a" (ret)
		: "d" (port)
	);

   	return ret;
}

void outportw(uint16 port, uint16 data)
{
	asm volatile
	(
		"outw %%ax, %%dx\n\t"
		:
		: "a" (data), "d" (port)
	);
}



void enable_interrupts()
{
	asm volatile
	(
		"sti"
		:
		:
	);
}

void disable_interrupts()
{
	asm volatile
	(
		"cli"
		:
		:
	);
}

void halt()
{
	asm volatile
	(
		"hlt"
		:
		:
	);
}
