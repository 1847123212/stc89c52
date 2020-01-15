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
#include"xprintf.h"
DATA unsigned int system_time0 = 0;	 //2���ֽ�
DATA unsigned int system_time1 = 0;
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
	xputs("os running\r\n"); 
}
//��ѯ�Ƿ��д�������
void task4(){

}

void task5(){
     //��Ϣ���з��Ͳ���
  // fd = spin_cycle_queue_init();
   //spin_cycle_queue_push(fd,0x33);
}
void task6(){
     //��Ϣ���н��ղ���
  // uchar content;
  // content = spin_cycle_queue_pop(fd);

}
void task7(){
   //�ڴ�������
   //uchar addr;
   //memory_pool_init();
   //addr = spin_memory_malloc(2);
 
}
static Tasks task[]=   
{   
    {0,1,400,100,task1}, //ι��		100ms
    {1,0,2000,500,task2}, //����	500ms
	{2,0,4000,1000,task3},//�����ڣ�1s
//	{3,0,2000,2000,task4},//�����ڣ�500ms
//	{4,0,2000,2000,task5},//��Ϣ���з��Ͳ��ԣ�500ms
//	{5,0,2000,2000,task6},//��Ϣ���н��ղ��ԣ�500ms
//	{3,0,2000,2000,task7},//�ڴ������ԣ�500ms
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
	 system_time0++;
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