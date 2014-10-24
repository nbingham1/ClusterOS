#include "kdt_isr.h"
#include "kvideo.h"

isr isr_list[256];

// This gets called from our ASM interrupt handler stub.
extern "C" void isr_handler(registers regs)
{
}

extern "C" void irq_handler(registers regs)
{
   // Send an EOI (end of interrupt) signal to the PICs.
   // If this interrupt involved the slave.
   if (regs.int_no >= 40)
   {
       // Send reset signal to slave.
       outportb(0xA0, 0x20);
   }
   // Send reset signal to master. (As well as slave, if necessary).
   outportb(0x20, 0x20);

   if (isr_list[regs.int_no] != 0)
   {
       isr handler = isr_list[regs.int_no];
       handler(regs);
   }
}

void register_isr(uint8 n, isr handler)
{
	isr_list[n] = handler;
}
