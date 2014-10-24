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
	unsigned long magic;
	unsigned long flags;
	unsigned long checksum;
	unsigned long header_addr;
	unsigned long load_addr;
	unsigned long load_end_addr;
	unsigned long bss_end_addr;
	unsigned long entry_addr;
};

struct aout_symbol_table_t
{
	unsigned long tabsize;
	unsigned long strsize;
	unsigned long addr;
	unsigned long reserved;
};

struct elf_section_header_table_t
{
	unsigned long num;
	unsigned long size;
	unsigned long addr;
	unsigned long shndx;
};

struct multiboot_info_t
{
	unsigned long flags;
	unsigned long mem_lower;
	unsigned long mem_upper;
	unsigned long boot_device;
	unsigned long cmdline;
	unsigned long mods_count;
	unsigned long mods_addr;
	union
	{
		aout_symbol_table_t aout_sym;
		elf_section_header_table_t elf_sec;
	} u;
	unsigned long mmap_length;
	unsigned long mmap_addr;
};

struct module_t
{
	unsigned long mod_start;
	unsigned long mod_end;
	unsigned long string;
	unsigned long reserved;
};

struct memory_map_t
{
	unsigned long size;
	unsigned long long int base_addr;
	unsigned long long int length;
	unsigned long type;
};

#endif
#endif
