#ifndef __I2C_H_
#define __I2C_H_

#include<reg52.h>
sbit SCL=P2^1;
sbit SDA=P2^0;

//ģ��I2C���ߵ����Ŷ���
#define	 I2C_SCL 	SCL
#define	 I2C_SDA	SDA

//����I2C����ʱ�ӵ���ʱֵ��Ҫ����ʵ������޸ģ�ȡֵ1��255
//SCL�ź�����ԼΪ(I2C_DELAY_VALUE*4+15)����������
#define I2C_DELAY_VALUE		1 

//����I2C����ֹͣ������һ�ο�ʼ֮ǰ�ĵȴ�ʱ�䣬ȡֵ1��65535
//�ȴ�ʱ��ԼΪ(I2C_STOP_WAIT_VALUE*8)����������
//���ڶ�������ȡֵΪ1���ɣ�������ĳЩ������˵���ϳ�����ʱ�Ǳ����
#define I2C_STOP_WAIT_VALUE	1

//I2C���߳�ʼ����ʹ���ߴ��ڿ���״̬

void I2C_Init(void);
void I2C_Start(void);
void I2C_Write(char dat);
char I2C_Read(void);
unsigned char I2C_GetAck(void);
void I2C_PutAck(unsigned char ack);
void I2C_Stop(void);

//I2C�����ۺϷ��ͺ�������ӻ����Ͷ���ֽڵ�����
unsigned char I2C_Puts
(
	unsigned char SlaveAddr,
	unsigned int SubAddr,
	unsigned char SubMod,
	unsigned char *dat,
	unsigned int Size
);

//I2C�����ۺϽ��պ������Ӵӻ����ն���ֽڵ�����
unsigned char I2C_Gets
(
	unsigned char SlaveAddr,
	unsigned int SubAddr,
	unsigned char SubMod,
	unsigned char *dat,
	unsigned int Size
);

#endif	//_I2C_H_
