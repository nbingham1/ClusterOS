#ifndef kdt_isr_h
#define kdt_isr_h

#include "common.h"

struct registers
{
   uint32 ds;                  // Data segment selector
   uint32 edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
   uint32 int_no, err_code;    // Interrupt number and error code (if applicable)
   uint32 eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
};

typedef void (*isr)(registers);

extern "C" void isr_handler(registers regs);
extern "C" void irq_handler(registers regs);

void register_isr(uint8 n, isr handler);

#endif
