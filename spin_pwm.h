#ifndef __PWM_H_
#define __PWM_H_

#include<reg52.h>
sbit pwm=P2^3;
extern volatile char pwm_counter; //250us����1�Σ�ÿ������4000��
extern const char top;//�̶�Ϊ100
PROCESS_NAME(pwm_led);
#endif