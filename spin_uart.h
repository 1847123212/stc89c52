#ifndef SPINUARTH
#define SPINUARTH
#include <reg52.h>	   //���ļ��ж�����51��һЩ���⹦�ܼĴ���
#include"spin_common.h"
extern sem_t uart_recv;
extern sem_t uart_send;		//�����ź���
extern uchar recv_buff[10];//����buff
extern uchar recv_buff_ptr;

uint spin_uart_init();//���ز�����
uint spin_write_uart(const char *buff,uint n);
uint spin_read_uart(char *buff);
uint spin_read_line(char *buff);
uchar spin_read_byte();
#endif