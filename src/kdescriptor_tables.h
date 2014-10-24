#include "common.h"
#include "kdt.h"

#ifndef kdescriptor_tables_h
#define kdescriptor_tables_h

#define KCODESEG 0x9A
#define KDATASEG 0x92
#define UCODESEG 0xFA
#define UDATASEG 0xF2

struct kgdt_entry
{
	uint16	limit_low;
	uint16	base_low;
	uint8	base_mid;
	uint8	access;
	uint8	granularity;
	uint8	base_high;

} __attribute__((packed));

static void kgdt_init();
static void kgdt_segment(sint32 num, uint32 base, uint32 limit, uint8 access, uint8 gran);

struct kidt_entry
{
	uint16	base_low;
	uint16	selector;
	uint8	zero;
	uint8	flags;
	uint16	base_high;
} __attribute__((packed));

static void kidt_init();
static void kidt_interrupt(uint8 num, uint32 base, uint16 selector, uint8 flag);

struct kdt_ptr
{
	uint16 limit;
	uint32 base;

} __attribute__((packed));


void kdt_init();

#endif
