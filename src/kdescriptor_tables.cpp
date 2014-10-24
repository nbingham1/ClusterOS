#include "kdescriptor_tables.h"

kgdt_entry kgdt[32];
kdt_ptr kgdt_ptr;
kidt_entry kidt[256];
kdt_ptr kidt_ptr;

static void kgdt_init()
{
	kgdt_ptr.limit = sizeof(kgdt_entry)*32 - 1;
	kgdt_ptr.base = (uint32)&kgdt;

	kgdt_segment(0, 0, 0, 0, 0);					// NULL Segment
	kgdt_segment(1, 0, 0xFFFFFFFF, KCODESEG, 0xCF);	// Kernel Space Code Segment
	kgdt_segment(2, 0, 0xFFFFFFFF, KDATASEG, 0xCF);	// Kernel Space Data Segment
	kgdt_segment(3, 0, 0xFFFFFFFF, UCODESEG, 0xCF);	// User Space Code Segment
	kgdt_segment(4, 0, 0xFFFFFFFF, UDATASEG, 0xCF);	// User Space Data Segment

	for (int x = 5; x < 32; x++)
		kgdt_segment(x, 0, 0, 0, 0);

	kgdt_flush((uint32)&kgdt_ptr);
}

static void kgdt_segment(sint32 num, uint32 base, uint32 limit, uint8 access, uint8 gran)
{
	kgdt[num].base_low    = (base) 		 & 0xFFFF;
	kgdt[num].base_mid 	  = (base >> 16) & 0xFF;
	kgdt[num].base_high   = (base >> 24) & 0xFF;

	kgdt[num].limit_low   = (limit) 	  & 0xFFFF;
	kgdt[num].granularity = (limit >> 16) & 0x0F;

	kgdt[num].granularity |= gran & 0xF0;
	kgdt[num].access      = access;
}

static void kidt_init()
{
	kidt_ptr.limit = sizeof(kidt_entry) * 256 -1;
	kidt_ptr.base  = (uint32)kidt;

	//memset(kidt, 0, sizeof(kidt_entry)*256);

	kidt_interrupt( 0, (uint32)isr0 , 0x08, 0x8E);
	kidt_interrupt( 1, (uint32)isr1 , 0x08, 0x8E);
	kidt_interrupt( 2, (uint32)isr2 , 0x08, 0x8E);
	kidt_interrupt( 3, (uint32)isr3 , 0x08, 0x8E);
	kidt_interrupt( 4, (uint32)isr4 , 0x08, 0x8E);
	kidt_interrupt( 5, (uint32)isr5 , 0x08, 0x8E);
	kidt_interrupt( 6, (uint32)isr6 , 0x08, 0x8E);
	kidt_interrupt( 7, (uint32)isr7 , 0x08, 0x8E);
	kidt_interrupt( 8, (uint32)isr8 , 0x08, 0x8E);
	kidt_interrupt( 9, (uint32)isr9 , 0x08, 0x8E);
	kidt_interrupt(10, (uint32)isr10 , 0x08, 0x8E);
	kidt_interrupt(11, (uint32)isr11 , 0x08, 0x8E);
	kidt_interrupt(12, (uint32)isr12 , 0x08, 0x8E);
	kidt_interrupt(13, (uint32)isr13 , 0x08, 0x8E);
	kidt_interrupt(14, (uint32)isr14 , 0x08, 0x8E);
	kidt_interrupt(15, (uint32)isr15 , 0x08, 0x8E);
	kidt_interrupt(16, (uint32)isr16 , 0x08, 0x8E);
	kidt_interrupt(17, (uint32)isr17 , 0x08, 0x8E);
	kidt_interrupt(18, (uint32)isr18 , 0x08, 0x8E);
	kidt_interrupt(19, (uint32)isr19 , 0x08, 0x8E);
	kidt_interrupt(20, (uint32)isr20 , 0x08, 0x8E);
	kidt_interrupt(21, (uint32)isr21 , 0x08, 0x8E);
	kidt_interrupt(22, (uint32)isr22 , 0x08, 0x8E);
	kidt_interrupt(23, (uint32)isr23 , 0x08, 0x8E);
	kidt_interrupt(24, (uint32)isr24 , 0x08, 0x8E);
	kidt_interrupt(25, (uint32)isr25 , 0x08, 0x8E);
	kidt_interrupt(26, (uint32)isr26 , 0x08, 0x8E);
	kidt_interrupt(27, (uint32)isr27 , 0x08, 0x8E);
	kidt_interrupt(28, (uint32)isr28 , 0x08, 0x8E);
	kidt_interrupt(29, (uint32)isr29 , 0x08, 0x8E);
	kidt_interrupt(30, (uint32)isr30 , 0x08, 0x8E);
	kidt_interrupt(31, (uint32)isr31, 0x08, 0x8E);

	outportb(0x20, 0x11);
	outportb(0xA0, 0x11);
	outportb(0x21, 0x20);
	outportb(0xA1, 0x28);
	outportb(0x21, 0x04);
	outportb(0xA1, 0x02);
	outportb(0x21, 0x01);
	outportb(0xA1, 0x01);
	outportb(0x21, 0x0);
	outportb(0xA1, 0x0);

	kidt_interrupt(32, (uint32)irq0 , 0x08, 0x8E);
	kidt_interrupt(33, (uint32)irq1 , 0x08, 0x8E);
	kidt_interrupt(34, (uint32)irq2 , 0x08, 0x8E);
	kidt_interrupt(35, (uint32)irq3 , 0x08, 0x8E);
	kidt_interrupt(36, (uint32)irq4 , 0x08, 0x8E);
	kidt_interrupt(37, (uint32)irq5 , 0x08, 0x8E);
	kidt_interrupt(38, (uint32)irq6 , 0x08, 0x8E);
	kidt_interrupt(39, (uint32)irq7 , 0x08, 0x8E);
	kidt_interrupt(40, (uint32)irq8 , 0x08, 0x8E);
	kidt_interrupt(41, (uint32)irq9 , 0x08, 0x8E);
	kidt_interrupt(42, (uint32)irq10 , 0x08, 0x8E);
	kidt_interrupt(43, (uint32)irq11 , 0x08, 0x8E);
	kidt_interrupt(44, (uint32)irq12 , 0x08, 0x8E);
	kidt_interrupt(45, (uint32)irq13 , 0x08, 0x8E);
	kidt_interrupt(46, (uint32)irq14, 0x08, 0x8E);
	kidt_interrupt(47, (uint32)irq15, 0x08, 0x8E);

	kidt_flush((uint32)&kidt_ptr);
}

static void kidt_interrupt(uint8 num, uint32 base, uint16 selector, uint8 flag)
{
	kidt[num].base_low 	= (base)		& 0xFFFF;
	kidt[num].base_high 	= (base >> 16)  & 0xFFFF;
	kidt[num].selector	= selector;
	kidt[num].zero		= 0;
	// We must uncomment the OR below when we get to using user-mode.
	// It sets the interrupt gate's privilege level to 3.
	kidt[num].flags   	= flag /* | 0x60 */;
}

void kdt_init()
{
	kgdt_init();
	kidt_init();
}
