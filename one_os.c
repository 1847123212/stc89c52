#include"one_os.h"
#include"spin_common.h"
#include"spin_userstart.h"
#include"spin_interupt.h"
#include"spin_timer.h"
#include"spin_exinterupt.h"
#include"spin_gpio.h"
#include"spin_uart.h"
#include"spin_watchdog.h"
#include"spin_pwrmgr.h"
#include<string.h>
#include<stdio.h>
//��ʱι������
void task1(){
	 spin_watchdog_clear();
}
//������������
void task2(){
	static uint recv_fre=0;
	recv_fre=~recv_fre;
	spin_set_gpio_bit_value(GPIO2,5,recv_fre);
}
//��ʱ�������ݵ�����
void task3(){
	 spin_write_uart("os running!\n",strlen("os running!\n"));
}
//��ѯ�Ƿ��д�������
//void task4(){
//     static uchar idata recv[15];
//	 uchar ret = 0;
// 	 ret = spin_read_byte();
//	 if(ret != 0)
//	 	spin_write_uart(&ret,strlen(ret));
//}
static idata Tasks task[]=   
{   
    {0,0,400,400,task1}, //ι��		100ms
    {1,0,2000,2000,task2}, //����	500ms
	{2,0,4000,4000,task3},//�����ڣ�1s
//	{3,0,2000,2000,task4},//�����ڣ�500ms
};

void TaskHangup(unsigned char Task_Num)//����������������������������
{ 
	task[Task_Num].Run=0;
}

void TaskRecovery(unsigned char Task_Num)//����ָ������������������������
{
	task[Task_Num].Run=1;
}

void TaskRemarks(void) //���ڶ�ʱ���ж�����
{
	unsigned char i;
	for (i=0; i<TASK_MAX; i++)          
	{
		if (task[i].Timer)          
		{
			task[i].Timer--;        
			if (task[i].Timer == 0)  																														//������65500���ֵ��֤�����ʱ��Ҳ��ִ����������
			{
					task[i].Timer = task[i].ItvTime;
					task[i].Run = 1;           
			}
		}
	}
}

void TaskProcess(void)//�������while(1)ѭ������
{
    unsigned char  i;
	for (i=0; i<TASK_MAX; i++)          
    {         
		if (task[i].Run)     
        {
             task[i].Run = 0;     
			 task[i].TaskHook();  
        }
    }   
	idle_mode();//����͹���ģʽ		
}