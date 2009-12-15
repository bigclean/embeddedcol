/*!
 * \file hardware.h
 * \brief pin configuration,based on hardware connection.separate software realization from hardware connection.
 */
#ifndef __HARDWARE_H_
#define __HARDWARE_H_
#include <c8051f410.h>
#define ADDRESS 0x72 /*!< 0x72 is the write mode addres for PCA8574,read mode address is 0x73 */

/*
 * \note these configure about I2C 
 */
sbit SDA = P0^3;  /*!< I2C SDA bus */
sbit SCL = P0^2;  /*!< I2C SCL bus */

sbit lcd_e = P1 ^ 5;		/*!< enable signal */
sbit lcd_rw = P1 ^ 4;		/*!< Read write signal */
sbit lcd_rs = P1 ^ 3;		/*!< Data/Instructions,also known as DI */
sbit lcd_cs1 = P1 ^ 6;		/*!< left screen choose */
sbit lcd_cs2 = P1 ^ 7;		/*!< right screen choose */
sbit lcd_rst = P0 ^ 7;		/*!< reset signal */
sbit lcd_busy = P2 ^ 7;		/*!< busy signal (DB7) */

#endif