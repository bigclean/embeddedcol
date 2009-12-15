/*!
 * \file exam.c
 * \brief just a test example
 */
#include "I2c.h"
#include "1602.h"

void main()
{
	PCA0MD &= ~0x40;
	OSCICN |= 0x87;
	P1MDOUT = 0x0E;
	P2MDOUT = 0xF0;
	XBR1 = 0x40;
	lcd_init();
	lcd_display_num(7,12);
}
