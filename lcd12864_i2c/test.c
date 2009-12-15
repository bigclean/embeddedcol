/*!
 * \file  main file for lcd12864
 * \brief just for test code above
 * \author Jujie Zheng 
 * \date 2009-8-3
 */
#include "def.h"
#include "lcd12864.h"

extern uchar code hanzi[];
extern uchar code character[];
extern uchar code number[];
extern uchar code letter[];

void main(void)
{
	uchar i, j;		//iÎªÁÐ,jÎªÒ³
	OSCICN    = 0x86;
	PCA0MD &= ~0x40;
	XBR1 = 0x40;
	lcd_init();
	for (i = 0; i < 8; i++)
	{
		lcd_display_hanzi(1, i, i, hanzi, 0);

	}
	for (j = 0; j < 14; j++)
	{
		lcd_display_character(5, j, j, letter, 0);
	}
}