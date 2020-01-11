#ifndef SPINTIMERH
#define SPINTIMERH

#include"spin_common.h"
#define mode0 0
#define mode1 1
#define mode2 2
#define mode3 3

void spin_timer_start(uchar dev);
void spin_timer_stop(uchar dev);
void spin_counter_time(uchar dev,uint time); //��Ϊ������ʹ�ã����������ⲿ����	,�����Ǵ���
void uart_boaud(uint overtime);//��uart��Ϊ�����ʷ�����
void delay2us(void);
void delay3us(void);
void delay1ms(void);
void delay1s(void);
void spin_sysTick(uint callback);
#endif