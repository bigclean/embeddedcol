/*! \file LCD12864.h
 *  \brief LCD12864 head file
 *  \author Jujie Zheng 
 *  \date 2009-8-3
 */
#include <c8051f410.h>

#ifndef __LCD_H_
#define __LCD_H_

#include "def.h"

/*
 *Macro definition
 */
#define disp_on    0x3f  /*!< screen display on code */ 
#define disp_off   0x3e  /*!< screen display off code */
#define disp_start_line     0xc0  /*!< disp_start_line indicates the display data RAM displayed at the top of the screen */
//#define disp_page  0xb8 
#define disp_x  0xb8  /*!< disp_x indicates the page address register. */
//#define disp_page  0xb8 
#define disp_y     0x40  /*!< display column address */


/*
 *Function declaration
 */
void lcd_init(void);
void delay1(unsigned int t);
void check_busy(void);
void reset();
void clear();
void delay(uint t);

/*!
 * \fn lcd_set_position(uchar x, uchar y)
 * \brief determine the right position in one single screen calculated by refered parameter.
 * \param  x  display page column,range is [0,7].
 * \param  y  display  real column position in line format(internal),range is [0,63].
 * exam: it's a bit of choopy,you can check your datasheet.
 */
void lcd_set_position(uchar x, uchar y);

/*!
 * \fn    lcd_write_code(uchar c, uchar cs1, uchar cs2);
 * \brief pass code sequence to left and right screen.
 * \param  d    write code,in [0,255],usually in hex format.usually from character moulding software.
 * \param  cs1  left screen select signal,1 to enable.
 * \param  cs2  right screen select signal,1 to enable.
 * \return void
 * exam: lcd_write_data(0x7f,0,1) will pass code '0x7f' to LCD12864 control chip,you can check chip manual and datasheet.
 */
void lcd_write_code(uchar c, uchar cs1, uchar cs2);

/*!
 * \fn lcd_write_data(uchar d, uchar cs1, uchar cs2)
 * \brief write data in left and right screen(actually it fills one pages of 8 lines)
 * \param    d     write data,in [0,255],usually in hex format.usually get from character moulding software.
 * \param    cs1   left screen select signal,1 to enable
 * \param    cs2  right screen select signal,1 to enable
 * \return void
 * exam: lcd_write_data(0x7f,0,1) will write data '0x7f' to right screen.
 */
void lcd_write_data(uchar d, uchar cs1, uchar cs2);

/*! 
 * \fn      lcd_final_write(uchar d, uchar x, uchar y);
 * \brief   write data in refered position.
 * \param   d  write data,in [0,255],also in hex format.usually from character moulding software.
 * \param   x  display page column ,range is in [0,7] display. 
 * \param	 y  column position in line format(internal),range is in [0,127].
 * \return  void
 * \warning This is a internal function,you are suggested to avoid using it directly.
 *             final_write(127,2,3) will write data '127',also known '7F' in column 2 and page 3.
 * \return void 
*/
void lcd_final_write(uchar d, uchar x, uchar y);

/*!
 * \fn  void lcd_display_character(uchar x, uchar y, uchar n, uchar code * p,
		       uchar highlight)
 * \brief  display english character
 * \param  x  display page position ,range must be even in [0,7],because every english character occurs two pages 
 * \param  y  display column position in character mode,range is in [1,16],but every screen actually only display 8 character.
 * \param  n  the display character position in character array
 * \param   p  display character array position,it's a pointer.(you can get the code from 取模软件)
 * \param  highlight  determine if it display in highlight mode(反白)
 * \return  void 
 *  exam:  you can use display_character(2,3,3,letter,0) to display character 'c' in page [2,3] and column 3 in screen
 */
extern void lcd_display_character(uchar x, uchar y, uchar n, uchar code * p,
		       uchar highlight);
			   
/*!
 * \fn  lcd_display_hanzi(uchar x, uchar y, uchar n, uchar code * p, uchar highlight)
 * \brief  display hanzi character
 * \param  x  display page position,must be even in [0,7],because every hanzi occurs two pages 
 * \param	y  display column position in character mode,in [1,8],because every hanzi width is twice of english character,but every screen actually only display 4 hanzi.
 * \param  n  the display character position in character array
 * \param   p  display character array position,it's a pointer.(you can get the code from 取模软件)
 * \param  highlight  determine if it display in highlight mode(反白)
 * \return void
 * exam:  you can use display_hanzi(2,3,3,letter,0) to display hanzi '患' in page [2,3] and column 3 in screen
 */ 
extern void lcd_display_hanzi(uchar x, uchar y, uchar n, uchar code * p, uchar highlight);

#endif