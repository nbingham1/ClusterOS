#include "kvideo.h"

uint16 *kvideo_mem = (uint16*)0xb8000;
uint16 kvideo_x_pos = 0;
uint16 kvideo_y_pos = 0;

void kcls()
{
	for (uint16 i = 0; i < 80*25; i++)
		kvideo_mem[i] = (uint8) ' ' | 0x0700;

	kcursorto(0, 0);
}

void kput(char c)
{
	uint16 off = kvideo_y_pos*80 + kvideo_x_pos;
	if (kvideo_x_pos >= 80)
		knewln();

	if (off >= 25*80)
		for (int i = 0; i < (off - 80*25)/80 + 1; i++)
			kscroll();

	switch (c)
	{
		case '\n':
			knewln();
			break;
		case '\r':
			knewln();
			break;
		case '\t':
			for (uint8 x = 0; x < 4; x++)
				kput(' ');
			break;
		default:
			kvideo_mem[kvideo_y_pos*80 + kvideo_x_pos] = (unsigned char) c | 0x0F00;
			kcursorto(kvideo_x_pos+1, kvideo_y_pos);
			break;
	}
}

void kprintf(const char *fmt, int mark, ...)
{
	char *ptr = (char*)((uint32)&mark+4);

	for (const char *ch = fmt; *ch && *ch != '\0'; ch++)
	{
		switch (*ch)
		{
			case '%':
				if (*(ch+1) == 'd')
				{
					kprintd(*(sint32*)ptr, 10);
					ptr = ptr + sizeof(sint32);
				}
				else if (*(ch+1) == 'h')
				{
					kprintd(*(sint32*)ptr, 16);
					ptr = ptr + sizeof(sint32);
				}
				ch = ch++;
				break;
			default:
				kput(*ch);
				break;
		}
	}
}

void kprints(const char *str)
{
	for (const char *ch = str; *ch && *ch != '\0'; ch++)
		kput(*ch);
}

void kprintd(sint32 number, uint32 base)
{
	if (base == 2)
		kput('B');
	else if (base == 8)
		kput('O');
	else if (base == 16)
	{
		kput('0');
		kput('x');
	}

	if (number == 0)
	{
		kput('0');
		return;
	}

	sint32 num = number < 0 ? -number : number;
	sint32 temp;
	sint32 div = 1;
	sint32 levels = 0;
	while (num/div > 0)
	{
		div *= base;
		levels++;
	}

	div /= base;
	if (number < 0)
		kput('-');

	while (div >= 1)
	{
		temp = (num/div);
		num = num - temp*div;

		if (temp < 10)
			kput(char(temp+48));
		else
			kput(char(temp+55));

		div /= base;
	}
}

void kcursorto(uint16 x_pos, uint16 y_pos)
{
	kvideo_y_pos = y_pos;
	kvideo_x_pos = x_pos;
	uint16 off = kvideo_y_pos*80 + kvideo_x_pos;
	outportb(0x3D4, 14);
	outportb(0x3D5, off >> 8);
	outportb(0x3D4, 15);
	outportb(0x3D5, off);
}

void knewln()
{
	kcursorto(0, kvideo_y_pos + 1);
}

void kscroll()
{
	for (uint16 i = 80; i < 80*25; i++)
		kvideo_mem[i - 80] = kvideo_mem[i];

	for (uint16 i = 80*24; i < 80*25; i++)
		kvideo_mem[i] = (uint8) ' ' | 0x0700;

	kcursorto(kvideo_x_pos, kvideo_y_pos - 1);
}
