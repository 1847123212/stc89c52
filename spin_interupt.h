#ifndef SPININTERUPTH
#define SPININTERUPTH
#include <reg52.h>	   //���ļ��ж�����51��һЩ���⹦�ܼĴ���
#include"spin_common.h"
extern uint* inter_vector_function[inter_num]; //�ŵ����������ø�ͷ�ļ����ļ�,��Ҫ�����ṩ�жϻص�����
typedef void*(interupt_callback)(void *);
void spin_interupt_init();
void spin_interupt_enable();
void spin_interupt_disable();
void spin_interupt_open(INTER_LIST num,INTER_PRORITY prority);
void spin_interupt_close(INTER_LIST num);
void spin_interupt_set_params(INTER_LIST num,uchar params);	 //������
#endif