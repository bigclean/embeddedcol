/*!
 * \file 1602.c 
 * \brief 1602 functiom implemention with I2C bus in 4-bit write mode
 */
#include "I2c.h"
#include "hardware.h"

static void delay(uint d)
{
	uint x,y;
	for(x = d; x > 0; x--)
	{
		for(y = 230; y > 0; y--);
	}
}

void lcd_write_code(uchar ins) //write command to LCD1602
{
	master_send_byte(ADDRESS, slave_receive_byte(ADDRESS) & 0xFD); //lcdrw = 0
	master_send_byte(ADDRESS, slave_receive_byte(ADDRESS) & 0x0F); //set higher 4-bit 0,ready for instruction higher 4-bit to write in
	master_send_byte(ADDRESS, slave_receive_byte(ADDRESS) | (ins & 0xF0)); //higher 4-bit of instruction and original lower 4-bit combined new data to write 
	master_send_byte(ADDRESS, slave_receive_byte(ADDRESS) | 0x04 ); //lcden = 1
	delay(1);
	master_send_byte(ADDRESS, slave_receive_byte(ADDRESS) & 0xFB); //lcden = 0,start to write
	
	ins = ins << 4; //left shift,get lower 4 bit of instruction
	master_send_byte(ADDRESS, slave_receive_byte(ADDRESS) & 0x0F); 
	master_send_byte(ADDRESS, slave_receive_byte(ADDRESS) | (ins & 0xF)); 
	master_send_byte(ADDRESS, slave_receive_byte(ADDRESS) | 0x04); // lcden = 1
	delay(1);
	master_send_byte(ADDRESS, slave_receive_byte(ADDRESS) & 0xFB); // lcden =0
}

void lcd_write_data(uchar d) // write data to LCD12864
{
	master_send_byte(ADDRESS, slave_receive_byte(ADDRESS) & 0xFD); //lcdrw = 0
	master_send_byte(ADDRESS, slave_receive_byte(ADDRESS) | 0x01); //lcdrs = 1
	master_send_byte(ADDRESS, slave_receive_byte(ADDRESS) & 0x0F); //set higher 4-bit 0,ready for data higher 4-bit to write in
	master_send_byte(ADDRESS, slave_receive_byte(ADDRESS) | (d & 0xF0)); //higher 4-bit of data and original lower 4-bit combined new data to write  
	master_send_byte(ADDRESS, slave_receive_byte(ADDRESS) | 0x04 ); //lcden =1
	delay(1);
	master_send_byte(ADDRESS, slave_receive_byte(ADDRESS) & 0xFB); //lcden = 0,start to write
	
	d = d << 4; //left shift,get lower 4 bit of data
	master_send_byte(ADDRESS, slave_receive_byte(ADDRESS) & 0x0F); 
	master_send_byte(ADDRESS, slave_receive_byte(ADDRESS) | (d & 0xF)); 
	master_send_byte(ADDRESS, slave_receive_byte(ADDRESS) | 0x04); // lcden = 1
	delay(1);
	master_send_byte(ADDRESS, slave_receive_byte(ADDRESS) & 0xFB); // lcden =0
}

void lcd_init()
{
	master_send_byte(ADDRESS, slave_receive_byte(ADDRESS) & 0xFB); //lcden = 0
	delay(10);
	lcd_write_code(0x28); /* function set,4-bit write mode,two lines and 5*8 character patterns */
	delay(1);
	lcd_write_code(0x28);
	delay(1);
	lcd_write_code(0x28);
	delay(1);
	master_send_byte(ADDRESS, slave_receive_byte(ADDRESS) | 0x04 ); //lcden = 1
	delay(1);
	master_send_byte(ADDRESS, slave_receive_byte(ADDRESS) & 0xFB); //lcden = 0,start to write
	lcd_write_code(0x0f); /* display on/off control,开显示，光标显示，光标闪烁 */ 
	lcd_write_code(0x06); /* entry mode set,完成一个字符码传送后，AC自动加1，显示不发生移位 */
	lcd_write_code(0x02); /* return home,归位指令设置地址计数器 AC = 0 */
	lcd_write_code(0x01); /* clear display,清显示 */
	delay(10);
}

void lcd_display_num(uchar num, uchar loc) //display numbers
{
	/* set DDRAM address */
	if (loc < 16) 
	{
		lcd_write_code(0x80 + loc - 1); //DDRAM first line start address is 0x60
	}
	else
	{
		lcd_write_code(0xc0 + (loc - 16) - 1); //DDRAM second line start address is 0xc0
	}
	delay(1);
	lcd_write_data(num + 0x30); //write data to DDRAM,0x30 is number '0' character code
}

void lcd_display_character(uchar c, uchar loc)
{
	if (loc < 16)
	{
		lcd_write_code(0x80 + loc - 1);
	}
	else
	{
		lcd_write_code(0xc0 + loc -16 - 1);
	}
	delay(1);
	lcd_write_data(c); //,write data to DDRAM,0x01 is character 'A' character code 
}

void lcd_display_string()
{
}
