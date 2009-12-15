/*!
 *  \file 1602.h
  * \brief  LCD1602 head file
 */
#ifndef __1602_H_
#define __1602_H_

#include "def.h"

/* funtion prototype */

/*!
 * \fn lcd_init()
 * \brief initlize LCD1602
 * \return none
 * \note in this section,we use LCD1602 in 4-bit write mode,and other four lower bits to use for rs,rw and enable signal
 */
void lcd_init();

/*!
 * \fn lcd_write_code(uchar ins)
 * \brief write code to LCD1602
 * \param ins instruction code write to LCD1602
 * \return none
 * \see lcd_write_data()
 */
void lcd_write_code(uchar ins);

/*!
 * \fn lcd_write_data(uchar d)
 * \brief data to write to LCD1602
 * \return none
 * \see lcd_write_code()
 */
void lcd_write_data(uchar d);

/*!
 * \fn void lcd_display_num(uchar num, uchar loc)
 * \brief display number
 * \param num number to display in LCD1602
 * \param loc display location,[1,16] means first line,[17,32] means second line
 * \return none
 * \see void lcd_display_character()
 */
void lcd_display_num(uchar num, uchar loc);

/*!
 * \fn void lcd_display_character(uchar c, uchar loc)
 * \brief display character in LCD1602
 * \param c character to display in LCD1602
 * \param loc display location,[1,16] means first line,[17,32] means second line
 * \return none
 * \see void lcd_display_num()
 */
void lcd_display_character(uchar c, uchar loc);

/*!
 * \fn void lcd_display_string()
 * \brief 
 * \return none
 * \see 
 */
void lcd_display_string();

#endif