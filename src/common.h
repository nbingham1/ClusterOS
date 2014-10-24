#ifndef common_h
#define common_h

// boolean
typedef bool					boolean;

// unsigned integers
typedef unsigned char			uint8;
typedef unsigned short			uint16;
typedef unsigned long			uint32;
typedef unsigned long long		uint64;

// signed integers
typedef signed char				sint8;
typedef signed short			sint16;
typedef signed long				sint32;
typedef signed long long		sint64;

// pointers
typedef void*					vptr;

void	outportb(uint16 port, uint8 value);
uint8	inportb(uint16 port);
void	outportw(uint16 port, uint16 value);
uint16	inportw(uint16 port);

void enable_interrupts();
void disable_interrupts();
void halt();

#endif
