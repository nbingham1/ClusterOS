#include "video.h"

video __video;

video::video()
{
	off = 0;
	pos = 0;
	videomem = (unsigned short*)0xb8000;
	clear();
	writestr((char *)"Initializing Video Memory...  [ done ]\n");
}

video::~video()
{
}

void video::clear()
{
	for (unsigned int i = 0; i < 80*25; i++)
		videomem[i] = (unsigned char) ' ' | 0x0700;

	pos = 0;
	off = 0;
}

void video::writestr(char *cp)
{
	for (char *ch = cp; *ch; ch++)
		put(*ch);
}

void video::writenum(unsigned long long int n, int base)
{
	unsigned int num = n;
	unsigned int temp;
	unsigned int div = 1;
	unsigned int levels = 0;
	while (num/div > 0)
	{
		div *= base;
		levels++;
	}

	div /= base;

	while (div >= 1)
	{
		temp = (num/div);
		num = num - temp*div;

		if (temp < 10)
			put(char(temp+48));
		else
			put(char(temp+55));

		div /= base;
	}
}

void video::writeaddr(unsigned long long int n)
{
	unsigned int num = n;
	unsigned int temp;
	unsigned int div = 1;
	unsigned int levels = 0;
	while (num/div > 0)
	{
		div *= 16;
		levels++;
	}

	div /= 16;
	put('0');
	put('x');

	for (int x = 0; x < 8 - levels; x++)
		put('0');

	while (div >= 1)
	{
		temp = (num/div);
		num = num - temp*div;

		if (temp < 10)
			put(char(temp+48));
		else
			put(char(temp+55));

		div /= 16;
	}
}

void video::put(char c)
{
	if (pos >= 80)
		newln();

	if (off >= 80*25)
		clear();

	switch (c)
	{
		case '\n':
			newln();
			break;
		case '\r':
			newln();
			break;
		case '\t':
			for (int x = 0; x < 4; x++)
				put(' ');
			break;
		default:
			videomem[off + pos] = (unsigned char) c | 0x0700;
			pos++;
			break;
	}
}

void video::newln()
{
	off += 80;
	pos = 0;
}
