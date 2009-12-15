/*! 
 * \file lcd12864.c
 * \brief LCD12864 drive funtions implementations
 * \author Jujie Zheng 
 * \date 2009-8-3
 */
#ifndef __lcd12864_H_
#define __lcd12864_H_
#include "hardware.h"
#include "I2c.h"
#include "lcd12864.h"
#include <intrins.h>

void delay1(uint t)
{
	uchar i,j;
	for(i=0;i<t;i++)
	for(j=0;j<1;j++);
}

void lcd_write_code(uchar c, uchar cs1, uchar cs2)
{
	lcd_cs1 = cs1;
	lcd_cs2 = cs2;
	check_busy();
	lcd_rs = 0;
	lcd_rw = 0;
	master_send_byte(ADDRESS, c);
	_nop_(); 
	_nop_();
	_nop_();
	_nop_(); 
	delay1(1);
	lcd_e = 1;
	_nop_(); 
	_nop_(); 
	delay1(1);
	lcd_e = 0;
}

void delay(uint t)
{
	uint i;
	for (; t > 0; t--)
	{
		for (i = 0; i < 124; i++)
		{;
		}
	}
}

void reset(void)
{
	lcd_rst = 0;
	delay(20);
	lcd_rst = 1;
	delay(20);
}

void clear(void)
{
	uchar x, y;
	for (y = 0; y < 8; y++)
	{
		for (x = 0; x < 128; x++)
		{
			lcd_final_write(0, x, y);
		}
	}
}

//检测忙状态
void check_busy(void)
{
	lcd_e = 1;
	lcd_rs = 0;
	lcd_rw = 1;
	_nop_();
	master_send_byte(ADDRESS, 0x77);
	//ACC=P2;
	/*while(1)
	   {
	   lcd_e = 1;
	   if(!lcd_busy)
	   {
	   break;
	   }
	   lcd_e = 0;
	   } */
	//while (lcd_busy);
	while(receive_byte()&0x90==1);
	_nop_();
	lcd_e = 0;
}

void lcd_set_position(uchar x, uchar y)
{
	//x = x + 0x40;
	//set which page to start,every screen have 8 pages,one pages have 8 lines.
	//every data will occupy one RAM unit.
	x = x + disp_x;
	lcd_write_code(x, 1, 1);	//execute code

	//y = y + 0xb8;
	//we can only operate every pages together
	y = y + disp_y;		//set column address
	lcd_write_code(y, 1, 1);
	lcd_write_code(disp_start_line,1,1);	   //avoid screen jump
}


//write data
//cs1 refers left,cs2 refers right
void lcd_write_data(uchar d, uchar cs1, uchar cs2)
{
	lcd_cs1 = cs1;
	lcd_cs2 = cs2;
	check_busy();
	lcd_rs = 1;
	lcd_rw = 0;
	master_send_byte(ADDRESS, d);
	_nop_(); 
	_nop_();
	_nop_();
	_nop_(); 
	delay1(1);
	lcd_e = 1;
	_nop_(); 
	_nop_(); 
	delay1(1);
	lcd_e = 0;
}

void lcd_final_write(uchar d, uchar x, uchar y)
{
	if (y >= 64)
	{
		lcd_set_position(y - 64, x);	//in right screen
		lcd_write_data(d, 0, 1);
	} else
	{
		lcd_set_position(y, x);	//in left screen
		lcd_write_data(d, 1, 0);
	}
}

void lcd_init(void)
{
	reset();
	//lcd_rst = 1;
	lcd_write_code(disp_on, 1, 1);	//开显示设置  
	lcd_write_code(disp_start_line, 1, 1);	//设置显示起始行为第一行      
	//lcd_write_code(disp_x,1,1);           //页面地址设置      
	lcd_write_code(disp_x, 1, 1);	//页面地址设置
	lcd_write_code(disp_y, 1, 1);	//列地址设为0
	clear();
	//lcd_write_code(disp_off,1,1);
}

void lcd_display_character(uchar x, uchar y, uchar n, uchar code * p,
		       uchar highlight)
{
	uchar i, dd;
	//every english character width is 8 columns,so it needs 8 cycles
	//every cycle,finish the same column up and above part.
	for (i = 0; i < 8; i++)
	{
		dd = p[i + n * 16];	//get up part code
		if (highlight == 1)
		{
			dd = 255 - dd;	//highlighting
		}
		//write data in column (y*8+i) and in up page y
		//real column address,in internal is (y*8+i),in [0,127]
		lcd_final_write(dd, y * 8 + i, x);
		dd = p[(i + 8) + n * 16];	//get the down part code
		if (highlight == 1)
		{
			dd = 255 - dd;
		}
		//write data,but in down page y+1
		lcd_final_write(dd, y * 8 + i, x + 1);
	}
}

void lcd_display_hanzi(uchar x, uchar y, uchar n, uchar code * p, uchar highlight)
{
	uchar i, dd;
	//every hanzi character width is 16 columns,so it needs 16 cycles
	//every cycle,finish the same column up and above part.
	for (i = 0; i < 16; i++)	//every hanzi width is 16 columns
	{
		dd = p[i + n * 32];
		if (highlight == 1)
		{
			dd = 255 - dd;	//highlighting
		}
		lcd_final_write(dd, y * 16 + i, x);
		dd = p[(i + 16) + n * 32];
		if (highlight == 1)
		{
			dd = 255 - dd;
		}
		lcd_final_write(dd, y * 16 + i, x + 1);
	}
}