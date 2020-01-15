#ifndef SPINWATCHDOGH
#define SPINWATCHDOGH
#include<reg52.h>
#include"spin_common.h"
void spin_watchdog_enable();
void spin_watchdog_disable();
void spin_watchdog_idlework(bool torf);
void spin_watchdog_clear();
//pre_scale 2 4 8 16 32 ....256 mhz=12,24
uint spin_watchdog_overtime(uchar pre_scale,uchar mhz);  //���ؿ��Ź����ʱ�䡣mhz��ϵͳƵ��
#endif