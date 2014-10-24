#include "common.h"

#ifndef multiboot_h
#define multiboot_h

#define MULTIBOOT_HEADER_MAGIC		0x1BADB002

#ifdef __ELF__
#define MULTIBOOT_HEADER_FLAGS		0x00000003
#else
#define MULTIBOOT_HEADER_FLAGS		0x00010003
#endif

#define MULTIBOOT_BOOTLOADER_MAGIC	0x2BADB002

#define STACK_SIZE					0x4000

#ifdef HAVE_ASM_USCORE
#define EXT_C(sym)					_## sym
#else
#define EXT_C(sym)					sym
#endif

#ifndef ASM

struct multiboot_header_t
{
	uint32 magic;
	uint32 flags;
	uint32 checksum;
	uint32 header_addr;
	uint32 load_addr;
	uint32 load_end_addr;
	uint32 bss_end_addr;
	uint32 entry_addr;
};

struct aout_symbol_table_t
{
	uint32 tabsize;
	uint32 strsize;
	uint32 addr;
	uint32 reserved;
};

struct elf_section_header_table_t
{
	uint32 num;
	uint32 size;
	uint32 addr;
	uint32 shndx;
};

struct multiboot_info_t
{
	uint32 flags;
	uint32 mem_lower;
	uint32 mem_upper;
	uint32 boot_device;
	uint32 cmdline;
	uint32 mods_count;
	uint32 mods_addr;
	union
	{
		aout_symbol_table_t aout_sym;
		elf_section_header_table_t elf_sec;
	} u;
	uint32 mmap_length;
	uint32 mmap_addr;
};

struct module_t
{
	uint32 mod_start;
	uint32 mod_end;
	uint32 string;
	uint32 reserved;
};

struct memory_map_t
{
	uint32 size;
	uint64 base_addr;
	uint64 length;
	uint32 type;
};

#endif
#endif
