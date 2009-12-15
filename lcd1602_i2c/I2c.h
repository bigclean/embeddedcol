/*!
 *  \file  I2c.h
  * \brief  I2c head file
 */
#ifndef __I2c_H_
#define __I2c_H_
#include "def.h"

/* funtion prototype */
/*!
 * \fn i2c_start()
 * \brief start I2C bus
 * return none
 */
void i2c_start();
/*!
 * \fn i2c_stop()
 * \brief stop I2c bus
 * \return none
 */
void i2c_stop();

/*!
 * \fn send_byte(uchar c)
 * \brief send byte to slave device
 * \param c the sended byte
 * \return none
 */
void send_byte(uchar c);

/*!
 * \fn master_send_byte(uchar sla, uchar c)
 * \brief master send byte to slave
 * \param sla slaver address
 * \param c the sended byte
 * \return none
 */
void master_send_byte(uchar sla, uchar c);
/*!
 * \fn i2c_ack(bit a)
 * \brief 
 * \return none
 */
void i2c_ack(bit a);

/*!
 * \fn receive_byte()
 * \brief receive from slave
 * \return received byte
 */
uchar receive_byte();
/*!
 * \fn slave_receive_byte(uchar sla)
 * \brief receive byte from the refered address
 * \param sla slaver device address
 * \return received byte
 */
uchar slave_receive_byte(uchar sla);

/*!
 * \fn delay_nop(uchar n)
 * \brief delay in system clock
 * \param n the amount of system clock you want to delay
 * \return none
 */
void delay_nop(uchar n);

#endif