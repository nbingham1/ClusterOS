#ifndef asmf_h
#define asmf_h

inline static unsigned char inportb(int port)
{
	register unsigned char r;
   
   	asm volatile
	( 
		"inb %%dx, %%al\n\t" 
		: "=a" (r) 
		: "d" (port)
	);

   	return (r);
}

inline static void outportb(int port, unsigned char data)
{
	asm volatile
	(
		"outb %%al, %%dx\n\t" 
		:
		: "a" (data), "d" (port)
	);
}

inline static unsigned short inportw(int port)
{
	register unsigned short r;
   
   	asm volatile
	(
		"inw %%dx, %%ax\n\t" 
		: "=a" (r) 
		: "d" (port)
	);

   	return (r);
}

inline static void outportw(int port, unsigned short data)
{
	asm volatile
	(
		"outw %%ax, %%dx\n\t" 
		:
		: "a" (data), "d" (port)
	);
}



inline static void enable()
{
	asm volatile 
	(
		"sti"
		:
		:
	);
}

inline static void disable()
{
	asm volatile
	(
		"cli"
		:
		:
	);
}

inline static void halt()
{
	asm volatile
	(
		"hlt"
		:
		:
	);
}
