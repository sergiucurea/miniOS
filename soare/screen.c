#include "screen.h"
#include <stdint.h>
static PSCREEN gVideo = (PSCREEN)(0x000B8000);



int line = 0;

int lastpos = 0;

void monitor_write(char* string)
{
	int i, len;
	len = 0;

	while (string[len] != 0)
	{
		len++;
	}
	for (i = line * 80; (i < line*80+len) && (i < line * 80+80); i++)
	{
		gVideo[i].color = 10;
		gVideo[i].c = string[i-line*80];
	}
	lastpos = i;
	line++;
}

void monitor_write_pos(char* string)
{
	int i, len;
	len = 0;

	while (string[len] != 0)
	{
		len++;
	}
	for (i = lastpos; (i < len+lastpos) && (i < line * 80 - 1); i++)
	{
		
		gVideo[i].color = 10;
		gVideo[i].c = string[i - lastpos];
	}
	lastpos = i;

}

void monitor_write_dec(uint32_t n)
{

	if (n == 0)
	{
		monitor_write_pos("0");
		return;
	}

	int32_t acc = n;
	char c[32];
	int i = 0;
	while (acc > 0)
	{
		c[i] = '0' + acc % 10;
		acc /= 10;
		i++;
	}
	c[i] = 0;

	char c2[32];
	c2[i--] = 0;
	int j = 0;
	while (i >= 0)
	{
		c2[i--] = c[j++];
	}
	monitor_write_pos(c2);

}

void HelloBoot()
{
	monitor_write("Hello World!!! from Sergiu's OS! ");
}


