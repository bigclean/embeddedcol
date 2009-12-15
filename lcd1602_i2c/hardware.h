/*!
 * \file hardware.h
 * \brief pin configuration
 * 
 * based on hardware connection.separate software realization from hardware connection.
 */
#ifndef __HARDWARE_H_
#define __HARDWARE_H_
#define ADDRESS 0x72 /*!< 0x72 is the write mode addres for PCA8574,read mode address is 0x73 */
#include<c8051f410.h>
#include<mcs51/C8051F410.h>
#endif

/*
 * \note these configure about I2C 
 */
sbit SDA = P0^3;  /*!< I2C SDA bus */
sbit SCL = P0^2;  /*!< I2C SCL bus */
/*!
 * \note P0 address is 0x80
 */
//__sbit __at (0x83) SDA; /*!< I2C SDA bus */
//__sbit __at (0x82) SCL; /*!< I2C SCL bus */


/* these configure for LCD1602 in 8-bit write mode */
sbit lcd_rs = P2^0; /*!< rs signal */
sbit lcd_rw = P2^1; /*!< rw signal */
sbit lcd_en = P2^3; /*!< en signal */

/*!
 * \note P2 address is 0xA0
 */
//__sbit __at (0xA0) lcd_rs; /*!< rs signal */
//__sbit __at (0xA1) lcd_rw; /*!< rw signal */
//__sbit __at (0xA2) lcd_en; /*!< en signal */

#endif