#ifndef SPINTIMERH
#define SPINTIMERH
#include <reg52.h>	   //���ļ��ж�����51��һЩ���⹦�ܼĴ���
#include"spin_common.h"
#include"spin_interupt.h"
//#include<stdarg.h>
typedef enum{
   mode0=0,
   mode1,
   mode2,
   mode3,
}TIMER_MODE_TYPES;

SPIN_STATUS spin_timer_us(uint us);	//��Ϊ��ʱ��ʹ��ʱ������Ƶ����������12��Ƶ������Ƶ����12MHZ,ָ��������1us
SPIN_STATUS spin_timer_ms(uint ms);
SPIN_STATUS spin_timer_sec(uint sec);
SPIN_STATUS spin_counter_time(uint time); //��Ϊ������ʹ�ã����������ⲿ����	,�����Ǵ���
//�������ʱ�䣬����Ҫ���õĳ�ֵ
uint primary_value(uint overflow_time_us);
void spin_timer_set(INTER_LIST dev,TIMER_MODE_TYPES mode,uint time);
void spin_timer_start(INTER_LIST dev);
void spin_timer_stop(INTER_LIST dev);
void spin_timer_for_uart(INTER_LIST dev,uint overtime);//��uart��Ϊ�����ʷ�����
void delay2us(void);
void delay3us(void);
void delay1ms(void);
void delay1s(void);
#endif