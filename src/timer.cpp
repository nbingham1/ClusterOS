#include "timer.h"

#include "kdt_isr.h"
#include "kvideo.h"

uint32 tick;
static void timer_callback(registers r)
{
	tick++;
	kprints("Tick: ");
	kprintd(tick, 10);
	kprints("\n");
}

void init_timer(uint32 freq)
{
	register_isr(32, &timer_callback);
	uint32 divisor = 1193180/freq;
	outportb(0x43, 0x36);
	uint8 l = (uint8)(divisor & 0xFF);
	uint8 w = (uint8)((divisor>>8) & 0xFF);

	outportb(0x40, l);
	outportb(0x40, w);
}
