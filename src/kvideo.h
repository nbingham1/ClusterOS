#include "common.h"

#ifndef kvideo_h
#define kvideo_h

void kcls();
void kput(char c);
void kprintf(const char *fmt, int mark, ...);
void kprints(const char *str);
void kprintd(sint32 number, uint32 base);
void kcursorto(uint16 x_pos, uint16 y_pos);
void knewln();
void kscroll();

#endif
