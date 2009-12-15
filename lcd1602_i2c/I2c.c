/*!
 *  \file  I2c.h
  * \brief I2c functions implemetations
  */
#include "hardware.h"
#include "def.h"
#include<intrins.h>

bit ack = 0; /*! I2C ack signal */

void delay_nop(uchar n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		_nop_();
	}
}
void i2c_start()
{
	SDA = 1; /* send data signal indicating start */
	delay_nop(2);
	SCL = 1;
	delay_nop(10);
	SDA = 0; /* send start singal */
	delay_nop(10);
	SCL = 0; /* ready for send or reoceive fat */
	delay_nop(4);
}

void i2c_stop()
{
	SDA = 0;  /*  send data indicating end singal */
	delay_nop(2);
	SCL = 1; /* send end signal */
	delay_nop(10); /* ������������ʱ�����4��s */
	SDA = 1;
	delay_nop(8);
}

void send_byte(uchar c)
{
	uchar bit_cnt;
	for (bit_cnt = 0; bit_cnt < 8; bit_cnt++) /* Ҫ���͵����ݳ���Ϊ8 λ */
	{
		if ((c << bit_cnt) & 0x80 ) /* test the highest bit 0 or 1,high bit in front of lower bit  */
		{
			SDA = 1; 
		}else
		{
			SDA = 0;
		}
		delay_nop(2);
		SCL = 1; /* ��ʱ����Ϊ�ߣ�֪ͨ��������ʼ��������λ */
		delay_nop(10);
		SCL = 0;
	}
	delay_nop(4);
	SDA = 1; /* 8 λ��������ͷ������ߣ�׼������Ӧ��λ */
	delay_nop(4); 
	SCL = 1;
	delay_nop(6);
	if (SDA == 1)
	{
		ack = 0;
	}else
	{
		ack = 1;
	}
	SCL = 0;
	delay_nop(4);
}

uchar receive_byte()
{
	uchar receive_char = 0;
	uchar bit_cnt;
	SDA = 1; /* ��������Ϊ���뷽ʽ */
	for (bit_cnt =0; bit_cnt <8; bit_cnt++)
	{
		delay_nop(2);
		SCL = 0; /* ��ʱ����Ϊ��,׼����������λ */
		delay_nop(4);
		SCL = 1; /* ��ʱ����Ϊ��ʹ��������������Ч */
		delay_nop(2);
		receive_char = receive_char << 1; /* higher bit left shift to let lower bit write in */
		if (SDA == 1)
		{
			receive_char += 1;
		}
		/* another writing style */
		/* receive_char = receive_char <<1 + SDA; */
		delay_nop(2);
	}
	SCL = 0;
	delay_nop(2);
	return receive_char;
}

void master_send_byte(uchar sla, uchar c)
{
	i2c_start(); /* Start I2c bus */
	send_byte(sla); /* send address */
	/*  if (ack == 0) return 0; */
	delay_nop(4);
	send_byte(c); /*  send data */
	/* if (ack == 0) return 0; */
	delay_nop(4);
	i2c_stop(); /* stop I2c bus */
}

void i2c_ack(bit a)
{
	if (a == 0)
	{
		SDA = 0; /* ack signal */
	}else
	{
		SDA = 1; /* nack signal */
	}
	delay_nop(2);
	SCL = 1; /* the 9th clock to accept ack signal */ 
	delay_nop(4);
	SCL = 0; /* ��ʱ����,ǯסI2C �����Ա�������� */
	delay_nop(2);
}

uchar slave_receive_byte(uchar sla)
{
	uchar receive; 
	i2c_start(); /* start I2c bus */
	send_byte(sla + 1); /* send address,because of master send mode,read address is slave+1 */
	receive = receive_byte();
	i2c_ack(1); /* send nack signal */
	i2c_stop(); /* stop I2c bus */
	return receive;
}