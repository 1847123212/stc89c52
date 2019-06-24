#include"spin_uart.h"
#include"spin_timer.h"
#include"spin_interupt.h"
#include<stdio.h>
#include<string.h>
sem_t uart_send;
sem_t uart_recv;
uchar recv_buff[10];//����buff
uchar recv_buff_ptr=0;
static const uint boaud_rate=2400;
static const uint over_time_us=13;//ÿover_time_us����ʱ��1���1��

uint spin_uart_init(){
	sem_init(uart_send,1);
	sem_init(uart_recv,0);
	spin_timer_for_uart(timer1,over_time_us);

   //SCON=0xF0;//��ʽ3�����ͨѶ���������
   //SCON = 0x50;		//8λ����,�ɱ䲨����
   SCON=0xD0;//��ʽ3,������� ֹͣλ1.5λ
   PCON|=0x80;//52��Ƭ��֧�֡�ʹ�ܺ󣬴���ʵ�ʲ����ʼӱ�
   spin_interupt_open(serial);	//�������ж�
   return boaud_rate;
}

uint spin_write_uart(const char *buff,uint n){
	uint i = 0;
	for(;i<n;i++){
		sem_wait(uart_send);                                        //�ȴ������ź���
		SBUF=*buff;
		buff++;
	}
}
//������ʽ
uchar spin_read_byte(){
	 char ret;
	 sem_wait(uart_recv);
	 critical_area_enter();
	 ret = recv_buff[--recv_buff_ptr];
	 critical_area_exit();
	 return ret;
}
//�������������
uint spin_read_line(char *buff){
	uint i = 0;
	for(;i<recv_buff_ptr;i++){
		sem_wait(uart_recv);
		critical_area_enter();
		buff[i] = recv_buff[--recv_buff_ptr];
		critical_area_exit();
		if(buff[i]==0x13)//�س���
			break;
	}
	buff[i++]='\0';
	recv_buff_ptr=0;//buff���,��ô����������
	return i;//�����ĳ���
}
//�������е����� ��������ʽ
uint spin_read_uart(char *buff){
	uint i = 0;
	critical_area_enter();
	for(;i<recv_buff_ptr;i++)
		buff[i] = recv_buff[i];
	recv_buff_ptr=0;   //buff���
	sem_init(uart_recv,0);//�ź������
	critical_area_exit();
	return i;//�����ĳ���	
}
